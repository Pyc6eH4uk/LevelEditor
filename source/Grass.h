//
// Created by gdhsnlvr on 03.07.17.
//

#ifndef FOALEDITOR_CELL_H
#define FOALEDITOR_CELL_H

#include "GridItem.h"

enum CellType {
    EMPTY_CELL,
    DEFAULT_CELL,
    COUNT_CELL
};

class Grass : public GridItem {
protected:
    CellType _type;

public:
    Grass(int x, int y, CellType type, QPixmap *pixmap);

    CellType get_type() const;
};


#endif //FOALEDITOR_CELL_H
