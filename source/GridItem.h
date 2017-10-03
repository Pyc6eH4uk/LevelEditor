//
// Created by gdhsnlvr on 03.07.17.
//

#ifndef FOALEDITOR_GRIDITEM_H
#define FOALEDITOR_GRIDITEM_H


#include <QtWidgets/QGraphicsItem>

class GridItem : public QGraphicsItem {
protected:
    int _x;
    int _y;
    QPixmap *_pixmap;

public:
    GridItem(int x, int y, QPixmap *pixmap);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int get_x() const;
    int get_y() const;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};


#endif //FOALEDITOR_GRIDITEM_H
