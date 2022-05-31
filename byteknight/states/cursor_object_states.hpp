#ifndef STATES_CURSOR_H
#define STATES_CURSOR_H

#include "generic_states.hpp"

class Cursor;

template <>
class Idle<Cursor> : public BaseState<Cursor>
{
public:
    Idle(Cursor* o);
    virtual void enter() override;
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

template <>
class Selected<Cursor> : public BaseState<Cursor>
{
public:
    Selected(Cursor* o);
    virtual void enter() override;
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

#endif // STATES_CURSOR_H
