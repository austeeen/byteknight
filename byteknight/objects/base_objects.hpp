#ifndef BASE_OBJ_HPP
#define BASE_OBJ_HPP

#include "common.hpp"
#include "math/math.hpp"
#include "datacore/common_core.hpp"
#include "datacore/object_core.hpp"

class ObjectBase
{
public:
    ObjectBase(const Object::ID id);
    ObjectBase(const Object::ID id, const SQ::rect& rect);
    ObjectBase(const Object::ID id, const SQ::rect& rect, const SQ::coord& crd);
    ~ObjectBase();
    const Object::ID getID() const;
    const sf::Vector2f getCenter() const;
    void setCenter(const sf::Vector2f c);

    SQ::rect rect;
    SQ::coord crd;
protected:
    const Object::ID _id;
    Meta::gamedata _scene_data;
};

#endif // BASE_OBJ_HPP
