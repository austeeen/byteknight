#include "components.hpp"

Frame::Frame(const float dur, const int row, const int indx, sf::Vector2i size):
duration(dur), texture_rect(indx * size.x, row * size.y, size.x, size.y)
{}

AnimRoll::AnimRoll():
row(0), num_frames(0), frame_indx(0), frame_time(0.0f)
{}
AnimRoll::AnimRoll(const int row, const int num_frames, const float dur, sf::Vector2i size):
row(row), num_frames(num_frames), frame_indx(0), frame_time(0.0f)
{
    for (int i = 0; i < num_frames; ++i) {
        frames.push_back(Frame(dur, row, i, size));
    }
}
bool AnimRoll::nextFrame(const float dt)
{
    frame_time += dt;
    if (frames[frame_indx].duration < frame_time) {
        frame_indx = (frame_indx + 1) % num_frames;
        frame_time = 0.0f;
        return true;
    }
    return false;
}
const sf::IntRect AnimRoll::getFrameRect() const
{
    return frames[frame_indx].texture_rect;
}

/**************************************************************************************************/

Component::Component(GameObject* obj): obj(obj)
{}

/**************************************************************************************************/

Animator::Animator(GameObject* obj, sf::Vector2i size):
Component(obj)
{
    animations[animstate::idle] = AnimRoll(IDLE_ROW, IDLE_FRAMES, 0.1f, size);
    animations[animstate::moving] = AnimRoll(MOVING_ROW, MOVING_FRAMES, 0.1f, size);
    cur_animation = animstate::idle;
}
void Animator::setState(animstate new_state)
{
    cur_animation = new_state;
}
bool Animator::nextFrame(const float dt)
{
    return animations[cur_animation].nextFrame(dt);
}
const sf::IntRect Animator::getFrameRect() const
{
    return animations.at(cur_animation).getFrameRect();
}

/**************************************************************************************************/

Sprite::Sprite(GameObject* obj, const sf::Vector2f start_pos, const std::string& img_fp, \
    const sf::IntRect texture_rect):
Component(obj)
{
    img_texture.loadFromFile(img_fp);
    sprite.setTexture(img_texture);
    sprite.setTextureRect(texture_rect);
    sprite.setPosition(start_pos);
}
void Sprite::setTextureRect(sf::IntRect texture_rect, const bool facing_right)
{
    if (!facing_right) {
        texture_rect.left += texture_rect.width;
        texture_rect.width = -texture_rect.width;
    }
    sprite.setTextureRect(texture_rect);
}
void Sprite::render(sf::RenderWindow &window, const sf::Vector2f &pos)
{
    sprite.setPosition(pos);
    window.draw(sprite);
}

/**************************************************************************************************/

Physics::Physics(GameObject* obj, const int speed, const sf::Vector2f start_pos):
Component(obj), speed(50), cur_pos(start_pos), cur_vel(0, 0)
{}
void Physics::move(int dir)
{
    switch(dir) {
        case DIR_UP: { cur_vel.y = -speed; break; }
        case DIR_DOWN: { cur_vel.y = speed; break; }
        case DIR_LEFT: { cur_vel.x = -speed; break; }
        case DIR_RIGHT: { cur_vel.x = speed; break; }
    }
}
void Physics::accelerate(const float dt)
{
    cur_pos.x += cur_vel.x * dt;
    cur_pos.y += cur_vel.y * dt;
    cur_vel.x = 0;
    cur_vel.y = 0;
}
const sf::Vector2f Physics::getPosition() const
{
    return this->cur_pos;
}
