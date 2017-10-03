//
// Created by gdhsnlvr on 03.07.17.
//

#ifndef FOALEDITOR_CELLBUILDER_H
#define FOALEDITOR_CELLBUILDER_H

#include "Grass.h"
#include "Bonus.h"
#include "Objects.h"

class GridItemBuilder {
protected:
    std::map<CellType, QPixmap*> _cellImages;
    std::map<BonusType, QPixmap*> _bonusImages;
    std::map<ObjectsType, QPixmap*> _foodImages;

public:
    GridItemBuilder() = default;

    void setPixmap(CellType type, QPixmap *pixmap);
    void setPixmap(BonusType type, QPixmap *pixmap);
    void setPixmap(ObjectsType type, QPixmap *pixmap);

    Grass*  buildCell(int x, int y, CellType type);
    Bonus* buildBonus(int x, int y, BonusType type);
    Objects*  buildFood(int x, int y, ObjectsType type);
};

#endif //FOALEDITOR_CELLBUILDER_H
