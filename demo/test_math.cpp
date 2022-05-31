#include <iostream>
#include <cstdio>

#include <math/math.hpp>


void test_rect()
{
    SQ::rect a(0, 0, 10, 10);
    std::cout << "a: " << a.tostr() << std::endl;

    std::cout << "a.right = 10" << std::endl;
    a.right = 10;
    std::cout << "a: " << a.tostr() << std::endl;

    std::cout << "a.right = 20" << std::endl;
    a.right = 20;
    std::cout << "a: " << a.tostr() << std::endl;

    std::cout << "a.centerx = 100" << std::endl;
    a.centerx = 100;
    std::cout << "a: " << a.tostr() << std::endl;

    std::cout << "a.height = 5" << std::endl;
    a.height = 5;
    std::cout << "a: " << a.tostr() << std::endl;

    std::cout << "a.width = 20" << std::endl;
    a.width = 20;
    std::cout << "a: " << a.tostr() << std::endl;


    SQ::rect b(15, 15, 30, 30);
    std::cout << "b: " << b.tostr() << std::endl;

    std::cout << "b.left += 10" << std::endl;
    b.left += 10;
    std::cout << "b: " << b.tostr() << std::endl;

    std::cout << "b.width -= 5" << std::endl;
    b.width -= 5;
    std::cout << "b: " << b.tostr() << std::endl;

    std::cout << "b.centery += 10" << std::endl;
    b.centery += 10;
    std::cout << "b: " << b.tostr() << std::endl;
}

void test_coord()
{
    SQ::coord crd(0, 0, 0, 0);
    std::cout << "crd " << crd.tostr() << std::endl;
    SQ::coord crd1(5, 10);
    SQ::coord crd2(42, 10);
    std::cout << "crd1 " << crd1.tostr() << std::endl;
    std::cout << "crd2 " << crd2.tostr() << std::endl;

    SQ::rect rct1 = crd1.torect((float) 8, (float) 8);
    SQ::rect rct2 = crd2.torect((float) 16, (float) 16);
    std::cout << "rct1 " << rct1.tostr() << std::endl;
    std::cout << "rct2 " << rct2.tostr() << std::endl;

    SQ::coord crd3("7,10");
    SQ::coord crd4("56,10,60,50");
    std::cout << "crd3 " << crd3.tostr() << std::endl;
    std::cout << "crd4 " << crd4.tostr() << std::endl;
}

int main()
{
    test_rect();
    // test_coord();
}
