#ifndef STATES_GAMEPIECE_H
#define STATES_GAMEPIECE_H

#include "generic_states.hpp"

class GamePiece;

template <>
class Idle<GamePiece> : public BaseState<GamePiece>
{
public:
    Idle(GamePiece* o);
    virtual void enter() override;
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

template <>
class Selected<GamePiece> : public BaseState<GamePiece>
{
public:
    Selected(GamePiece* o);
    virtual void enter() override;
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

template <>
class Moving<GamePiece> : public BaseState<GamePiece>
{
public:
    Moving(GamePiece* o);
    virtual void enter() override {};
    virtual void enter(sptr<SquareEvent> e) override;
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};

template <>
class Killed<GamePiece> : public BaseState<GamePiece>
{
public:
    Killed(GamePiece* o);
    virtual void enter() override;
    virtual void enter(sptr<SquareEvent> e) override {};
    virtual void next(sptr<SquareEvent> e) override;
    virtual void exit() override;

    virtual void update(const float dt) override;
    virtual void render(sf::RenderWindow* window) override;
};
#endif // STATES_GAMEPIECE_H
