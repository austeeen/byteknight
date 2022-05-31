#include "game_piece_states.hpp"
#include "objects/tile_object.hpp"
#include "objects/game_piece.hpp"

/**************************************************************************************************/
Idle<GamePiece>::Idle(GamePiece* o): BaseState<GamePiece>(o)
{}
void Idle<GamePiece>::enter()
{}
void Idle<GamePiece>::next(sptr<SquareEvent> e)
{
    switch (e->msg) {
        case MSG::SET_SELECTED: {
            this->_obj->switchState(statekey::selected);
            break;
        }
        case MSG::KILL_GAME_PIECE: {
            this->_obj->switchState(statekey::killed);
            break;
        }
        default: break;
    }
}
void Idle<GamePiece>::update(const float dt)
{}
void Idle<GamePiece>::render(sf::RenderWindow* window)
{
    this->_obj->_sprite->render(window);
}
void Idle<GamePiece>::exit()
{

}

/**************************************************************************************************/
Selected<GamePiece>::Selected(GamePiece* o): BaseState<GamePiece>(o)
{}
void Selected<GamePiece>::enter()
{
    this->_obj->_moveset->createMoveset();
}
void Selected<GamePiece>::next(sptr<SquareEvent> e)
{
    switch (e->msg)
    {
        case MSG::SET_DESELECTED: {
            this->_obj->switchState(statekey::idle);
            break;
        }
        case MSG::MOVE_GAME_PIECE: {
            this->_obj->switchState(statekey::moving, e);
            break;
        }
        default: break;
    }
}
void Selected<GamePiece>::update(const float dt)
{
    this->_obj->_physics->update(dt);
}
void Selected<GamePiece>::render(sf::RenderWindow* window)
{
    this->_obj->_moveset->render(window);
    this->_obj->_sprite->render(window);
}
void Selected<GamePiece>::exit()
{
    this->_obj->_moveset->clearMoveset();
}

/**************************************************************************************************/
Moving<GamePiece>::Moving(GamePiece* o): BaseState<GamePiece>(o)
{}
void Moving<GamePiece>::enter(sptr<SquareEvent> e)
{
    this->_obj->_setTargetTile(e->tile);
}
void Moving<GamePiece>::next(sptr<SquareEvent> e)
{
    switch (e->msg)
    {
        case MSG::GAME_PIECE_IDLE: {
            this->_obj->switchState(statekey::idle);
            break;
        }
        default: break;
    }
}
void Moving<GamePiece>::update(const float dt)
{
    this->_obj->_physics->update(dt);
    if (!this->_obj->_physics->isMoving()) {
        sptr<SquareEvent> e = mkptr<SquareEvent>(MSG::GAME_PIECE_IDLE);
        this->_obj->_node->notifySelf(e);
    }
}
void Moving<GamePiece>::render(sf::RenderWindow* window)
{
    this->_obj->_sprite->render(window);
}
void Moving<GamePiece>::exit()
{
    this->_obj->_resolvePlacement();
}

/**************************************************************************************************/
Killed<GamePiece>::Killed(GamePiece* o): BaseState<GamePiece>(o)
{}
void Killed<GamePiece>::enter()
{
    this->_obj->_sprite->flickerObj().started = true;
}
void Killed<GamePiece>::next(sptr<SquareEvent> e)
{}
void Killed<GamePiece>::update(const float dt)
{
    this->_obj->_sprite->update(dt);
    if (this->_obj->_sprite->flickerObj().num_switches > 10) {
        this->_obj->switchState(statekey::idle);
    }
}
void Killed<GamePiece>::render(sf::RenderWindow* window)
{
    this->_obj->_sprite->render(window);
}
void Killed<GamePiece>::exit()
{
    this->_obj->_alive = false;
}

/**************************************************************************************************/
