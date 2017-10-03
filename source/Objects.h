//
// Created by gdhsnlvr on 03.07.17.
//

#ifndef FOALEDITOR_FOOD_H
#define FOALEDITOR_FOOD_H

#include "GridItem.h"

enum ObjectsType {
    STARS,
    TREES,
    WATERFLOW,
    COUNT_OBJECTS
};

class Objects : public GridItem {
protected:
    ObjectsType _type;

public:
    Objects(int x, int y, ObjectsType type, QPixmap *pixmap);

    ObjectsType get_type() const;
};


#endif //FOALEDITOR_FOOD_H
