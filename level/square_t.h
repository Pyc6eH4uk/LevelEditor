//
// Created by gdhsnlvr on 02.10.17.
//

#ifndef CROSSROAD_LEVEL_CELL_H
#define CROSSROAD_LEVEL_CELL_H


class square_t {
protected:
    int m_x, m_y, m_w, m_h;

public:
    square_t();
    square_t(int x, int y, int w, int h);

    int x() const;
    int y() const;
    int w() const;
    int h() const;

    void set_x(int x);
    void set_y(int y);
    void set_w(int w);
    void set_h(int h);

    bool intersect(const square_t &s) const;
};


#endif //CROSSROAD_LEVEL_CELL_H
