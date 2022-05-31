#ifndef STATES_INSTANCE_H
#define STATES_INSTANCE_H

#include "generic_states.hpp"

class Instance;

template <>
class StartUp<Instance> : public BaseState<Instance>
{
public:
    StartUp(Instance* o);
    virtual void enter() override;
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

template <>
class Running<Instance> : public BaseState<Instance>
{
public:
    Running(Instance* o);
    virtual void enter() override;
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

template <>
class TearDown<Instance> : public BaseState<Instance>
{
public:
    TearDown(Instance* o);
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override;
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

#endif // STATES_INSTANCE_H
