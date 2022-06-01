#include "move_set.hpp"
#include "objects/game_object.hpp"
#include "objects/tile_object.hpp"

std::map<std::string, std::vector<std::string>> ChessPieces {
    { "bishop", { "UL", "UULL", "UR", "UURR", "DR", "DDRR", "DL", "DDLL" } },
    { "king", { "UL", "U", "UR", "L", "R", "DR", "D", "DL" } },
    { "knight", { "UUL", "UUR", "LLU", "RRU", "LLD", "RRD", "DDL", "DDR" } },
};

void cMoveSet::create()
{
    std::vector<std::string> moves = ChessPieces[_ast->move_set];

    for (std::string &m_str : moves) {
        bt::moveset movedirs;
        for (auto chr : m_str) {
            movedirs.push_back(bt::C2DIR4.at(chr));
        }
        allmoves.push_back(movedirs);
    }
}
void cMoveSet::render(sf::RenderWindow* window)
{
    for (auto [id, t] : tileset)
        t->render(window);
}
void cMoveSet::createMoveset()
{
    _obj->getTile()->getTiles(allmoves, tileset);
};
void cMoveSet::clearMoveset()
{
    tileset.clear();
}
bool cMoveSet::contains(const Object::ID id) const
{
    return tileset.count(id) > 0;
}
