#include "math.hpp"

namespace SQ {

/**************************************************************************************************/
/* LINE */

line::line() :
line(0.0, 0.0)
{};
line::line(float a, float b) :
a(a), b(b)
{};
line::line(sf::Vector2f &v) :
line(v.x, v.y)
{};
line::line(const sf::Vector2f &v) :
line(v.x, v.y)
{};
line line::clip(const float a, const float b, const float u, const float v)
{
    if (u > a) {
        if (b > v) {
            return line(u, v);
        }
        return line(u, (b - u));
    } else {
        if (v > b) {
            return line(a, b);
        }
        return line(a, (v - a));
    }
}
line& line::clip(const float u, const float v)
{
    if (u > a) {
        if (b > v) {
            a = u;
            b = v;
        } else {
            a = u;
            b = b - u;
        }
    } else {
        if (v <= b)
            b = v - a;
    }
    return *this;
}

/**************************************************************************************************/
/* COORD */

coord::coord() : i(0), cols(0), x(0), y(0)
{};
coord::coord(const int x, const int y, const int i, const int cols) : i(i), cols(cols), x(x), y(y)
{};
coord::coord(const int i, const int cols) : i(i), cols(cols), x(i % cols), y(i / cols)
{};
coord::coord(const std::string &str) : i(0), cols(0), x(0), y(0)
{
    std::vector<int> v;
    split(str, ',', v);
    if (v.size() == 2) {
        i = v[0];
        cols = v[1];
        x = i % cols;
        y = i / cols;
    }
    else if (v.size() == 4) {
        i = v[0];
        cols = v[1];
        x = v[2];
        y = v[3];
    }
}
coord::coord(const std::string &str, const int i, const int cols) : i(0), cols(cols), x(0), y(0)
{
    std::vector<int> v;
    split(str, ',', v);
    if (v.size() == 2) {
        x = v[0];
        y = v[1];
        this->i = y * cols + x;
    }
}
coord::coord(const rect &r) : coord((int) floor(r.left / r.width), (int) floor(r.top / r.height))
{}
coord::coord(const rect &r, const int w, const int h) : coord((int) floor(r.left / w), (int) floor(r.top / h))
{}
coord::coord(const rect &r, const sf::Vector2i &v) : coord((int) floor(r.left / v.x), (int) floor(r.top / v.y))
{}

rect coord::torect(const float w, const float h) {
    return rect((float) x * w, (float) y * h, w, h);
}
rect coord::torect(const sf::Vector2f &v) {
    return rect((float) x * v.x, (float) y * v.y, v.x, v.y);
}
rect coord::torect(const SQ::rect &r) {
    return rect((float) x * r.width, (float) y * r.height, r.width, r.height);
}
const std::string coord::tostr() const {
    return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(i) + "," + std::to_string(cols);
}

/**************************************************************************************************/
/* VAL */
rect::val::val(rect *r, const float v, void(rect::*_m)(const float)): r(r), mv(v), __move(_m)
{};
rect::val& rect::val::operator=(const val& v)
{
    (r->*__move)((float)v - mv);
    set((float)v);
    return *this;
}
rect::val& rect::val::operator=(const float v)
{
    (r->*__move)(v - mv);
    set(v);
    return *this;
}
rect::val& rect::val::operator+=(const float dv)
{
    (r->*__move)(dv);
    move(dv);
    return *this;
}
rect::val& rect::val::operator-=(const float dv)
{
    (r->*__move)(-dv);
    move(-dv);
    return *this;
}
rect::val::operator float() const
{
    return mv;
}
std::string rect::val::tostr() const
{
    return std::to_string(mv);
}
void rect::val::move(const float d)
{
    mv += d;
}
void rect::val::set(const float d)
{
    mv = d;
}

/* POINT */

rect::point::point(val *x, val *y):
xy{x, y}, x(x), y(y)
{}
rect::point& rect::point::operator=(const rect::point& v)
{
    *x = *v.x;
    *y = *v.y;
    return *this;
}
std::string rect::point::tostr() const
{
    return "(" + x->tostr() + ", " + y->tostr() + ")";
}
rect::point::operator sf::Vector2f() const
{
    return sf::Vector2f((float) *x, (float) *y);
}
rect::val& rect::point::operator[](const int i) const
{
    return *xy[i];
}
/* RECT */
rect::rect(): rect(0.f, 0.f, 0.f, 0.f)
{}
rect::rect(const float x, const float y, const float w, const float h) :
left   (this, x,           &rect::__sl ),
right  (this, x + w,       &rect::__sr ),
top    (this, y,           &rect::__sb ),
bottom (this, y + h,       &rect::__st ),
centerx(this, x + (w / 2), &rect::__scx),
centery(this, y + (h / 2), &rect::__scy),
width  (this, w,           &rect::__sw ),
height (this, h,           &rect::__sh ),
center(&centerx, &centery),
pos(&left, &top),
size(&width, &height)
{}
rect::rect(const sf::FloatRect& fr) :
rect(fr.top, fr.left, fr.width, fr.height)
{}
rect::rect(const sf::Vector2f &p, const sf::Vector2f &s) :
rect(p.x, p.y, s.x, s.y)
{};
rect::rect(const std::vector<float> &v) :
rect(v[0], v[1], v[2], v[3])
{};
rect::rect(const std::string &str) :
rect(split4(str, ','))
{}
rect::rect(const coord &c, const float w, const float h) :
rect((c.i % c.cols) * w, (c.i / c.cols) * h, w, h)
{}
rect::rect(const coord &c, const sf::Vector2f &s) :
rect((c.i % c.cols) * s.x, (c.i / c.cols) * s.y, s.x, s.y)
{}
rect::rect(const rect& r) :
left   (this, (float)r.left,                         &rect::__sl ),
right  (this, (float)r.left + (float)r.width,        &rect::__sr ),
top    (this, (float)r.top,                          &rect::__sb ),
bottom (this, (float)r.top  + (float)r.height,       &rect::__st ),
centerx(this, (float)r.left + ((float)r.width / 2),  &rect::__scx),
centery(this, (float)r.top  + ((float)r.height / 2), &rect::__scy),
width  (this, (float)r.width,                        &rect::__sw ),
height (this, (float)r.height,                       &rect::__sh ),
center(&centerx, &centery),
pos(&left, &top),
size(&width, &height)
{}
rect& rect::operator=(const rect &r)
{
    left.set(r.left);
    right.set(r.right);
    top.set(r.top);
    bottom.set(r.bottom);
    centerx.set(r.centerx);
    centery.set(r.centery);
    width.set(r.width);
    height.set(r.height);
    return *this;
}
void rect::setPosition(const sf::Vector2f& p)
{
    this->left = p.x;
    this->top = p.y;
}
void rect::setPosition(const coord& c)
{
    this->left = c.x * (float) this->width;
    this->top = c.y * (float) this->height;
}
void rect::setPosition(const float x, const float y)
{
    this->left = x;
    this->top = y;
}
void rect::setSize(const sf::Vector2f& s)
{
    this->width = s.x;
    this->height = s.y;
}
void rect::setSize(const float x, const float y)
{
    this->width = x;
    this->height = y;
}
void rect::setCenter(const sf::Vector2f& c)
{
    this->centerx = c.x;
    this->centery = c.y;
}
void rect::setCenter(const coord& c)
{
    this->centerx = (c.x * (float) this->width) + (float) this->width / 2;
    this->centery = (c.y * (float) this->height) + (float) this->height / 2;
}
void rect::setCenter(const float x, const float y)
{
    this->centerx = x;
    this->centery = y;
}
sf::Vector2f rect::getSize() const
{
    return sf::Vector2f(width, height);
}
sf::Vector2f rect::getPosition() const
{
    return sf::Vector2f(left, top);
}
rect::operator sf::FloatRect() const
{
    return sf::FloatRect(left, top, width, height);
}
rect::operator sf::IntRect() const
{
    return sf::IntRect(left, top, width, height);
}
coord rect::tocoord(const int cols)
{
    return coord((int) floor(top / height) * cols + (int) floor(left / width), cols);
}
coord rect::tocoord(const int cols, const float w, const float h)
{
    return coord((int) floor(top / h) * cols + (int) floor(left / w), cols);
}
coord rect::tocoord(const int cols, const sf::Vector2f s)
{
    return coord((int) floor(top / s.y) * cols + (int) floor(left / s.x), cols);
}
std::string rect::tostr() const
{
    return "[" + left.tostr() + ", " + top.tostr() + ", " + right.tostr() + ", " + bottom.tostr() + "], (" + width.tostr() + ", " + height.tostr() + ")";
}
rect rect::clip(const rect &a, const rect &b)
{
    float dx = 0.0, dy = 0.0;

    if (b.left > a.left) {
        dx = b.left - a.right; // dy < 0
    } else {
        dx = b.right - a.left; // dx > 0
    }
    if (b.top > a.top) {
        dy = b.top - a.bottom; // dy < 0
    } else {
        dy = b.bottom - a.top; // dy > 0
    }
    return rect(0.0, 0.0, dx, dy);
}
rect rect::clip(const rect &rect) const
{
    return rect::clip(*this, rect);
}
const bool rect::exists() const
{
    return !(this->left == 0 && this->top == 0 && this->right == 0 && this->bottom == 0);
}
/**************************************************************************************************/

const void move(rect& r, const coord& c)
{
    r.left = c.x * r.width;
    r.top = c.y * r.height;
}
const void move(sf::FloatRect& r, const coord& c)
{
    r.left = c.x * r.width;
    r.top = c.y * r.height;
}

}
