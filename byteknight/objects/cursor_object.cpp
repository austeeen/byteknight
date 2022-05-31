#include "cursor_object.hpp"
#include "game_object.hpp"
#include "tile_object.hpp"
#include "layers/object_layer.hpp"

Cursor::Cursor(const Object::ID id, ObjectLayer* layer, const ObjectAsset &ast) :
GameObject(id, layer, ast)
{
    _physics = new cPhysics(this);
    this->_hovered_obj = nullptr;
    this->_selected_obj = nullptr;

    registerState(statekey::idle, new Idle<Cursor>(this));
    registerState(statekey::selected, new Selected<Cursor>(this));
    this->switchState(statekey::idle);

    this->_node->observe("instance");
}
Cursor::~Cursor()
{
    _selected_obj = nullptr;
    _hovered_obj = nullptr;
    SQ::destroy(_physics);
}
void Cursor::build()
{
    this->_physics->create();
    this->_sprite->create();
}
void Cursor::processEvents()
{
    if (!this->_active) {
        return;
    }

    while (this->_node->hasEvents()) {
        sptr<SquareEvent> e = this->_node->pop();
        if (e->msg == MSG::CTLR_PRESSED) {
            this->__bindingInput(e->binding);
        } else {
            this->_cur_state->next(e);
        }
    }
}
void Cursor::update(const float dt)
{
    this->_updateHovering(this->_tile->getObject());
    this->_cur_state->update(dt);
}
void Cursor::lateUpdate()
{
    this->_layer->addRenderedObject(this->_id, Render::Last);
}
void Cursor::render(sf::RenderWindow *window)
{
    this->_cur_state->render(window);
}
bool Cursor::isIdle() const
{
    return _cur_state_key == statekey::idle;
}
void Cursor::setTile(Tile* const next)
{
    SQ::throwForNullPtr(next, "NEXT TILE");

    if (this->_tile != nullptr){
        this->_tile->clearCursor(this->_group_id);
    }

    next->setCursor(this->_group_id, this);
    this->_tile = next;
}
bool Cursor::_canSelect() const
{
    return (this->_hovered_obj != nullptr &&
            this->_hovered_obj->getGroup() == this->_group_id);
}
bool Cursor::_isHovering() const
{
    return this->_hovered_obj != nullptr;
}
void Cursor::_setSelected(GamePiece* obj)
{
    if (this->_selected_obj != nullptr) {
        if (this->_selected_obj->getID() == obj->getID())
            return;
        this->_clearSelected();
    }
    this->_selected_obj = obj;
    if (this->_selected_obj != nullptr) {
        sptr<SquareEvent> e = mkptr<SquareEvent>(MSG::SET_SELECTED);
        this->_node->notifyNode(e, this->_selected_obj->getNodeName());
    }
}
void Cursor::_updateHovering(GamePiece* obj)
{
    this->_hovered_obj = obj;
}
void Cursor::_clearSelected()
{
    sptr<SquareEvent> e = mkptr<SquareEvent>(MSG::SET_DESELECTED);
    this->_node->notifyNode(e, this->_selected_obj->getNodeName());
    this->_selected_obj = nullptr;
}
void Cursor::_clearHovering()
{
    this->_hovered_obj = nullptr;
}
GamePiece* Cursor::_getHoveredObject() const
{
    // todo unsure if needed
    return this->_hovered_obj;
}
void Cursor::_renderHoveredObject(sf::RenderWindow* window)
{
    if (this->_hovered_obj != nullptr) {
        this->_hovered_obj->renderAsHovered(window);
    }
}
void Cursor::__bindingInput(BindingEvent binding)
{
    if (binding.dir != SQ::dir4::none) {
        this->__changeTile(binding.dir);
    }
    else {
        switch (binding.binding) {
            case io::select: {
                this->_node->notifySelf(mkptr<SquareEvent>(MSG::CURSOR_SELECTED));
                break;
            }
            case io::back: {
                this->_node->notifySelf(mkptr<SquareEvent>(MSG::CURSOR_DESELECTED));
                break;
            }
        }
    }
}
void Cursor::__changeTile(SQ::dir4 dir)
{
    Tile* next_tile = this->_tile->getNeighbor(dir);
    if (this->_physics->setDestination(next_tile)) {
        this->setTile(next_tile);
    }
}
