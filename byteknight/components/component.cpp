#include "component.hpp"
#include "objects/game_object.hpp"
#include "layers/layer_base.hpp"
#include "components/sprite.hpp"

ObjectComponent::ObjectComponent(GameObject *obj):
_ast(obj->getAsset()), _obj(obj)
{}
ObjectComponent::~ObjectComponent()
{
    _obj = nullptr;
    _ast = nullptr;
};
cSprite *ObjectComponent::_getSprite()
{
    return this->_obj->_sprite;
}

LayerComponent::LayerComponent(ObjectLayer *lyr) :
lyr(lyr), ast(lyr->getAsset())
{}
LayerComponent::~LayerComponent()
{
    lyr = nullptr;
    ast = nullptr;
};
