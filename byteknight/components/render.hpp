#ifndef CMP_RENDER_HPP
#define CMP_RENDER_HPP

/* todo eventually might use a component like this but easier to just put this in sprite component
for now

#include "component.hpp"
#include "sprite.hpp"

struct switchtimer {
    float switch_at;
    float cur_dt;
    bool toggle;
};

class cRender: public ObjectComponent
{
public:
    cRender(GameObject *obj);
    ~cRender() override;
    void update(const float dt) override;
    void render(sf::RenderWindow* window) override;
    void flicker();

private:
    switchtimer __flicker;
    cSprite* __sprite;
};
*/
#endif // CMP_RENDER_HPP
