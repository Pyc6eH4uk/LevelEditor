//
// Created by gdhsnlvr on 02.10.17.
//

#ifndef CROSSROAD_LEVEL_LEVEL_GENERATOR_T_H
#define CROSSROAD_LEVEL_LEVEL_GENERATOR_T_H


#include <set>
#include <vector>
#include "point_t.h"

class level_generator_t {
protected:
    int m_seed;
    std::set<point_t> m_grass_set;
    std::set<point_t> m_tree_set;
    std::set<point_t> m_star_set;
    std::vector<point_t> m_grass_path;
    std::vector<point_t> m_directions;
    int m_grass_count;
    int m_tree_count;
    int m_star_count;
    int m_relax_count;

public:
    level_generator_t() = default;
    level_generator_t(int grass_count, int relax_count, int tree_count, int star_count);

    void reset_seed();
    void set_seed(int seed);
    void solve_level();

    std::vector<point_t> grasses() const;
    std::vector<point_t> trees() const;
    std::vector<point_t> stars() const;
    int seed() const;

protected:
    int point_index_in_path(point_t point) const;
    bool point_has_bad_cells(point_t point, int distance) const;
    std::vector<point_t> get_near_points(point_t point) const;

    int find_distance(point_t from, point_t to);
    bool generate_path_can_find_path(point_t from, point_t to, point_t parent);
    void generate_path_dfs(point_t current, point_t start, int depth);
    void generate_path();
    void relax_path();
    void add_trees();
    void add_stars();
};


#endif //CROSSROAD_LEVEL_LEVEL_GENERATOR_T_H
