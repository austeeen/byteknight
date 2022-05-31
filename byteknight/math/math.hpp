#ifndef MTH_MATH_H
#define MTH_MATH_H

#include <cstdint>
#include "utils/util.hpp"

namespace SQ
{
    const int X = 0;
    const int Y = 1;
    typedef const uint8_t dir;
    enum dir4: dir { up, right, down, left, none };
    enum dir8: dir { ul, u, ur, r, dr, d, dl, l };

    typedef std::vector<dir4> moveset;

    const std::map<const char, dir4> C2DIR4 {
        {'U', dir4::up}, {'D', dir4::down}, {'L', dir4::left}, {'R', dir4::right},
        {'u', dir4::up}, {'d', dir4::down}, {'l', dir4::left}, {'r', dir4::right}
    };

    class rect;

    class line
    {
    public:
        float a, b;

        line();
        line(float a, float b);
        line(sf::Vector2f &v);
        line(const sf::Vector2f &v);

        static line clip(const float a, const float b, const float u, const float v);
        line& clip(const float u, const float v);
    };

    class coord
    {
    public:
        int i, cols, x, y;

        coord();
        coord(const int x, const int y, const int i, const int cols);
        coord(const int i, const int cols);
        coord(const std::string &str);
        coord(const std::string &str, const int i, const int cols);
        coord(const rect &r);
        coord(const rect &r, const int w, const int h);
        coord(const rect &r, const sf::Vector2i &v);
        rect torect(const float w, const float h);
        rect torect(const sf::Vector2f &v);
        rect torect(const SQ::rect &r);
        const std::string tostr() const;
    };

    class rect
    {
    public:

        struct val
        {
        private:
            rect *r;
            float mv;
            void(rect::*__move)(const float);
        public:
            val(rect *r, const float v, void(rect::*_m)(const float));
            val& operator=(const val& v);
            val& operator=(const float v);
            val& operator+=(const float dv);
            val& operator-=(const float dv);
            operator float() const;
            std::string tostr() const;
            void move(const float d);
            void set(const float d);
        };

        struct point
        {
        private:
            val* xy[2];
            val *x, *y;
        public:
            point(val *x, val *y);
            point& operator=(const point& v);
            template <class ITGR>
            point& operator=(const sf::Vector2<ITGR>& v) {
                *x = (float) v.x;
                *y = (float) v.y;
                return *this;
            };

            operator sf::Vector2f() const;
            std::string tostr() const;
            val& operator[](const int i) const;
        };

        val left, right, top, bottom, centerx, centery, width, height;
        point center, pos, size;

        rect();
        rect(const float x, const float y, const float w, const float h);
        rect(const sf::FloatRect& fr);
        rect(const sf::Vector2f &p, const sf::Vector2f &s);
        rect(const std::string &str);
        rect(const coord &c, const float w, const float h);
        rect(const coord &c, const sf::Vector2f &s);
        rect(const std::vector<float> &v);
        rect(const rect& r);

        rect& operator=(const rect &r);

        inline void move(float *vel) {
            this->left += (float)vel[SQ::X];
            this->top  += (float)vel[SQ::Y];
        }

        inline void move(float x, float y) {
            this->left += x;
            this->top  += y;
        }

        inline void shrink(int s) {
            this->width -= s;
            this->height -= s;
        }

        void setPosition(const sf::Vector2f& p);
        void setPosition(const coord& c);
        void setPosition(const float x, const float y);

        void setSize(const sf::Vector2f& s);
        void setSize(const float x, const float y);

        void setCenter(const sf::Vector2f& c);
        void setCenter(const coord& c);
        void setCenter(const float x, const float y);

        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;

        operator sf::FloatRect() const;
        operator sf::IntRect() const;

        coord tocoord(const int cols);
        coord tocoord(const int cols, const float w, const float h);
        coord tocoord(const int cols, const sf::Vector2f s);
        std::string tostr() const;

        static rect clip(const rect &a, const rect &b);
        rect clip(const rect &rect) const;

        const bool exists() const;

    private:
        void __sl(const float dx) { right.move(dx);  centerx.move(dx); }
        void __sr(const float dx) { left.move(dx);   centerx.move(dx); }
        void __st(const float dy) { bottom.move(dy); centery.move(dy); }
        void __sb(const float dy) { top.move(dy);    centery.move(dy); }

        void __scx(const float dx){ left.move(dx);     right.move(dx); }
        void __scy(const float dy){ top.move(dy);     bottom.move(dy); }

        void __sw(const float dw) { right.move(dw);  centerx.move(dw / 2); }
        void __sh(const float dh) { bottom.move(dh); centery.move(dh / 2); }
    };
    const void move(rect& r, const coord& c);
    const void move(sf::FloatRect& r, const coord& c);

} // namespace SQ


#endif // MTH_MATH_H
