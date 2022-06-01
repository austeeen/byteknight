#include "canvas.hpp"

namespace bt::gui
{

Canvas::Canvas(Menu* menu, SceneContext* scene_context, const WidgetAsset& wdgt_ast):
Widget(menu, scene_context, wdgt_ast), EventfulWidget(wdgt_ast)
{
    this->_menu->add<EventfulWidget>(this);
    __img_sprite.setTexture(wdgt_ast.img_texture);
}
Canvas::~Canvas()
{}
void Canvas::setUp()
{
    this->_rect = _ast.position_rect;
    this->__surface.create(this->_rect.width, this->_rect.height);
    this->updatePosition();
}
void Canvas::onReset()
{
    this->updatePosition();
}
void Canvas::processEvents()
{
    while (this->_node->hasEvents()) {
        sptr<SquareEvent> e = this->_node->pop();
        switch(e->binding.binding) {
            case io::back: {
                this->_node->notifyNode(mkptr<SquareEvent>(MSG::POP_MENU_RESTORE), this->_menu->getName());
                break;
            }
            case io::menu: {
                this->_node->notifyNode(mkptr<SquareEvent>(MSG::POP_MENU_RESTORE), this->_menu->getName());
                break;
            }
            default: break;
        }
    }
}
void Canvas::updatePosition()
{
    // todo -- turn into a switch and add more anchoring options eventually
    if (this->_ast.anchor == Widgets::CENTER) {
        this->_rect.center = this->_menu->getCenter();
    }
    this->__sprite_surf.setPosition(this->_rect.pos);
}
void Canvas::renderAll(std::vector<RenderedWidget*>& to_render)
{
    this->__surface.clear(sf::Color::Transparent);
    this->__surface.draw(__img_sprite);
    for (auto wdgt : to_render) {
        wdgt->render(this->__surface);
    }
    this->__surface.display();
    this->__sprite_surf.setTexture(this->__surface.getTexture());
}
const sf::Sprite& Canvas::getSurfaceSprite() const
{
    return this->__sprite_surf;
}

}
