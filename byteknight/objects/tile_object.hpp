#ifndef UTL_TILE_H
#define UTL_TILE_H

#include "base_objects.hpp"
#include "utils/math.hpp"

class GamePiece;
class Cursor;

class Tile: public ObjectBase
{
public:
    Tile(const Object::ID id, const bt::rect r, const bt::coord c);
    ~Tile();
    void build();
    void setUp();
    void render(sf::RenderWindow* window);
    void renderAsHovered(sf::RenderWindow *window) {};
    void setNeighbor(bt::dir4 d, Tile* t);
    bool hasNeighbor(bt::dir4 d);
    Tile* getNeighbor(bt::dir4 d);
    void setObject(GamePiece* obj);
    bool hasObject() const;
    GamePiece* getObject() const;
    void clearObject();
    void setCursor(const Groups::ID t, Cursor* c);
    bool hasCursor(const Groups::ID t);
    Cursor* getCursor(const Groups::ID t);
    void clearCursor(const Groups::ID t);
    void getTiles(std::vector<bt::moveset> &moves, std::map<const Object::ID, Tile*> &tileset);

    const std::string tostr();

private:
    void __removeNeighbor(bt::dir4 dir);
    Tile* __neighbors[4];
    GamePiece *__obj;
    std::map<const Groups::ID, Cursor*> __cursors;
    sf::RectangleShape* __tileshape;
};
#endif // UTL_TILE_H
