#include "game_object.hpp"
#include "tile_object.hpp"
#include "assets/object_assets.hpp"

GameObject::GameObject(const Object::ID id, ObjectLayer* layer, const ObjectAsset &ast) :
ObjectBase(id, ast.collision_rect, ast.start_coord),
_active(false),
_alive(true),
_layer(layer),
_ast(ast),
_group_id(ast.group_id),
_node(new bt::Node(ast.name)),
_tile(nullptr),
_sprite(new cSprite(this))
{}
GameObject::~GameObject()
{
    _layer = nullptr;
    _tile = nullptr;
    bt::destroy(_node);
}
void GameObject::setUp()
{
    bt::throwForNullPtr(_tile, GETNAME(_tile));
    this->rect.setCenter(this->_tile->getCenter());
}
bool GameObject::isActive() const
{
    return _active;
}
bool GameObject::isAlive() const
{
    return _alive;
}
void GameObject::onActivate()
{
    this->_active = true;
}
void GameObject::onDeactivate()
{
    this->_active = false;
}
ObjectAsset* GameObject::getAsset()
{
    return &_ast;
}
Tile* GameObject::getTile() const
{
    return _tile;
}
const std::string& GameObject::getNodeName() const
{
    return this->_node->name();
}
const int GameObject::getType() const
{
    return this->_ast.type_id;
}
const Groups::ID& GameObject::getGroup() const
{
    return this->_group_id;
}
void GameObject::setGroup(Groups::ID id)
{
    this->_group_id = id;
}
void GameObject::removeGroup()
{
    this->_group_id = -1;
}
