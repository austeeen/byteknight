#include <iostream>
#include <cstdio>

struct data {
    int num;
};

struct val
{
    float mv;
    val(float v): mv(v) {};
};

struct point
{
    data d;
    val *x, *y;
    point(val *x, val *y): x(x), y(y) {};
    friend std::ostream& operator<<(std::ostream& os, const point& p)
    {
        std::cout << "(" << p.x->mv << ", " << p.y->mv << ")";
        return os;
    }
    data* getdata() { return &d; }
};


class rect
{
public:
    val cx, cy;
    point cntr;
    rect() : cx(6.0), cy(5.0), cntr(&cx, &cy)
    {
        cntr.d.num = 1;
    };
    data* getdata() { return cntr.getdata(); }
};

int main()
{
    /*
    std::cout << center << std::endl;
    centerx.mv = 4.0;
    std::cout << center << std::endl;
    */

    rect r;
    data md = *r.getdata();

    std::cout << md.num << std::endl;

}
