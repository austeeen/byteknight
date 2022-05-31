#include "tile_object.hpp"
#include "cursor_object.hpp"

Tile::Tile(const Object::ID id, const SQ::rect r, const SQ::coord c) :
ObjectBase(id, r, c)
{
    __neighbors[SQ::dir4::up] = nullptr;
    __neighbors[SQ::dir4::right] = nullptr;
    __neighbors[SQ::dir4::down] = nullptr;
    __neighbors[SQ::dir4::left] = nullptr;
    __obj = nullptr;
    __tileshape = nullptr;
}
Tile::~Tile()
{
    SQ::destroy(__tileshape);
    for (int i = 0; i < 4; i++) {
        if (__neighbors[i] != nullptr)
            __neighbors[i]->__removeNeighbor(static_cast<SQ::dir4>((i + 2) % 4));
    }
    this->__obj = nullptr;
    this->__cursors.clear();
}
void Tile::__removeNeighbor(SQ::dir4 dir)
{
    this->__neighbors[dir] = nullptr;
}
void Tile::build()
{
    this->__tileshape = new sf::RectangleShape();
}
void Tile::setUp()
{
    sf::Vector2f pos = this->rect.pos;
    sf::Vector2f size = this->rect.size;
    pos.x += 4;
    pos.y += 4;
    size.x -= 8;
    size.y -= 8;
    this->__tileshape->setPosition(pos);
    this->__tileshape->setSize(size);
    this->__tileshape->setFillColor(sf::Color::Transparent);
    this->__tileshape->setOutlineColor(sf::Color::Red);
    this->__tileshape->setOutlineThickness(1);
}
void Tile::setNeighbor(SQ::dir4 dir, Tile *t)
{
    this->__neighbors[dir] = t;
}
bool Tile::hasNeighbor(SQ::dir4 d)
{
    return this->__neighbors[d] != nullptr;
}
Tile* Tile::getNeighbor(SQ::dir4 d)
{
    return this->__neighbors[d];
}
void Tile::setObject(GamePiece* obj)
{
    this->__obj = obj;
}
bool Tile::hasObject() const
{
    return this->__obj != nullptr;
}
GamePiece* Tile::getObject() const
{
    return this->__obj;
}
void Tile::clearObject()
{
    this->__obj = nullptr;
}
void Tile::setCursor(const Groups::ID t, Cursor* c)
{
    this->__cursors[t] = c;
}
bool Tile::hasCursor(const Groups::ID t)
{
    if (this->__cursors.count(t) == 0)
        return false;
    return this->__cursors[t] != nullptr;
}
Cursor* Tile::getCursor(const Groups::ID t)
{
    if (this->__cursors.count(t) == 0)
        return nullptr;
    return this->__cursors[t];
}
void Tile::clearCursor(const Groups::ID t)
{
    if (this->__cursors.count(t) == 0) {
        SQ::err("Tile::clearCursor", "cannot clear __cursors[%d], key does not exist.", t);
        return;
    }
    this->__cursors[t] = nullptr;
}
void Tile::getTiles(std::vector<SQ::moveset> &moves, std::map<const Object::ID, Tile*> &tileset)
{
    tileset.clear();
    Tile *p = this;
    for (auto &m_str : moves) {
        Tile *t = p;
        for (auto d : m_str) {
            if (!t->hasNeighbor(d)) {
                t = nullptr;
                break;
            } else {
                t = t->getNeighbor(d);
            }
        }
        if (t)
            tileset[t->getID()] = t;
    }
}
void Tile::render(sf::RenderWindow* window)
{
    window->draw(*__tileshape);
}
const std::string Tile::tostr()
{
    return this->crd.tostr();
}
