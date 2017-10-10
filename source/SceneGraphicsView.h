//
// Created by gdhsnlvr on 03.07.17.
//

#ifndef FOALEDITOR_SCENEGRAPHICSVIEW_H
#define FOALEDITOR_SCENEGRAPHICSVIEW_H


#include <QtWidgets/QGraphicsView>
#include <QtCore/QJsonObject>
#include <level/level_t.h>
#include <level/level_generator_t.h>
#include "Grass.h"
#include "GridItemBuilder.h"

class SceneGraphicsView : public QGraphicsView {
protected:
    int _width, _height;
    QGraphicsScene _scene;
    GridItemBuilder _gridItemBuilder;
    CellType _current_cell_type;
    BonusType _current_bonus_type;
    ObjectsType _current_food_type;
    bool _mouse_pressed;
    level_generator_t _level_generator;
    int _center_offset_x;
    int _center_offset_y;

public:
    SceneGraphicsView();

    int get_width() const;
    void set_width(int _width);
    int get_height() const;
    void set_height(int _height);

    void set_level_generator(const level_generator_t &_level_generator);

    void set_current_cell_type(CellType _current_type);
    void set_current_bonus_type(BonusType _current_bonus_type);
    void set_current_food_type(ObjectsType _current_food_type);

    void generate();

    void load(QJsonObject jsonObject);
    QJsonObject save();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void updateCellAt(QPointF position);
    void updateBonusAt(QPointF position);
    void updateFoodAt(QPointF position);
};


#endif //FOALEDITOR_SCENEGRAPHICSVIEW_H
