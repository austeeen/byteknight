#ifndef SQR_WINDOW_HPP
#define SQR_WINDOW_HPP

#include <SFML/Graphics.hpp>

class SqrWindow
{
public:
    SqrWindow();
    SqrWindow(const sf::Vector2u size, const std::string title);

    bool poll(sf::Event& e);
    void close();
    void clear();
    void display();
    bool alive() const;
    sf::Vector2u getSize() const;

    void draw(const sf::RenderTexture &rt, const sf::Vector2f& pos);
    void draw(const sf::Drawable &render_object);
    void draw(const sf::Drawable &render_object, const sf::RenderStates &states);
    void draw(const sf::Drawable &render_object, const sf::Transform &xform);
    void draw(const sf::FloatRect& r);
    void draw(const sf::Vector2f& center, const int r);
    void draw(const sf::VertexArray &verts, const sf::RenderStates &render_texture);

private:
    void __setIntrinsics();
    sf::RenderWindow __window;
};

#endif // SQR_WINDOW_HPP
