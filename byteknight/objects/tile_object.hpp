#ifndef UTL_TILE_H
#define UTL_TILE_H

#include "base_objects.hpp"
#include "math/math.hpp"

class GamePiece;
class Cursor;

class Tile: public ObjectBase
{
public:
    Tile(const Object::ID id, const SQ::rect r, const SQ::coord c);
    ~Tile();
    void build();
    void setUp();
    void render(sf::RenderWindow* window);
    void renderAsHovered(sf::RenderWindow *window) {};
    void setNeighbor(SQ::dir4 d, Tile* t);
    bool hasNeighbor(SQ::dir4 d);
    Tile* getNeighbor(SQ::dir4 d);
    void setObject(GamePiece* obj);
    bool hasObject() const;
    GamePiece* getObject() const;
    void clearObject();
    void setCursor(const Groups::ID t, Cursor* c);
    bool hasCursor(const Groups::ID t);
    Cursor* getCursor(const Groups::ID t);
    void clearCursor(const Groups::ID t);
    void getTiles(std::vector<SQ::moveset> &moves, std::map<const Object::ID, Tile*> &tileset);

    const std::string tostr();

private:
    void __removeNeighbor(SQ::dir4 dir);
    Tile* __neighbors[4];
    GamePiece *__obj;
    std::map<const Groups::ID, Cursor*> __cursors;
    sf::RectangleShape* __tileshape;
};
#endif // UTL_TILE_H
