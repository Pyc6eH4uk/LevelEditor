//
// Created by gdhsnlvr on 02.10.17.
//

#include "level_t.h"

level_t::level_t() {

}

const std::vector<point_t> &level_t::grass() const {
    return m_grass;
}

const std::vector<point_t> &level_t::tree() const {
    return m_tree;
}

template<typename iter_t>
void level_t::set_grass(iter_t begin, iter_t end) {
    m_grass.clear();
    m_grass.insert(m_grass.end(), begin, end);
}

template<typename iter_t>
void level_t::set_tree(iter_t begin, iter_t end) {
    m_tree.clear();
    m_tree.insert(m_tree.end(), begin, end);
}
