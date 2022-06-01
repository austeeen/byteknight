#ifndef CMP_PHYSICS_HPP
#define CMP_PHYSICS_HPP

#include "component.hpp"

class cPhysics: public ObjectComponent
{
public:
    cPhysics(GameObject* obj) : ObjectComponent(obj),
    sign{0, 0},
    target{0.0, 0.0}, dist{0.0, 0.0}, vel{0.0, 0.0},
    acl(0.0), max_spd(0.0), wait(0.3), _dt(0.0) {};
    void create() override;
    void update(const float dt) override;
    bool setDestination(Tile* tile);
    bool isMoving() { return vel[bt::X] || vel[bt::Y]; };

private:
    void __setNewTarget(const sf::Vector2f new_target);
    void __updateAxis(const int ax, const float dt);
    template <typename T> int sgn(const T val) { return (T(0) < val) - (val < T(0)); }
    int sign[2];
    float target[2], dist[2], vel[2], acl, max_spd, wait, _dt;
    std::vector<sf::Vector2f> move_queue;
};

#endif // CMP_PHYSICS_HPP
