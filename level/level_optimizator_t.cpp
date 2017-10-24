//
// Created by gdhsnlvr on 10.10.17.
//

#include <iostream>
#include "level_optimizator_t.h"

level_optimizator_t::level_optimizator_t(const std::set<point_t> grass, int visible_radius) {
    m_grass = grass;
    m_visible_radius = visible_radius;
}

void level_optimizator_t::calculate() {
    build_squares();
    optimize_idexes();
}

void level_optimizator_t::build_squares() {
    std::vector<point_t> grass(m_grass.begin(), m_grass.end());

    const int inf = - (int) 1e9;
    point_t dir_left = {-1, 0};
    point_t dir_right = {1, 0};
    point_t dir_down = {0, -1};

    int n = (int) grass.size();
    for (int i = 0; i < n; i++) {
        if (!m_grass.count(grass[i] + dir_left)) {
            m_scan_line[grass[i].y()] = grass[i].x();
        }
        if (!m_grass.count(grass[i] + dir_right)) {
            square_t square;
            square.set_x(m_scan_line[grass[i].y()]);
            square.set_y(grass[i].y());
            square.set_w(grass[i].x() - m_scan_line[grass[i].y()] + 1);
            square.set_h(1);
            m_result_squares.push_back(square);
        }
    }

    std::cerr << m_result_squares.size() << " \\ " << m_grass.size() << std::endl;
}

void level_optimizator_t::optimize_idexes() {
    std::vector<point_t> grass(m_grass.begin(), m_grass.end());

    int max_count = 0;
    for (int i = 0; i < grass.size(); i++) {
        m_optimazed_squares[grass[i]].clear();
        m_optimazed_boundary[grass[i]].clear();
        square_t square;
        square.set_x(grass[i].x() - m_visible_radius);
        square.set_y(grass[i].y() - m_visible_radius);
        square.set_w(1 + 2 * m_visible_radius);
        square.set_h(1 + 2 * m_visible_radius);
        for (int j = 0; j < m_result_squares.size(); j++) {
            if (square.intersect(m_result_squares[j])) {
                m_optimazed_squares[grass[i]].push_back(j);
            }
        }
        max_count = std::max(max_count, (int) m_optimazed_squares[grass[i]].size());
    }

    std::cerr << max_count << " \\ " << m_grass.size() << std::endl;
}

const std::vector<square_t> &level_optimizator_t::getM_result_squares() const {
    return m_result_squares;
}

const std::vector<point_t> &level_optimizator_t::getM_boundary_points() const {
    return m_boundary_points;
}

const std::map<point_t, std::vector<int>> &level_optimizator_t::getM_optimazed_squares() const {
    return m_optimazed_squares;
}

const std::map<point_t, std::vector<int>> &level_optimizator_t::getM_optimazed_boundary() const {
    return m_optimazed_boundary;
}
