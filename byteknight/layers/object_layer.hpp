#ifndef LYR_OBJECTS_HPP
#define LYR_OBJECTS_HPP

#include "common.hpp"
#include "layer_base.hpp"
#include "components/object_group.hpp"
#include "assets/object_assets.hpp"
#include "assets/scene_assets.hpp"

/*
idea - Interface > Container > System > Component
break up the layer stuff into more simple container-like classes
factor out layer functionality into system/components that are used by a layer
tile layer could be the same as the object layer just with different components
*/

class GameObject;

class ObjectLayer: public LayerBase
{
public:
    ObjectLayer(const std::string& name, bt::SceneContext* scene_context, const ObjectLayerAsset &lyr_ast);
    ~ObjectLayer() override;
    void build() override;
    void setUp() override;
    void processEvents() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow* window) override;
    bool canExit() override;
    void onStart() override;

    void addRenderedObject(const Object::ID id, const Render::Order order);
    void addRenderedObject(const Render::OrderedObject ordered_obj);
    void queueToRemove(const Object::ID id);
    void swapActiveGroup();

    void getAllObjects(std::vector<GameObject*>& objs);

private:
    bool __createObject(const ObjectAsset& ast);
    void __createGroup(const Groups::ID id,  const std::string& group_name);
    void __updateDespawnedObjects();
    void __destroyObject(const Object::ID id);

    std::map<Object::ID, GameObject*> __allobjects;
    std::map<Groups::ID, cObjectGroup*> __groups;
    cObjectGroup* __active_group;
    cObjectGroup* __inactive_group;
    Render::Queue __to_render;
    std::vector<Object::ID> __to_despawn;
};

#endif // SCN_LYR_OBJECTS_HPP
