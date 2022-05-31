#ifndef UTL_DIRECTIONAL_H
#define UTL_DIRECTIONAL_H

/*
#include <SFML/Graphics.hpp>
#include <math.h>

// may not need
template < class T>
class Position
{
public:
    T x, y;
    Position(): x(0.0), y(0.0) {}
    Position(T x, T y): x(x), y(y) {}
    inline operator bool() const { return (x != 0) || (y != 0); }

    inline bool operator==(const Position<T>& v){ return (x == v.x) && (y == v.y); }
    inline bool operator!=(const Position<T>& v){ return !(this == v); }

    inline Position<T> operator++(T) const  { x++; y++; return *this; } // requires <T> = int
    inline Position<T> operator--(T) const  { x++; y++; return *this; } // requires <T> = int
    inline Position<T> operator+(const T v) const { return Position(x + v, y + v); }
    inline Position<T> operator-(const T v) const { return Position(x - v, y - v); }
    inline Position<T>& operator+=(const Position<T>& rhs) const { x += rhs->x; y += rhs->y; return *this; }
    inline Position<T>& operator-=(const Position<T>& rhs) const { x -= rhs->x; y -= rhs->y; return *this; }

    template < class R >
    inline Position<T> operator+(const Position<R> &v) const { return XY(x + v.x, y + v.y); }
    template < class R >
    inline Position<T> operator-(const Position<R> &v) const { return XY(x - v.x, y - v.y); }

    inline bool operator< (const Position<T>& o) const { return (this.x <= o.x) || (this.y <= o.y); }
    inline bool operator> (const Position<T>& o) const { return o < *this; }
    inline bool operator<=(const Position<T>& o) const { return !(*this > o); }
    inline bool operator>=(const Position<T>& o) const { return !(*this < o); }

    inline T& operator[](std::size_t idx) {
        if (idx == 0)
            return x;
        if (idx == 1)
            return y;
        throw std::invalid_argument(std::string(idx));
    }
    inline const T& operator[](std::size_t idx) const {
        if (idx == 0)
            return x;
        if (idx == 1)
            return y;
        throw std::invalid_argument(std::string(idx));
    }
    inline T& operator[](char idx) {
        if (idx == 'x')
            return x;
        if (idx == 'y')
            return y;
        throw std::invalid_argument(std::string(idx));
    }
    inline const T& operator[](char idx) const {
        if (idx == 'x')
            return x;
        if (idx == 'y')
            return y;
        throw std::invalid_argument(std::string(idx));
    }
};

template < class T>
Position<T> abs(Position<T> v) { return Position<T>(fabs(v.x), fabs(v.y)); };

template <class T>
Position<T> abs(T x, T y) { return Position<T>(fabs(x), fabs(y)); };


class Vector
{
public:
    Vector(): max(0.0), acl(0.0), vx(0.0), vy(0.0), sx(0), sy(0) {};

    template <typename T>
    void sgn(const T x, const T y)
    {
        sx = (T(0) < x) - (x < T(0));
        sy = (T(0) < y) - (y < T(0));
    }

    void update(const float dt)
    {
        vx += (vx * dt) * sx;
        vy += (vy * dt) * sy;
        if (fabs(vx) > max)
            vx = max * sx;
        if (fabs(vy) > max)
            vy = max * sy;
    }
    bool isMoving();

private:
    float max, acl, vx, vy;
    int sx, sy;
};
*/

#endif // UTL_DIRECTIONAL_H
