//
// Created by gdhsnlvr on 02.10.17.
//

#ifndef CROSSROAD_LEVEL_LEVEL_T_H
#define CROSSROAD_LEVEL_LEVEL_T_H


#include <vector>
#include "point_t.h"

class level_t {
protected:
    std::vector<point_t> m_grass;
    std::vector<point_t> m_tree;

public:
    level_t();

    const std::vector<point_t> &grass() const;
    const std::vector<point_t> &tree() const;

    template <typename iter_t>
    void set_grass(iter_t begin, iter_t end);

    template <typename iter_t>
    void set_tree(iter_t begin, iter_t end);
};


#endif //CROSSROAD_LEVEL_LEVEL_T_H
