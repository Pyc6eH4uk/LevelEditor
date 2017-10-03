//
// Created by gdhsnlvr on 03.07.17.
//

#include "GridItemBuilder.h"

void GridItemBuilder::setPixmap(CellType type, QPixmap *pixmap) {
    _cellImages[type] = pixmap;
}

void GridItemBuilder::setPixmap(BonusType type, QPixmap *pixmap) {
    _bonusImages[type] = pixmap;
}

void GridItemBuilder::setPixmap(ObjectsType type, QPixmap *pixmap) {
    _foodImages[type] = pixmap;
}

Grass *GridItemBuilder::buildCell(int x, int y, CellType type) {
    return new Grass(x, y, type, _cellImages[type]);
}

Bonus *GridItemBuilder::buildBonus(int x, int y, BonusType type) {
    return new Bonus(x, y, type, _bonusImages[type]);
}

Objects *GridItemBuilder::buildFood(int x, int y, ObjectsType type) {
    return new Objects(x, y, type, _foodImages[type]);
}
