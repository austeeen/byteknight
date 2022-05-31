#include "base_objects.hpp"

ObjectBase::ObjectBase(const Object::ID id) :
_id(id)
{}
ObjectBase::ObjectBase(const Object::ID id, const SQ::rect& rect) :
rect(rect), _id(id)
{}
ObjectBase::ObjectBase(const Object::ID id, const SQ::rect& rect, const SQ::coord& crd) :
rect(rect), crd(crd), _id(id)
{}
ObjectBase::~ObjectBase()
{}
const Object::ID ObjectBase::getID() const
{
    return _id;
}
const sf::Vector2f ObjectBase::getCenter() const
{
    return (sf::Vector2f) rect.center;
}
void ObjectBase::setCenter(const sf::Vector2f c)
{
    this->rect.center = c;
}
