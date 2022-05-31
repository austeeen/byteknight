#include "cursor_object_states.hpp"
#include "objects/cursor_object.hpp"
#include "objects/tile_object.hpp"

/**************************************************************************************************/
Idle<Cursor>::Idle(Cursor* o): BaseState<Cursor>(o)
{}
void Idle<Cursor>::enter()
{}
void Idle<Cursor>::next(sptr<SquareEvent> e)
{
    switch (e->msg) {
        case MSG::CURSOR_SELECTED: {
            if (this->_obj->_canSelect()) {
                this->_obj->switchState(statekey::selected);
            }
        }
        default: break;
    }
}
void Idle<Cursor>::exit()
{}
void Idle<Cursor>::update(const float dt)
{
    this->_obj->_physics->update(dt);
}
void Idle<Cursor>::render(sf::RenderWindow* window)
{
    this->_obj->_renderHoveredObject(window);
    this->_obj->_sprite->render(window);
}
/**************************************************************************************************/
Selected<Cursor>::Selected(Cursor* o): BaseState<Cursor>(o)
{}
void Selected<Cursor>::enter()
{
    this->_obj->_setSelected(this->_obj->_hovered_obj);
}
void Selected<Cursor>::next(sptr<SquareEvent> e)
{
    switch (e->msg)
    {
        case MSG::CURSOR_SELECTED: {
            if (this->_obj->_canSelect()) {
                this->_obj->switchState(statekey::selected);
            }
            else if (this->_obj->_selected_obj->moveSetContains(this->_obj->_tile->getID())) {
                sptr<SquareEvent> sq_event = mkptr<SquareEvent>(MSG::MOVE_GAME_PIECE, this->_obj->_tile);
                this->_obj->_node->notifyNode(sq_event, this->_obj->_selected_obj->getNodeName());
                this->_obj->switchState(statekey::idle);
            }
            else {
                this->_obj->switchState(statekey::idle);
            }
            break;
        }
        case MSG::CURSOR_DESELECTED: {
            this->_obj->switchState(statekey::idle);
            break;
        }
        default: break;
    }
}
void Selected<Cursor>::update(const float dt)
{
    this->_obj->_physics->update(dt);
}
void Selected<Cursor>::exit()
{
    this->_obj->_clearSelected();
}
void Selected<Cursor>::render(sf::RenderWindow* window)
{
    this->_obj->_renderHoveredObject(window);
    this->_obj->_sprite->render(window);
}
/**************************************************************************************************/
