#ifndef STATES_GENERIC_H
#define STATES_GENERIC_H

#include "common.hpp"
#include "datacore/event_core.hpp"

enum class statekey { inactive, idle, selected, moving, killed, startup, running, teardown };

template <class T>
class BaseState
{
public:
    BaseState(T* o): _obj(o) {};
    virtual ~BaseState() {};
    virtual void enter() = 0;
    virtual void enter(sptr<SquareEvent> e) = 0;
    virtual void next(sptr<SquareEvent> e) = 0;
    virtual void exit() = 0;

    virtual void update(const float dt) = 0;
    virtual void render(sf::RenderWindow* window) = 0;

protected:
    T* _obj;
};

template <class T>
class Inactive : public BaseState<T>
{
public:
    Inactive(T* o): BaseState<T>(o) {};
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override {};
    virtual void exit() override {};

    virtual void update(const float dt) override {};
    virtual void render(sf::RenderWindow* window) override {};
};

template <class T>
class Idle : public BaseState<T>
{
public:
    Idle(T* o): BaseState<T>(o) {};
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override {};
    virtual void exit() override {};

    virtual void update(const float dt) override {};
    virtual void render(sf::RenderWindow* window) override {};
};

template <class T>
class Selected : public BaseState<T>
{
public:
    Selected(T* o): BaseState<T>(o) {};
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override {};
    virtual void exit() override {};

    virtual void update(const float dt) override {};
    virtual void render(sf::RenderWindow* window) override {};
};

template <class T>
class Moving : public BaseState<T>
{
public:
    Moving(T* o): BaseState<T>(o) {};
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override {};
    virtual void exit() override {};

    virtual void update(const float dt) override {};
    virtual void render(sf::RenderWindow* window) override {};
};

template <class T>
class Killed : public BaseState<T>
{
public:
    Killed(T* o): BaseState<T>(o) {};
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override {};
    virtual void exit() override {};

    virtual void update(const float dt) override {};
    virtual void render(sf::RenderWindow* window) override {};
};

template <class T>
class StartUp : public BaseState<T>
{
public:
    StartUp(T* o): BaseState<T>(o) {};
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override {};
    virtual void exit() override {};

    virtual void update(const float dt) override {};
    virtual void render(sf::RenderWindow* window) override {};
};

template <class T>
class Running : public BaseState<T>
{
public:
    Running(T* o): BaseState<T>(o) {};
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override {};
    virtual void exit() override {};

    virtual void update(const float dt) override {};
    virtual void render(sf::RenderWindow* window) override {};
};

template <class T>
class TearDown : public BaseState<T>
{
public:
    TearDown(T* o): BaseState<T>(o) {};
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override {};
    virtual void exit() override {};

    virtual void update(const float dt) override {};
    virtual void render(sf::RenderWindow* window) override {};
};

#endif // STATES_GENERIC_H
