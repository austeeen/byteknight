#include "window.hpp"

namespace bt
{
ByteWindow::ByteWindow():
ByteWindow(sf::Vector2u(800, 600), "NO TITLE")
{}
ByteWindow::ByteWindow(const sf::Vector2u size, const std::string title):
__window(sf::VideoMode(size.x, size.y), title)
{
    __setIntrinsics();
}
void ByteWindow::__setIntrinsics()
{
    __window.setVerticalSyncEnabled(true);
    __window.setKeyRepeatEnabled(false);
}
bool ByteWindow::poll(sf::Event &e)
{
    return __window.pollEvent(e);
}
void ByteWindow::close() {
    __window.close();
}
void ByteWindow::clear() {
    __window.clear();
}
void ByteWindow::display() {
    __window.display();
}
bool ByteWindow::alive() const {
    return __window.isOpen();
}
sf::Vector2u ByteWindow::getSize() const {
    return __window.getSize();
};
void ByteWindow::draw(const sf::RenderTexture &rt, const sf::Vector2f& pos) {
    __window.draw(sf::Sprite(rt.getTexture()));
}
void ByteWindow::draw(const sf::Drawable &render_object) {
    __window.draw(render_object);
}
void ByteWindow::draw(const sf::Drawable &render_object, const sf::RenderStates &states) {
    __window.draw(render_object, states);
}
void ByteWindow::draw(const sf::Drawable &render_object, const sf::Transform &xform) {
    __window.draw(render_object, xform);
}
void ByteWindow::draw(const sf::VertexArray &verts, const sf::RenderStates &render_texture) {
    __window.draw(verts, render_texture);
}
void ByteWindow::draw(const sf::FloatRect& r)
{
    sf::RectangleShape rectangle(sf::Vector2f(r.width, r.height));
    rectangle.setPosition(r.left, r.top);
    rectangle.setOutlineColor(sf::Color::Blue);
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(sf::Color::Transparent);
    __window.draw(rectangle);
}
void ByteWindow::draw(const sf::Vector2f& center, const int r)
{
    sf::CircleShape circle(r);
    circle.setPosition(center.x - r, center.y - r); // default origin is (0, 0) -- even for circles...
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(2);
    circle.setFillColor(sf::Color::Transparent);
    __window.draw(circle);
}
}
