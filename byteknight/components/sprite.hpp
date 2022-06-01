#ifndef CMP_SPRITE_HPP
#define CMP_SPRITE_HPP

#include "component.hpp"

struct switchtimer {
    float switch_at, cur_dt;
    bool toggle, started;
    int num_switches;
    switchtimer(float sw_at);
    void update(const float dt);
};

class cSprite: public ObjectComponent
{
public:
    cSprite(GameObject* obj);
    void create() override;
    void update(const float dt) override;
    void render(sf::RenderWindow* window) override;
    switchtimer& flickerObj();

private:
    switchtimer __flicker;
    sf::Sprite __sprite;
    bt::rect __texture_rect, __current_rect, __collision_rect;
};

#endif // CMP_SPRITE_HPP
