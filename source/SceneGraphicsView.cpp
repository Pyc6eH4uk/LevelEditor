//
// Created by gdhsnlvr on 03.07.17.
// Editet by Pyc6eH4uk on 3.10.17
//

#include "SceneGraphicsView.h"
#include "GridItemBuilder.h"

#include <QMouseEvent>
#include <QDebug>

#include <cstdlib>
#include <cmath>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <level/level_optimizator_t.h>

SceneGraphicsView::SceneGraphicsView() {
    _scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(&_scene);
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Foal game editor"));
    setBackgroundBrush(Qt::darkGray);
    resize(400, 300);

    _width = 8;
    _height = 32;

    _gridItemBuilder.setPixmap(CellType::DEFAULT_CELL, new QPixmap(":/resource/grass_cell.png"));
    _gridItemBuilder.setPixmap(CellType::EMPTY_CELL, new QPixmap(":/resource/empty_cell.png"));

    _gridItemBuilder.setPixmap(ObjectsType::STARS, new QPixmap(":/resource/star.png"));
    _gridItemBuilder.setPixmap(ObjectsType::TREES, new QPixmap(":/resource/tree.png"));
    _gridItemBuilder.setPixmap(ObjectsType::WATERFLOW, new QPixmap(":/resource/waterfall.png"));

    _mouse_pressed = false;
    _current_cell_type = COUNT_CELL;
    _current_bonus_type = COUNT_BONUS;
    _current_food_type = COUNT_OBJECTS;
}

void SceneGraphicsView::generate() {
    _level_generator.solve_level();
    const int inf = (int) 1e9;
    int min_x = inf;
    int max_x = -inf;
    int min_y = inf;
    int max_y = -inf;
    for (auto point : _level_generator.grasses()) {
        min_x = std::min(min_x, point.x());
        max_x = std::max(max_x, point.x());
        min_y = std::min(min_y, point.y());
        max_y = std::max(max_y, point.y());
    }
    _width = max_x - min_x + 1;
    _height = max_y - min_y + 1;

    _scene.clear();
    _scene.setSceneRect(- 32, - 32, _width * 32 + 64, _height * 32 + 64 + 32);
    setMinimumWidth(std::min(_width * 32 + 32 * 3, 800));

    auto grasses = _level_generator.grasses();
    std::set<point_t> grassesSet(grasses.begin(), grasses.end());

    for (int i = 0; i < _width; ++i) {
        for (int j = 0; j < _height; ++j) {
            if (grassesSet.count(point_t(i + min_x, j + min_y))) {
                CellType cellType = CellType::DEFAULT_CELL;
                Grass *cell = _gridItemBuilder.buildCell(i, j, cellType);
                _scene.addItem(cell);
            } else {
                CellType cellType = CellType::EMPTY_CELL;
                Grass *cell = _gridItemBuilder.buildCell(i, j, cellType);
                _scene.addItem(cell);
            }
        }
    }

    for (auto tree : _level_generator.trees()) {
        int i = tree.x() - min_x;
        int j = tree.y() - min_y;
        Objects *new_cell = _gridItemBuilder.buildFood(i, j, ObjectsType::TREES);
        _scene.addItem(new_cell);
    }

    for (auto star : _level_generator.stars()) {
        int i = star.x() - min_x;
        int j = star.y() - min_y;
        Objects *new_cell = _gridItemBuilder.buildFood(i, j, ObjectsType::STARS);
        _scene.addItem(new_cell);
    }
}

int SceneGraphicsView::get_width() const {
    return _width;
}

void SceneGraphicsView::set_width(int _width) {
    SceneGraphicsView::_width = _width;
}

int SceneGraphicsView::get_height() const {
    return _height;
}

void SceneGraphicsView::set_height(int _height) {
    SceneGraphicsView::_height = _height;
}

void SceneGraphicsView::updateCellAt(QPointF position) {
    auto items = _scene.items(position, Qt::IntersectsItemShape, Qt::DescendingOrder, transform());
    for (auto item : items) {
        Grass *cell = dynamic_cast<Grass *>(item);

        if (cell) {
            Grass *new_cell = _gridItemBuilder.buildCell(cell->get_x(), cell->get_y(), _current_cell_type);

            _scene.removeItem(item);
            _scene.addItem(new_cell);
        }
    }
}

void SceneGraphicsView::updateBonusAt(QPointF position) {
    auto items = _scene.items(position, Qt::IntersectsItemShape, Qt::DescendingOrder, transform());

    Grass *cell = nullptr;
    for (auto item : items) {
        Bonus *bonus = dynamic_cast<Bonus *>(item);
        if (bonus) {
            _scene.removeItem(bonus);
        }

        Objects *food = dynamic_cast<Objects *>(item);
        if (food) {
            _scene.removeItem(food);
        }

        Grass *curCell = dynamic_cast<Grass *>(item);
        if (curCell) {
            cell = curCell;
        }
    }

    if (cell) {
        if (cell->get_type() == EMPTY_CELL)
            return;

        Bonus *new_cell = _gridItemBuilder.buildBonus(cell->get_x(), cell->get_y(), _current_bonus_type);

        _scene.addItem(new_cell);
    }
}

