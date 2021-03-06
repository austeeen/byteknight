#include "physics.hpp"
#include "objects/tile_object.hpp"
#include "objects/game_object.hpp"

void cPhysics::create()
{
    max_spd = _ast->speed;
    acl = _ast->acl;
}
void cPhysics::update(const float dt)
{
    _dt += dt;
    if (move_queue.size()) {
        __setNewTarget(move_queue.back());
        move_queue.pop_back();
    }
    if (!sign[bt::X] && !sign[bt::Y]) { return; }

    if (sign[bt::X]) { __updateAxis(bt::X, dt); }
    if (sign[bt::Y]) { __updateAxis(bt::Y, dt); }
}
bool cPhysics::setDestination(Tile* tile)
{
    if (!tile || _dt <= wait) {
        return false;
    }
    move_queue.push_back(tile->getCenter());
    _dt = 0;
    return true;
}
void cPhysics::__setNewTarget(const sf::Vector2f new_target)
{
    target[bt::X] = new_target.x;
    target[bt::Y] = new_target.y;

    // set axis directional signs ( -1, 0, 1 )
    sign[bt::X] = sgn(target[bt::X] - _obj->rect.centerx);
    sign[bt::Y] = sgn(target[bt::Y] - _obj->rect.centery);
}
void cPhysics::__updateAxis(const int ax, const float dt)
{
    this->dist[ax] = this->target[ax] - _obj->rect.center[ax];
    if (sgn(this->dist[ax]) != this->sign[ax]) {
        this->_obj->rect.center[ax] = this->target[ax];
        this->sign[ax] = 0;
        this->dist[ax] = 0.0;
        this->vel[ax] = 0.0;
        return;
    }
    else if (this->vel[ax] < this->max_spd) {
        this->vel[ax] += this->acl * dt;
        if (this->vel[ax] > this->max_spd)
            this->vel[ax] = this->max_spd;
    }
    this->_obj->rect.center[ax] += vel[ax] * sign[ax];
}
