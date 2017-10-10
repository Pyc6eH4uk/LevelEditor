//
// Created by gdhsnlvr on 02.10.17.
//

#include <cmath>
#include "point_t.h"

point_t::point_t()
    : m_x(0), m_y(0)
{
}

point_t::point_t(int x, int y)
    : m_x(x), m_y(y)
{
}

int point_t::x() const {
    return m_x;
}

int point_t::y() const {
    return m_y;
}

void point_t::set_x(int x) {
    m_x = x;
}

void point_t::set_y(int y) {
    m_y = y;
}

int point_t::distance(const point_t &p) const {
    return (int) (std::abs(m_x - p.m_x) + std::abs(m_y - p.m_y));
}

point_t point_t::operator+(const point_t &p) const {
    return { m_x + p.m_x, m_y + p.m_y };
}

point_t point_t::operator-(const point_t &p) const {
    return { m_x + p.m_x, m_y + p.m_y };
}

bool point_t::operator==(const point_t &p) const {
    return m_x == p.m_x && m_y == p.m_y;
}

bool point_t::operator<(const point_t &p) const {
    return m_y < p.m_y || (m_y == p.m_y && m_x < p.m_x);
}

std::vector<point_t> point_t::near() const {
    static std::vector<point_t> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    std::vector<point_t> result;
    for (auto dir : directions) {
        result.push_back(*this + dir);
    }
    return result;
}
