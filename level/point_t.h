//
// Created by gdhsnlvr on 02.10.17.
//

#ifndef CROSSROAD_LEVEL_POINT_T_H
#define CROSSROAD_LEVEL_POINT_T_H


#include <vector>

class point_t {
protected:
    int m_x;
    int m_y;

public:
    point_t();
    point_t(int x, int y);

    int x() const;
    int y() const;

    void set_x(int x);
    void set_y(int y);

    int distance(const point_t &p) const;
    std::vector<point_t> near() const;

    point_t operator + (const point_t &p) const;
    point_t operator - (const point_t &p) const;

    bool operator == (const point_t &p) const;
    bool operator < (const point_t &p) const;
};


#endif //CROSSROAD_LEVEL_POINT_T_H
