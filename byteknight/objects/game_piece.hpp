#ifndef OBJ_GAMEPIECE_HPP
#define OBJ_GAMEPIECE_HPP

#include "properties/stateful.hpp"
#include "states/game_piece_states.hpp"
#include "game_object.hpp"

class GamePiece: public GameObject, public Stateful<GamePiece>
{
private:
    friend Idle<GamePiece>;
    friend Selected<GamePiece>;
    friend Moving<GamePiece>;
    friend Killed<GamePiece>;
public:
    GamePiece(const Object::ID id, ObjectLayer* layer, const ObjectAsset &ast);
    ~GamePiece();
    void build() override;
    void processEvents() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow *window) override;
    void renderAsHovered(sf::RenderWindow *window) override;
    void onKill() override;
    bool isIdle() const override;
    void setTile(Tile* const next) override;
    bool moveSetContains(const Object::ID id);

protected:
    void _setTargetTile(Tile* const t);
    void _resolvePlacement();

    cMoveSet* _moveset;
    cPhysics* _physics;
private:
    Tile* __target;
};

#endif // OBJ_GAMEPIECE_HPP
