#include "game_piece.hpp"
#include "tile_object.hpp"
#include "layers/object_layer.hpp"

GamePiece::GamePiece(const Object::ID id, ObjectLayer* layer, const ObjectAsset &ast) :
GameObject(id, layer, ast)
{
    _moveset = new cMoveSet(this);
    _physics = new cPhysics(this);

    registerState(statekey::idle, new Idle<GamePiece>(this));
    registerState(statekey::selected, new Selected<GamePiece>(this));
    registerState(statekey::moving, new Moving<GamePiece>(this));
    registerState(statekey::killed, new Killed<GamePiece>(this));
    this->switchState(statekey::idle);

    __target = nullptr;
}
GamePiece::~GamePiece()
{
    __target = nullptr;
    SQ::destroy(_moveset);
    SQ::destroy(_physics);
}
void GamePiece::build()
{
    this->_moveset->create();
    this->_physics->create();
    this->_sprite->create();
}
void GamePiece::processEvents()
{
    // if not (can_process) return
    while (this->_node->hasEvents()) {
        sptr<SquareEvent> e = this->_node->pop();
        // if event in my actions call actions[event](event)
        //else
        this->_cur_state->next(e);
    }
}
void GamePiece::update(const float dt)
{
    this->_cur_state->update(dt);
}
void GamePiece::lateUpdate()
{
    this->_layer->addRenderedObject(this->_id, this->_id);
}
void GamePiece::render(sf::RenderWindow *window)
{
    this->_cur_state->render(window);
}
void GamePiece::renderAsHovered(sf::RenderWindow *window)
{
    this->_ast.nametag->setPosition(this->rect.left, this->rect.bottom);
    window->draw(*this->_ast.nametag);
}
void GamePiece::onKill()
{
    // todo -- should probably use this right?
    // this->_alive = false;
}
bool GamePiece::isIdle() const
{
    return _cur_state_key == statekey::idle;
}
void GamePiece::setTile(Tile* const next)
{
    SQ::throwForNullPtr(next, "NEXT TILE");
    if (this->_tile != nullptr) {
        this->_tile->clearObject();
    }
    next->setObject(this);
    this->_tile = next;
}
void GamePiece::_setTargetTile(Tile* const target)
{
    __target = target;
    _physics->setDestination(target);
}
void GamePiece::_resolvePlacement()
{
    if (this->__target->hasObject()) {
        GamePiece* obj = this->__target->getObject();
        if (this->_group_id != obj->getGroup()) {
            sptr<SquareEvent> e = mkptr<SquareEvent>(MSG::KILL_GAME_PIECE, obj->getID());
            this->_node->notifyNode(e, obj->getNodeName());
        }
        obj = nullptr;
    }
    this->setTile(this->__target);
    this->__target = nullptr;
}
bool GamePiece::moveSetContains(const Object::ID id)
{
    return this->_moveset->contains(id);
}
