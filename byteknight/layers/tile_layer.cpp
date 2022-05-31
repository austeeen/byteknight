#include "tile_layer.hpp"
#include "objects/tile_object.hpp"
#include "objects/cursor_object.hpp"

TileLayer::TileLayer(const std::string& name, SceneContext* scene_context, const LayerAsset &lyr_ast) :
LayerBase(name, scene_context, lyr_ast), scenedata(scene_context->getSceneData())
{
    SQ::warnForBadValue<int>(lyr_ast.lyr_cols, GETNAME(lyr_ast.lyr_cols), "TileLayer");
};
TileLayer::~TileLayer()
{
    for (auto tile : alltiles)
        SQ::destroy(tile);
    alltiles.clear();
}
void TileLayer::build()
{
    __generateTiles();
    for(auto& t : alltiles) {
        t->build();
    }
    __arrangeTiles();
}
void TileLayer::setUp()
{
    for(auto& t : alltiles) {
        t->setUp();
    }
}
void TileLayer::__generateTiles()
{
    for (unsigned int i = 0; i < scenedata.total_tiles; i++) {
        const Object::ID id = i;
        SQ::coord c(i, lyr_ast.lyr_cols);
        SQ::rect r(c, (sf::Vector2f) scenedata.tile_size.size);
        Tile* t = new Tile(id, r, c);
        alltiles.push_back(t);
    }
}
void TileLayer::__arrangeTiles()
{
    const int bw = scenedata.board_size.width;
    const int bh = scenedata.board_size.height;

    for (size_t i = 0; i < alltiles.size(); i ++) {
        Tile *t = alltiles[i];
        if (t->crd.y > 0)
            t->setNeighbor(SQ::dir4::up,    alltiles[i - bw]);
        if (t->crd.y < (bh - 1))
            t->setNeighbor(SQ::dir4::down,  alltiles[i + bw]);
        if (t->crd.x > 0)
            t->setNeighbor(SQ::dir4::left,  alltiles[i - 1]);
        if (t->crd.x < (bw - 1))
            t->setNeighbor(SQ::dir4::right, alltiles[i + 1]);
    }
}
void TileLayer::assign(GameObject* obj)
{
    obj->setTile(alltiles[obj->crd.i]);
}
void TileLayer::assign(std::vector<GameObject*> &objects)
{
    for (auto obj : objects) {
        obj->setTile(alltiles[obj->crd.i]);
    }
}
void TileLayer::render(sf::RenderWindow* window)
{
    for(auto t : alltiles) {
        t->render(window);
    }
}
const std::string TileLayer::tostr() const
{
    std::string ret = "";
    for(size_t i = 0; i < alltiles.size(); i++) {
        if (i % lyr_ast.lyr_cols == 0) {
            ret += "\n|";
        }
        std::string c = "";
        if (alltiles[i]->hasObject()) {
            c += "O";
        }
        if (alltiles[i]->hasCursor(Groups::RED_TEAM)) {
            c += "R";
        }
        if (alltiles[i]->hasCursor(Groups::BLUE_TEAM)) {
            c += "B";
        }
        while (c.size() < 3) {
            c += " ";
        }
        c += "|";
        ret += c;
    }
    return ret;
}
