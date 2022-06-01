#ifndef CMP_MOVESET_HPP
#define CMP_MOVESET_HPP

#include "component.hpp"
#include "datacore/object_core.hpp"

class cMoveSet: public ObjectComponent
{
public:
    cMoveSet(GameObject* obj): ObjectComponent(obj) {};
    ~cMoveSet() override {
        _obj = nullptr;
        tileset.clear();
    };
    void create() override;
    void render(sf::RenderWindow* window) override;
    void createMoveset();
    void clearMoveset();
    bool contains(const Object::ID id) const;

private:
    std::map<const Object::ID, Tile*> tileset;
    int numtiles;
    std::vector<bt::moveset> allmoves;

};

#endif // CMP_MOVESET_HPP
