//
// Created by gdhsnlvr on 02.10.17.
//

#include "square_t.h"

square_t::square_t()
    : m_x(0), m_y(0), m_w(0), m_h(0)
{

}

square_t::square_t(int x, int y, int w, int h)
        : m_x(x), m_y(y), m_w(w), m_h(h)
{

}

int square_t::x() const {
    return m_x;
}

int square_t::y() const {
    return m_y;
}

int square_t::w() const {
    return m_w;
}

int square_t::h() const {
    return m_h;
}

void square_t::set_x(int x) {
    m_x = x;
}

void square_t::set_y(int y) {
    m_y = y;
}

void square_t::set_w(int w) {
    m_w = w;
}

void square_t::set_h(int h) {
    m_h = h;
}

bool square_t::intersect(const square_t &s) const {
    return s.m_x >= m_x + m_w || s.m_x + s.m_w <= m_x ||
            s.m_y >= m_y + m_h || s.m_y + s.m_h <= m_y;
}
