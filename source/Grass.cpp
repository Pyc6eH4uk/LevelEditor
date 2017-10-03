//
// Created by gdhsnlvr on 03.07.17.
//

#include "Grass.h"

#include <QPainter>
#include <QDebug>

Grass::Grass(int x, int y, CellType type, QPixmap *pixmap) : GridItem(x, y, pixmap) {
    _type = type;
}

CellType Grass::get_type() const {
    return _type;
}
