#ifndef OBJ_ACTIVE_HPP
#define OBJ_ACTIVE_HPP

#include "base_objects.hpp"
#include "layers/object_layer.hpp"
#include "components/move_set.hpp"
#include "components/physics.hpp"
#include "components/sprite.hpp"
#include "events/event_node.hpp"

class Tile;
class ObjectLayer;

class GameObject: public ObjectBase
{
public:
    GameObject(const Object::ID id, ObjectLayer* layer, const ObjectAsset &ast);
    virtual ~GameObject();
    virtual void build() { };
    virtual void setUp();
    virtual void processEvents() { };
    virtual void update(const float dt) { };
    virtual void lateUpdate() { };
    virtual void render(sf::RenderWindow *window) { };
    virtual void renderAsHovered(sf::RenderWindow *window) { };
    virtual void onKill() { };
    virtual void onReset() { };
    virtual bool isIdle() const = 0;
    bool isActive() const;
    bool isAlive() const;
    void onActivate();
    void onDeactivate();

    virtual void setTile(Tile* const next) = 0;
    Tile* getTile() const;

    ObjectAsset* getAsset();
    const std::string& getNodeName() const;
    const int getType() const;
    const Groups::ID& getGroup() const;
    void setGroup(Groups::ID id);
    void removeGroup();

protected:
    friend ObjectComponent;

    bool _active, _alive;
    ObjectLayer* _layer;
    ObjectAsset _ast;
    Groups::ID _group_id;
    bt::Node* _node;
    Tile* _tile;
    cSprite* _sprite;
};

#endif // OBJ_ACTIVE_HPP
