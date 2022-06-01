#ifndef OBJ_CURSOR_HPP
#define OBJ_CURSOR_HPP

#include "states/cursor_object_states.hpp"
#include "game_piece.hpp"

class Cursor: public GameObject, public Stateful<Cursor>
{
    friend Idle<Cursor>;
    friend Selected<Cursor>;
public:
    Cursor(const Object::ID id, ObjectLayer* layer, const ObjectAsset &ast);
    ~Cursor();
    void build() override;
    // void setUp() override;
    void processEvents() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow *window) override;

    // todo: could render cursors as hovered as well
    void renderAsHovered(sf::RenderWindow *window) override {};

    // todo: maybe run some kill animation on the cursor when the team is dead
    void onKill() override {};

    bool isIdle() const override;
    void setTile(Tile * const next) override;

protected:
    bool _canSelect() const;
    bool _isHovering() const;
    void _setSelected(GamePiece* obj);
    void _updateHovering(GamePiece* obj);
    void _clearSelected();
    void _clearHovering();
    GamePiece* _getHoveredObject() const;
    void _renderHoveredObject(sf::RenderWindow* window);

    GamePiece* _hovered_obj;
    GamePiece* _selected_obj;
    cPhysics* _physics;

private:
    void __bindingInput(BindingEvent dir);
    void __changeTile(bt::dir4 dir);
};

#endif // OBJ_CURSOR_HPP
