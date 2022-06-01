#include "button.hpp"

namespace bt::gui
{

SimpleButton::SimpleButton(Menu* menu, SceneContext* scene_context, const WidgetAsset& wdgt_ast):
Widget(menu, scene_context, wdgt_ast), TargetableWidget(wdgt_ast)
{
    this->_menu->add<TargetableWidget>(this);
    this->_rect = _ast.position_rect;
    std::cout << this->_ast.name << " rect: "<< this->_rect.tostr() << std::endl;
}
SimpleButton::~SimpleButton()
{}
void SimpleButton::setUp()
{
    this->updatePosition();
}

}
