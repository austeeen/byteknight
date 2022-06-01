#include "object_group.hpp"
#include "objects/cursor_object.hpp"

cObjectGroup::cObjectGroup(ObjectLayer* lyr, const Groups::ID id, const std::string& name):
LayerComponent(lyr), id(id), name(name), node(new bt::Node(name)), cursor(nullptr), state(GroupState::inactive)
{
    ths_turn.clearMask();
    trigger_turn.clearMask();

    trigger_turn.setBit((int) MSG::MOVE_GAME_PIECE);
    trigger_turn.setBit((int) MSG::GAME_PIECE_IDLE);
}
cObjectGroup::~cObjectGroup()
{
    bt::destroy(node);

    if (cursor != nullptr) {
        cursor->removeGroup();
        cursor = nullptr;
    }

    for (auto [id, obj] : objects) {
        obj->removeGroup();
        obj = nullptr;
    }
    state = GroupState::inactive;
    ths_turn.clearMask();
    trigger_turn.clearMask();
}
void cObjectGroup::__add(const Object::ID id, GameObject* obj)
{
    obj->setGroup(this->id);
    node->observe(obj->getNodeName());
}
void cObjectGroup::add(const Object::ID id, GameObject* obj)
{
    switch (obj->getType()) {
        case Object::CURSOR: {
            this->add(id, dynamic_cast<Cursor*>(obj));
            break;
        }
        case Object::GAMEPIECE: {
            this->add(id, dynamic_cast<GamePiece*>(obj));
            break;
        }
        default: {
            bt::warn("cObjectGroup::add", "could not determine object type");
        }
    }
}
void cObjectGroup::add(const Object::ID id, GamePiece* obj)
{
    __add(id, obj);
    objects[id] = obj;
}
void cObjectGroup::add(const Object::ID id, Cursor* obj)
{
    __add(id, obj);
    cursor = obj;
}
void cObjectGroup::setActive()
{
    for (auto [id, obj] : objects) {
        obj->onActivate();
    }
    if (cursor != nullptr) {
        cursor->onActivate();
    }
    state = GroupState::active;
}
void cObjectGroup::setInactive()
{
    for (auto [id, obj] : objects) {
        obj->onDeactivate();
    }
    cursor->onDeactivate();
    state = GroupState::inactive;
}
bool cObjectGroup::contains(const Object::ID id)
{
    return objects.count(id) > 0;
}
bool cObjectGroup::isEmpty()
{
    return objects.empty();
}
void cObjectGroup::lateUpdate()
{
    while(this->node->hasEvents()) {
        sptr<SquareEvent> e = this->node->pop();
        switch(e->msg) {
            case MSG::KILL_GAME_PIECE: {
                this->__remove(e->object_id);
                break;
            }
            default: break;
        }
        ths_turn.setBit((int) e->msg);
        if (trigger_turn == (ths_turn & trigger_turn)) {
            bt::debug("cObjectGroup::lateUpdate", "triggered next turn");
            this->ths_turn.clearMask();
            this->lyr->swapActiveGroup();
        }
    }
}
void cObjectGroup::render(sf::RenderWindow* window)
{
    for (auto [id, obj] : objects) {
        obj->render(window);
    }
    if (state == GroupState::active) {
        cursor->render(window);
    }
}
void cObjectGroup::__remove(const Object::ID id)
{
    objects.erase(id);
    this->lyr->queueToRemove(id);
    if (this->isEmpty()) {
        node->notifyNode(mkptr<SquareEvent>(MSG::TEAM_LOST, this->name), "instance");
    }
}
