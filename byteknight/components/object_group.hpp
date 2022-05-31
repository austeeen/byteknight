#ifndef CMP_OBJGROUP_HPP
#define CMP_OBJGROUP_HPP

#include "component.hpp"
#include "events/event_node.hpp"
#include "utils/bitmask.hpp"
#include "datacore/object_core.hpp"

enum GroupState { active, inactive };

class Cursor;
class GamePiece;
class GameObject;

class cObjectGroup: public LayerComponent
{
public:
    cObjectGroup(ObjectLayer* lyr, const Groups::ID id, const std::string& name);
    ~cObjectGroup();
    void add(const Object::ID id, GameObject* obj);
    void add(const Object::ID id, GamePiece* obj);
    void add(const Object::ID id, Cursor* obj);
    void setActive();
    void setInactive();
    void lateUpdate();
    void render(sf::RenderWindow* window);

    bool contains(const Object::ID id);
    bool isEmpty();


private:
    void __add(const Object::ID id, GameObject* obj);
    void __remove(const Object::ID id);

    const Groups::ID id;
    const std::string name;
    Node* node;
    Cursor* cursor;
    std::map<const Object::ID, GamePiece*> objects;
    GroupState state;
    std::map<const MSG, int> bit_table;
    Bitmask ths_turn;
    Bitmask trigger_turn;
};

#endif // CMP_OBJGROUP_HPP
