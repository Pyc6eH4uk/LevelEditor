//
// Created by gdhsnlvr on 03.07.17.
//

#include "Bonus.h"

Bonus::Bonus(int x, int y, BonusType type, QPixmap *pixmap) : GridItem(x, y, pixmap) {
    _type = type;
}

BonusType Bonus::get_type() const {
    return _type;
}
