#ifndef CMP_COMPONENT_HPP
#define CMP_COMPONENT_HPP

#include "common.hpp"
#include "math/math.hpp"
#include "assets/object_assets.hpp"
#include "assets/scene_assets.hpp"

class GameObject;
class Tile;
class ObjectLayer;
class cSprite;

class ObjectComponent
{
public:
    ObjectComponent(GameObject *obj);
    virtual ~ObjectComponent();
    virtual void create() = 0;
    virtual void update(const float dt) {};
    virtual void render(sf::RenderWindow* window) {};

protected:
    cSprite* _getSprite();
    ObjectAsset* _ast;
    GameObject* _obj;
};


class LayerComponent
{
public:
    LayerComponent(ObjectLayer *lyr);
    virtual ~LayerComponent();

protected:
    ObjectLayer* lyr;
    const LayerAsset* ast;
};

#endif // CMP_COMPONENT_HPP
