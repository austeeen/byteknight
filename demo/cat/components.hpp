#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include "common.hpp"
#include "typedef.hpp"

struct Frame
{
    Frame(const float dur, const int row, const int indx, sf::Vector2i size);
    const float duration;
    const sf::IntRect texture_rect;
};

class AnimRoll
{
public:
    AnimRoll();
    AnimRoll(const int row, const int num_frames, const float dur, sf::Vector2i size);
    bool nextFrame(const float dt);
    const sf::IntRect getFrameRect() const;

private:
    int row, num_frames, frame_indx;
    float frame_time;
    std::vector<Frame> frames;
};

/**************************************************************************************************/

class Component
{
public:
    Component(GameObject* obj);

public:
    GameObject* obj;
};

/**************************************************************************************************/

class Animator: public Component
{
public:
    Animator(GameObject* obj, sf::Vector2i size);
    void setState(animstate new_state);
    bool nextFrame(const float dt);
    const sf::IntRect getFrameRect() const;

private:
    std::map<animstate, AnimRoll> animations;
    animstate cur_animation;
};

/**************************************************************************************************/

class Sprite: public Component
{
public:
    Sprite(GameObject* obj, const sf::Vector2f start_pos, const std::string& img_fp,
        const sf::IntRect texture_rect);
    void setTextureRect(const sf::IntRect texture_rect, const bool facing_rect);
    void render(sf::RenderWindow &window, const sf::Vector2f &pos);

private:
    sf::Texture img_texture;
    sf::Sprite sprite;
};

/**************************************************************************************************/

class Physics: public Component
{
public:
    Physics(GameObject* obj, const int speed, const sf::Vector2f start_pos);
    void move(int dir);
    void accelerate(const float dt);
    const sf::Vector2f getPosition() const;

private:
    int speed;
    sf::Vector2f cur_pos;
    sf::Vector2f cur_vel;
};

#endif // ANIMATOR_HPP
