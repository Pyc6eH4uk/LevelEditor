//
// Created by gdhsnlvr on 03.07.17.
//

#include "GridItem.h"
#include <QPainter>

GridItem::GridItem(int x, int y, QPixmap *pixmap) {
    _x = x;
    _y = y;
    _pixmap = pixmap;

    setPos(x * _pixmap->width(), y * _pixmap->height());
}

void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0, 0, *_pixmap);
}

int GridItem::get_x() const {
    return _x;
}

int GridItem::get_y() const {
    return _y;
}

QRectF GridItem::boundingRect() const {
    return QRectF(0, 0, _pixmap->width(), _pixmap->height());
}

QPainterPath GridItem::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
