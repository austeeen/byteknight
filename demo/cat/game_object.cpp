#include "game_object.hpp"

GameObject::GameObject(const sf::Vector2f start_pos, const std::string img_fp,
    const sf::IntRect texture_rect):
    facing_right(true), size(texture_rect.width, texture_rect.height),
    start_pos(start_pos)
{
    this->sprite = new Sprite(this, start_pos, img_fp, texture_rect);
    this->animator = new Animator(this, size);
    this->physics = new Physics(this, 50, start_pos);
}
sf::Vector2f GameObject::getPosition() const
{
    return this->physics->getPosition();
}
void GameObject::setUp()
{

}
void GameObject::move(int dir)
{
    switch(dir) {
        case DIR_LEFT: { facing_right = false; break; }
        case DIR_RIGHT: { facing_right = true;  break; }
    }
    this->physics->move(dir);
    animator->setState(animstate::moving);
}
void GameObject::update(const float dt)
{
    if (animator->nextFrame(dt)) {
        sprite->setTextureRect(animator->getFrameRect(), facing_right);
    }
    this->physics->accelerate(dt);
    animator->setState(animstate::idle);
}
void GameObject::lateUpdate()
{
    // collision check
}
void GameObject::render(sf::RenderWindow &window)
{
    sprite->render(window, this->physics->getPosition());
}
