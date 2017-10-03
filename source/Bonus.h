//
// Created by gdhsnlvr on 03.07.17.
// Edited by Pyc6eH4uk 3.10.17
//

#ifndef FOALEDITOR_BONUS_H
#define FOALEDITOR_BONUS_H


#include <QtWidgets/QGraphicsItem>
#include "GridItem.h"

enum BonusType {
    COUNT_BONUS
};

class Bonus : public GridItem {
protected:
    int _x;
    int _y;
    BonusType _type;
    QPixmap *_pixmap;

public:
    Bonus(int x, int y, BonusType type, QPixmap *pixmap);

    BonusType get_type() const;
};


#endif //FOALEDITOR_BONUS_H
