#include "object_layer.hpp"
#include "objects/cursor_object.hpp"
#include "objects/game_piece.hpp"

ObjectLayer::ObjectLayer(const std::string& name, bt::SceneContext* scene_context, const ObjectLayerAsset &lyr_ast) :
LayerBase(name, scene_context, lyr_ast)
{
    for (const auto& ast : lyr_ast.obj_list)
    {
        if (__createObject(ast)) {
            if (ast.group_id != Groups::NO_TEAM) {
                if (__groups.count(ast.group_id) == 0) {
                    __createGroup(ast.group_id, ast.group_name);
                }
                this->__groups[ast.group_id]->add(ast.id, __allobjects[ast.id]);
            }
        }
    }
}
bool ObjectLayer::__createObject(const ObjectAsset& ast)
{
    bool was_created = false;
    switch(ast.type_id)
    {
        case Object::CURSOR: {
            Cursor* obj = new Cursor(ast.id, this, ast);
            __allobjects[ast.id] = obj;
            was_created = true;
            break;
        }
        case Object::GAMEPIECE: {
            GamePiece* obj = new GamePiece(ast.id, this, ast);
            __allobjects[ast.id] = obj;
            was_created = true;
            break;
        }
        default: {
            bt::err("ObjectLayer::ObjectLayer", "Unknown object type %s", ast.type);
            break;
        };
    }
    return was_created;
}
void ObjectLayer::__createGroup(const Groups::ID id, const std::string& group_name)
{
    this->__groups[id] = new cObjectGroup(this, id, group_name);
}
ObjectLayer::~ObjectLayer()
{
    for (auto [id, grp] : __groups)
        bt::destroy(grp);
    __groups.clear();

    for (auto [id, obj] : __allobjects)
        bt::destroy(obj);
    __allobjects.clear();
}
void ObjectLayer::build()
{
    for (auto [obj_id, obj] : __allobjects) {
        obj->build();
    }
}
void ObjectLayer::setUp()
{
    for (auto [obj_id, obj] : __allobjects) {
        obj->setUp();
    }
}
void ObjectLayer::processEvents()
{
    for (auto [obj_id, obj] : __allobjects) {
        obj->processEvents();
    }
}
void ObjectLayer::update(const float dt)
{
    for (auto [obj_id, obj] : __allobjects) {
        obj->update(dt);
    }
}
void ObjectLayer::lateUpdate()
{
    for (auto [group_id, group] : __groups) {
        group->lateUpdate();
    }

    if (this->__to_despawn.size() > 0) {
        this->__updateDespawnedObjects();
    }

    for (auto [obj_id, obj] : __allobjects) {
        obj->lateUpdate();
    }
}
void ObjectLayer::__updateDespawnedObjects()
{
    /*
    idea -- consider using a deque instead of two vectors
    just use an iterator to move through each object in __to_despawn
    if an object is not ready to be erased, pop it from the deque and then push it to the front of the deque
     -- this may invalidate the iterator though and cause weird behavior, test first
    */

    /*
    sometimes i don't want to instantly erase an object from memory when another interface flags
    it as 'dead' -- so i use a despawn buffer to keep those objects on death row and check if its
    okay to erase them each frame.
    */
    std::vector<Object::ID> despawn_buffer;
    for (const Object::ID &dead_id : __to_despawn) {
        if (!__allobjects[dead_id]->isAlive()) {
            __destroyObject(dead_id);
        } else {
            despawn_buffer.push_back(dead_id);
        }
    }
    __to_despawn.clear();
    if (despawn_buffer.size() > 0) {
        __to_despawn = despawn_buffer;
    }
}
void ObjectLayer::__destroyObject(const Object::ID id)
{
    bt::destroy(__allobjects[id]);
    __allobjects.erase(id);
}
void ObjectLayer::render(sf::RenderWindow* window)
{
    // todo: render stack stuff
    __inactive_group->render(window);
    __active_group->render(window);
    for (const Object::ID &dead_id : __to_despawn) {
        __allobjects[dead_id]->render(window);
    }
}
bool ObjectLayer::canExit()
{
    return this->__to_despawn.size() == 0;
}
void ObjectLayer::onStart()
{
    bt::throwForNullPtr(__groups[Groups::RED_TEAM], "red team");
    bt::throwForNullPtr(__groups[Groups::BLUE_TEAM], "blue team");
    // todo -- allow user to "roll" to decide whose first?
    this->__active_group = __groups[Groups::RED_TEAM];
    this->__inactive_group = __groups[Groups::BLUE_TEAM];
    this->__active_group->setActive();
    this->__inactive_group->setInactive();
}
void ObjectLayer::addRenderedObject(const Object::ID id, const Render::Order order)
{
    __to_render.push(Render::OrderedObject{id, order});
}
void ObjectLayer::addRenderedObject(const Render::OrderedObject ordered_obj)
{
    __to_render.push(ordered_obj);
}
void ObjectLayer::queueToRemove(const Object::ID id)
{
    this->__to_despawn.push_back(id);
}
void ObjectLayer::swapActiveGroup()
{
    this->__active_group->setInactive();
    this->__inactive_group->setActive();
    cObjectGroup* hold = this->__active_group;
    this->__active_group = this->__inactive_group;
    this->__inactive_group = hold;
}
void ObjectLayer::getAllObjects(std::vector<GameObject*>& objs)
{
    for (auto [obj_id, obj] : __allobjects) {
        objs.push_back(obj);
    }
}
