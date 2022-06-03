#ifndef CAT_HPP
#define CAT_HPP

#include "common.hpp"
#include "components.hpp"

class State
{
public:
    State(GameObject* obj);
    virtual void enter() = 0;
    virtual void next() = 0;
    virtual void exit() = 0;

protected:
    GameObject* obj;
};

class Idle: public State
{
public:
    Idle(GameObject* obj);

};

class Move: public State
{
public:
    Move(GameObject* obj);

};

class Jump: public State
{
public:
    Jump(GameObject* obj);

};


class GameObject
{
public:
    GameObject(const sf::Vector2f start_pos, const std::string img_fp, const sf::IntRect texture_rect);
    void setUp();
    void move(int dir);
    void update(const float dt);
    void lateUpdate();
    void render(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;

private:
    bool facing_right;
    sf::Vector2i size;
    const sf::Vector2f start_pos;
    Sprite* sprite;
    Animator* animator;
    Physics* physics;
};

#endif // CAT_HPP
