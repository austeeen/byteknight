#include "widget.hpp"

namespace bt::gui
{
/**************************************************************************************************/
/* WIDGET */
Widget::Widget(Menu* menu, SceneContext* scene_context, const WidgetAsset &wdgt_ast):
_menu(menu), _scene_context(scene_context), _ast(wdgt_ast)
{}
Widget::~Widget()
{
    _menu = nullptr;
    _scene_context = nullptr;
}
void Widget::updatePosition()
{}
const rect& Widget::getRect() const
{
    return this->_rect;
}
/**************************************************************************************************/
/* REACTIVE WIDGET */
ReactiveWidget::ReactiveWidget(const WidgetAsset& wdgt_ast)
{
    _action = new SquareEvent(wdgt_ast.action_msg);
}
ReactiveWidget::~ReactiveWidget()
{
    destroy(_action);
}
const sptr<SquareEvent> ReactiveWidget::getEvent() const
{
    return mkptr<SquareEvent>(*this->_action);
}

/**************************************************************************************************/
/* TARGETABLE WIDGET */
TargetableWidget::TargetableWidget(const WidgetAsset& wdgt_ast):
ReactiveWidget(wdgt_ast), _name(wdgt_ast.name)
{
    _neighbors[dir4::up] = nullptr;
    _neighbors[dir4::right] = nullptr;
    _neighbors[dir4::down] = nullptr;
    _neighbors[dir4::left] = nullptr;
}
TargetableWidget::~TargetableWidget()
{
    _neighbors[dir4::up] = nullptr;
    _neighbors[dir4::right] = nullptr;
    _neighbors[dir4::down] = nullptr;
    _neighbors[dir4::left] = nullptr;
}
void TargetableWidget::setNeighbor(dir4 dir, TargetableWidget *t)
{
    printf("setting: %s:%d -> %s\n", this->_name.c_str(), (int) dir, t->getName().c_str());
    this->_neighbors[dir] = t;
}
bool TargetableWidget::hasNeighbor(dir4 d)
{
    return this->_neighbors[d] != nullptr;
}
TargetableWidget* TargetableWidget::getNeighbor(dir4 d)
{
    return this->_neighbors[d];
}
const std::string& TargetableWidget::getName() const
{
    return this->_name;
}

/**************************************************************************************************/
/* EVENTFUL WIDGET */
EventfulWidget::EventfulWidget(const WidgetAsset& wdgt_ast):
_node(new Node(wdgt_ast.name))
{
    this->_node->subscribe("controller", "gui_channel");
}
EventfulWidget::~EventfulWidget()
{
    destroy(_node);
}

/**************************************************************************************************/
/* UPDATED WIDGET */

/**************************************************************************************************/
/* RENDERED WIDGET */
RenderedWidget::RenderedWidget(const WidgetAsset& wdgt_ast):
_sprite(new sf::Sprite())
{
    _sprite->setTexture(wdgt_ast.img_texture);
    if (wdgt_ast.texture_rect.exists()) {
        sf::FloatRect texture_rect = wdgt_ast.texture_rect;
        if (wdgt_ast.flip_sprite) {
            std::cout << "flipping sprite" << std::endl;
            texture_rect.left += texture_rect.width;
            texture_rect.width = -texture_rect.width;
        }
        _sprite->setTextureRect((sf::IntRect) texture_rect);
    }
}
RenderedWidget::~RenderedWidget()
{
    destroy(this->_sprite);
}
}
