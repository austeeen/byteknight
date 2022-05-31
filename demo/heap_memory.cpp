#include <iostream>
#include <cstdio>
#include <vector>

template<class T> inline void destroy(T*& p) { delete p; p = nullptr; }

struct val
{
    float mv;
    val(float v): mv(v) {};
};


val* make_val(int i)
{
    val *v = new val((float)i);
    return v;
}


int main()
{
    std::vector<val*> allvals;

    for (int i = 0; i < 5; i++ ) {
        allvals.push_back(make_val(i));
    }

    for (auto v : allvals) {
        std::cout << v->mv << std::endl;
    }

    auto active = &allvals.back();

    for (auto v : allvals) {
        std::cout << "destruct: " << v->mv << std::endl;
        destroy(v);
    }
    allvals.clear();

    if (active) {
        std::cout << "active: " << (*active)->mv << std::endl;
    }
    destroy(active);
}
