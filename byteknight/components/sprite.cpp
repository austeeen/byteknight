#include "sprite.hpp"
#include "objects/game_object.hpp"

switchtimer::switchtimer(float sw_at):
switch_at(sw_at), cur_dt(0.f), toggle(false), started(false), num_switches(0)
{}
void switchtimer::update(const float dt)
{
    cur_dt += dt;
    if(cur_dt >= switch_at) {
        num_switches++;
        toggle = !toggle;
        cur_dt = 0.f;
    }
}

cSprite::cSprite(GameObject *obj):
ObjectComponent(obj), __flicker(0.1f)
{}
void cSprite::create()
{
    __sprite.setTexture(_ast->img_texture);
    __texture_rect = _ast->texture_rect;
    __collision_rect = _ast->collision_rect;
    __current_rect = __texture_rect;
    __sprite.setTextureRect(sf::IntRect(__texture_rect));
}
void cSprite::update(float dt)
{
    if (__flicker.started) {
        __flicker.update(dt);
    }
}
switchtimer& cSprite::flickerObj()
{
    return this->__flicker;
}
void cSprite::render(sf::RenderWindow* window)
{
    if (!__flicker.toggle && __flicker.started) {
        return;
    }
    __sprite.setPosition(_obj->rect.pos);
    window->draw(__sprite);
}