void SceneGraphicsView::updateFoodAt(QPointF position) {
    auto items = _scene.items(position, Qt::IntersectsItemShape, Qt::DescendingOrder, transform());

    Grass *cell = nullptr;
    for (auto item : items) {
        Grass *curCell = dynamic_cast<Grass *>(item);
        if (curCell) {
            cell = curCell;
        }
    }

    if (cell) {
        if (cell->get_type() == EMPTY_CELL && _current_food_type == ObjectsType::WATERFLOW) {
            Objects *new_cell = _gridItemBuilder.buildFood(cell->get_x(), cell->get_y(), _current_food_type);

            for (auto item : items) {
                Objects *food = dynamic_cast<Objects *>(item);
                if (food) {
                    _scene.removeItem(food);
                }
            }

            _scene.addItem(new_cell);
        } else if (cell->get_type() != EMPTY_CELL && _current_food_type != ObjectsType::WATERFLOW) {
            Objects *new_cell = _gridItemBuilder.buildFood(cell->get_x(), cell->get_y(), _current_food_type);

            for (auto item : items) {
                Objects *food = dynamic_cast<Objects *>(item);
                if (food) {
                    _scene.removeItem(food);
                }
            }

            _scene.addItem(new_cell);
        }
    }
}

void SceneGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    QGraphicsView::mouseReleaseEvent(event);

    _mouse_pressed = false;

    if (_current_cell_type != COUNT_CELL)
        updateCellAt(mapToScene(event->pos()));
    if (_current_bonus_type != COUNT_BONUS)
        updateBonusAt(mapToScene(event->pos()));
    if (_current_food_type != COUNT_OBJECTS)
        updateFoodAt(mapToScene(event->pos()));
}

void SceneGraphicsView::mousePressEvent(QMouseEvent *event) {
    QGraphicsView::mousePressEvent(event);

    _mouse_pressed = true;
}

void SceneGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);

    if (!_mouse_pressed) return;

    if (_current_cell_type != COUNT_CELL)
        updateCellAt(mapToScene(event->pos()));
    if (_current_bonus_type != COUNT_BONUS)
        updateBonusAt(mapToScene(event->pos()));
    if (_current_food_type != COUNT_OBJECTS)
        updateFoodAt(mapToScene(event->pos()));
}

void SceneGraphicsView::set_current_cell_type(CellType _current_type) {
    SceneGraphicsView::_current_cell_type = _current_type;
}

void SceneGraphicsView::set_current_bonus_type(BonusType _current_bonus_type) {
    SceneGraphicsView::_current_bonus_type = _current_bonus_type;
}

void SceneGraphicsView::set_current_food_type(ObjectsType _current_food_type) {
    SceneGraphicsView::_current_food_type = _current_food_type;
}

QJsonObject SceneGraphicsView::save() {
    level_optimizator_t level_optimizator(_level_generator.grasses_set(), 16);
    level_optimizator.calculate();

    std::vector<Grass*> cells;
    std::vector<Bonus*> bonuses;
    std::vector<Objects*> foods;

    for (auto item : items()) {
        Grass *cell = dynamic_cast<Grass *>(item);
        if (cell) {
            cells.push_back(cell);
        }

        Bonus *bonus = dynamic_cast<Bonus *>(item);
        if (bonus) {
            bonuses.push_back(bonus);
        }

        Objects *food = dynamic_cast<Objects *>(item);
        if (food) {
            foods.push_back(food);
        }
    }

    QJsonObject jsonObject;

    QJsonArray cellsArray;
    for (Grass* cell : cells) {
        QJsonObject cellObject;
        cellObject["x"] = cell->get_x();
        cellObject["y"] = cell->get_y();
        cellObject["type"] = (int) cell->get_type();
        cellsArray.push_back(cellObject);
    }

    QJsonArray bonusesArray;
    for (Bonus* bonus : bonuses) {
        QJsonObject cellObject;
        cellObject["x"] = bonus->get_x();
        cellObject["y"] = bonus->get_y();
        cellObject["type"] = (int) bonus->get_type();
        bonusesArray.push_back(cellObject);
    }

    QJsonArray foodArray;
    for (Objects* cell : foods) {
        QJsonObject cellObject;
        cellObject["x"] = cell->get_x();
        cellObject["y"] = cell->get_y();
        cellObject["type"] = (int) cell->get_type();
        foodArray.push_back(cellObject);
    }

    jsonObject["width"] = _width;
    jsonObject["height"] = _height;
    jsonObject["cells"] = cellsArray;
    jsonObject["objects"] = foodArray;

    return jsonObject;
}

void SceneGraphicsView::load(QJsonObject jsonObject) {
    _scene.clear();

    _width = jsonObject["width"].toInt();
    _height = jsonObject["height"].toInt();

    _scene.setSceneRect(- 32, - 32, _width * 32 + 64, _height * 32 + 64 + 32);
    setMinimumWidth(_width * 32 + 32 * 3);

    auto cells = jsonObject["cells"].toArray();
    auto foods = jsonObject["objects"].toArray();

    for (int i = 0; i < cells.size(); i++) {
        auto cellObject = cells[i].toObject();
        Grass *cell = _gridItemBuilder.buildCell(
                cellObject["x"].toInt(),
                cellObject["y"].toInt(),
                static_cast<CellType>(cellObject["type"].toInt())
        );
        _scene.addItem(cell);
    }


    for (int i = 0; i < foods.size(); i++) {
        auto cellObject = foods[i].toObject();
        Objects *cell = _gridItemBuilder.buildFood(
                cellObject["x"].toInt(),
                cellObject["y"].toInt(),
                static_cast<ObjectsType >(cellObject["type"].toInt())
        );
        _scene.addItem(cell);
    }
}

void SceneGraphicsView::set_level_generator(const level_generator_t &_level_generator) {
    SceneGraphicsView::_level_generator = _level_generator;
}
