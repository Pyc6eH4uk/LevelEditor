//
// Created by gdhsnlvr on 02.10.17.
//

#include <algorithm>
#include <queue>
#include <map>
#include <iostream>
#include "level_generator_t.h"

level_generator_t::level_generator_t(int grass_count, int relax_count, int tree_count, int star_count) {
    m_grass_count = grass_count;
    m_relax_count = relax_count;
    m_tree_count = tree_count;
    m_star_count = star_count;
    m_directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
}

int level_generator_t::point_index_in_path(point_t point) const {
    auto it = std::find(m_grass_path.begin(), m_grass_path.end(), point);
    if (it != m_grass_path.end())
        return (int) (it - m_grass_path.begin());
    return -1;
}

bool level_generator_t::point_has_bad_cells(point_t cell, int distance) const {
    auto index = m_grass_path.size();
    for (int dx = -distance; dx <= distance; dx++) {
        for (int dy = -distance; dy <= distance; dy++) {
            auto near_distance = std::abs(dx) + std::abs(dy);
            if (near_distance <= distance) {
                auto near = cell + point_t {dx, dy};
                auto index_near = point_index_in_path(near);
                if (index_near >= 0 && near_distance != std::abs(index - index_near)) {
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<point_t> level_generator_t::get_near_points(point_t point) const {
    std::vector<point_t> near_points;

    for (auto direction : m_directions) {
        near_points.emplace_back(point + direction);
    }

    return near_points;
}

bool level_generator_t::generate_path_can_find_path(point_t from, point_t to, point_t parent) {
    std::set<point_t> forbidden;
    for (auto point : m_grass_path) {
        if (point == to || point == parent) continue;

        forbidden.insert(point);
        for (auto near : get_near_points(point)) {
            forbidden.insert(near);
        }
    }

    if (forbidden.count(from)) {
        return false;
    }

    std::set<point_t> used;
    std::queue<point_t> q;
    q.push(from);
    used.insert(from);

    while (!q.empty()) {
        point_t current = q.front();
        q.pop();

        for (auto near : get_near_points(current)) {
            if (near == to) {
                return true;
            }

            if (forbidden.count(near) || used.count(near)) {
                continue;
            }

            used.insert(near);
            q.push(near);
        }
    }

    return false;
}

void level_generator_t::generate_path_dfs(point_t current, point_t start, int depth) {
    if (depth == m_grass_count)
        return;

    m_grass_path.push_back(current);
    m_grass_set.insert(current);

    auto near_points = get_near_points(current);
    std::random_shuffle(near_points.begin(), near_points.end());

    for (auto point : near_points) {
        if (point_has_bad_cells(point, 2)) {
            continue;
        }

        if (generate_path_can_find_path(point, start, current)) {
            generate_path_dfs(point, start, depth + 1);
            break;
        }
    }
}

void level_generator_t::generate_path() {
    m_grass_set.clear();
    m_grass_path.clear();

    point_t start {0, 0};
    generate_path_dfs(start, start, 0);
}

int level_generator_t::find_distance(point_t from, point_t to) {
    std::map<point_t, int> result;
    std::queue<point_t> q;
    q.push(from);

    while (!q.empty()) {
        point_t current = q.front();
        q.pop();

        if (current == to) {
            return result[to];
        }

        for (auto near : get_near_points(current)) {
            if (!m_grass_set.count(near) || result.count(near)) {
                continue;
            }

            result[near] = result[current] + 1;
            q.push(near);
        }
    }

    return std::numeric_limits<int>::max();
}

void level_generator_t::relax_path() {
    std::set<point_t> used;
    std::set<point_t> boundarySet;
    std::vector<point_t> boundary;

    used.insert(m_grass_path.begin(), m_grass_path.end());
    boundarySet.insert(m_grass_path.begin(), m_grass_path.end());
    boundary.insert(boundary.end(), m_grass_path.begin(), m_grass_path.end());

    for (int t = 0; t < m_relax_count; t++) {
        while (true) {
            int random_index = (int) (rand() % boundary.size());
            point_t current = boundary[random_index];

            bool found = false;
            for (auto near : get_near_points(current)) {
                if (used.count(near)) continue;

                int currentDistance = find_distance(m_grass_path.front(), m_grass_path.back());
                m_grass_set.insert(near);
                int nextDistnace = find_distance(m_grass_path.front(), m_grass_path.back());

                if (currentDistance == nextDistnace) {
                    found = true;
                    used.insert(near);
                    boundary.push_back(near);
                    boundarySet.insert(near);

                    for (auto n1 : get_near_points(near)) {
                        if (!boundarySet.count(n1)) continue;

                        int count = 0;
                        for (auto n2 : get_near_points(n1)) {
                            if (m_grass_set.count(n2))
                                count++;
                        }

                        if (count == 4) {
                            boundarySet.erase(n1);
                            auto it = std::find(boundary.begin(), boundary.end(), n1);
                            boundary.erase(it);
                        }
                    }

                    break;
                } else {
                    m_grass_set.erase(near);
                }
            }

            if (found) break;
        }
    }
}

void level_generator_t::add_trees() {
    std::set<point_t> pathSet(m_grass_path.begin(), m_grass_path.end());
    std::vector<point_t> grasses(m_grass_set.begin(), m_grass_set.end());

    for (int t = 0; t < m_tree_count; t++) {
        int max_iter = 1000;
        while (max_iter--) {
            int random_index = (int) (rand() % grasses.size());
            point_t current = grasses[random_index];
            bool found = false;

            if (!pathSet.count(current) && !m_tree_set.count(current)) {
                found = true;
                m_tree_set.insert(current);
            }

            if (found) break;
        }
    }
}

void level_generator_t::add_stars() {
    std::set<point_t> pathSet(m_grass_path.begin(), m_grass_path.end());
    std::vector<point_t> grasses(m_grass_set.begin(), m_grass_set.end());

    for (int t = 0; t < m_star_count; t++) {
        int max_iter = 1000;
        while (max_iter--) {
            int random_index = (int) (rand() % grasses.size());
            point_t current = grasses[random_index];
            bool found = false;

            if (!pathSet.count(current) && !m_tree_set.count(current) && !m_star_set.count(current)) {
                found = true;
                m_star_set.insert(current);
            }

            if (found) break;
        }
    }
}

void level_generator_t::solve_level() {
    generate_path();
    relax_path();
    add_trees();
    add_stars();
}

std::vector<point_t> level_generator_t::grasses() const {
    return std::vector<point_t>(m_grass_set.begin(), m_grass_set.end());
}

std::vector<point_t> level_generator_t::trees() const {
    return std::vector<point_t>(m_tree_set.begin(), m_tree_set.end());
}

std::vector<point_t> level_generator_t::stars() const {
    return std::vector<point_t>(m_star_set.begin(), m_star_set.end());
}

void level_generator_t::reset_seed() {
    set_seed(time(nullptr));
}

void level_generator_t::set_seed(int seed) {
    m_seed = seed;
    srand(seed);
}

int level_generator_t::seed() const {
    return m_seed;
}
