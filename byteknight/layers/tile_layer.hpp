#ifndef LYR_TILE_HPP
#define LYR_TILE_HPP

#include "common.hpp"
#include "layer_base.hpp"
#include "math/math.hpp"
#include "assets/scene_assets.hpp"

class GameObject;
class GamePiece;
class Cursor;
class Tile;

class TileLayer: public LayerBase
{
public:
    TileLayer(const std::string& name, SceneContext* scene_context, const LayerAsset& lyr_ast);
    ~TileLayer() override;
    void build() override;
    void setUp() override;
    void processEvents() override {};
    void update(const float dt) override {};
    void lateUpdate() override {};
    void render(sf::RenderWindow* window) override;

    void onReset() override {};
    void onStart() override {};

    void setActive() override {};
    void setPaused() override {};
    void setFrozen() override {};
    void setInactive() override {};

    void assign(GameObject* obj);
    void assign(std::vector<GameObject*> &objects);

    const std::string tostr() const;

private:
    void __generateTiles();
    void __arrangeTiles();

    Meta::gamedata scenedata;
    std::vector<Tile*> alltiles;
    std::map<const Object::ID, int> tile2indx;
};

#endif // LYR_TILE_HPP
