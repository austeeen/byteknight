#ifndef STATES_INSTANCE_H
#define STATES_INSTANCE_H

#include "generic_states.hpp"

namespace bt {
    class Instance;
}

template <>
class StartUp<bt::Instance> : public BaseState<bt::Instance>
{
public:
    StartUp(bt::Instance* o);
    virtual void enter() override;
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

template <>
class Running<bt::Instance> : public BaseState<bt::Instance>
{
public:
    Running(bt::Instance* o);
    virtual void enter() override;
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

template <>
class TearDown<bt::Instance> : public BaseState<bt::Instance>
{
public:
    TearDown(bt::Instance* o);
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override;
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

#endif // STATES_INSTANCE_H
