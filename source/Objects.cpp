//
// Created by gdhsnlvr on 03.07.17.
//

#include "Objects.h"

Objects::Objects(int x, int y, ObjectsType type, QPixmap *pixmap) : GridItem(x, y, pixmap) {
    _type = type;
}

ObjectsType Objects::get_type() const {
    return _type;
}
