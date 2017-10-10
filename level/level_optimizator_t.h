//
// Created by gdhsnlvr on 10.10.17.
//

#ifndef FOALEDITOR_LEVEL_OPTIMIZATOR_T_H
#define FOALEDITOR_LEVEL_OPTIMIZATOR_T_H


#include <set>
#include <map>
#include <vector>
#include "point_t.h"
#include "square_t.h"

class level_optimizator_t {
protected:
    std::set<point_t> m_grass;
    std::map<int, int> m_scan_line;
    std::vector<square_t> m_result_squares;
    std::vector<point_t> m_boundary_points;
    std::map<point_t, std::vector<int>> m_optimazed_squares;
    std::map<point_t, std::vector<int>> m_optimazed_boundary;
    int m_visible_radius;

public:
    level_optimizator_t(const std::set<point_t> grass, int visible_radius = 16);

    void calculate();

protected:
    void build_squares();
    void optimize_idexes();
};


#endif //FOALEDITOR_LEVEL_OPTIMIZATOR_T_H
