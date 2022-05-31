#include "cursor.hpp"

namespace gui
{

Cursor::Cursor(Menu* menu, SceneContext* scene_context, const WidgetAsset& wdgt_ast):
Widget(menu, scene_context, wdgt_ast),
EventfulWidget(wdgt_ast), UpdatedWidget(), RenderedWidget(wdgt_ast), __cur_target(nullptr)
{
    this->_menu->add<EventfulWidget>(this);
    this->_menu->add<UpdatedWidget>(this);
    this->_menu->add<RenderedWidget>(this);
}
Cursor::~Cursor()
{
    __targets.clear();
    __cur_target = nullptr;
}
void Cursor::setUp()
{
    this->__setUpTargets();
    this->_rect = this->_ast.position_rect;
    this->updatePosition();
    // self.animation = self.data.get('animation')
}
void Cursor::onReset()
{
    /*
    if self.animation:
        self.animation.reset()
    self.xy = (0, 0)
    self.container.move_cursor()
    */
}
void Cursor::processEvents()
{
    while (this->_node->hasEvents()) {
        sptr<SquareEvent> e = this->_node->pop();
        if (e->binding.dir != SQ::dir4::none) {
            this->setTarget(e->binding.dir);
        }
        else if (e->binding.binding == io::select) {
            this->_node->notifyNode(this->__cur_target->getEvent(), this->_menu->getName());
        }
    }
}
void Cursor::update(const float dt)
{
    /*
    if not self.animation:
        return
    self.animation.update()
    */
    this->_sprite->setPosition(this->_rect.pos);
}
void Cursor::render(sf::RenderTexture& surface)
{
    // std::cout << "cursor render" << std::endl;
    surface.draw(*this->_sprite);
}
void Cursor::updatePosition()
{
    if (this->__cur_target == nullptr) {
        SQ::warn("gui::Cursor::updatePosition", "called but cursor has no current target");
        return;
    }
    // todo -- eventually switch on an anchor to set where it anchors to.
    const SQ::rect trect = this->__cur_target->getRect();
    // case LEFT:
    this->_rect.right = trect.left;
    this->_rect.centery = trect.centery;

    std::cout << "cursor rect: " << this->_rect.tostr() << std::endl;
}
void Cursor::setTarget(SQ::dir4 dir)
{
    if (this->__cur_target->hasNeighbor(dir)) {
        this->__cur_target = this->__cur_target->getNeighbor(dir);
        this->updatePosition();
    }
}
void Cursor::__setUpTargets()
{
    this->_menu->getTargetables(__targets);

    // align targets like tiles -- currently only supports vertical alignment
    for (auto& t : __targets) {
        SQ::rect trect = t->getRect();
        // arbitrarily chose 100 -- could in theory be an issue
        float min_above = 100.0f;
        float min_below = 100.0f;
        for (auto& n : __targets) {
            SQ::rect nrect = n->getRect();
            // this only applies to vertical alignment
            if (nrect.bottom != trect.bottom) {
                float dabv = trect.top - nrect.bottom;
                if (dabv < min_above && dabv > 0.0f) {
                    t->setNeighbor(SQ::dir4::up, n);
                    min_above = dabv;
                }
            }
            // this only applies to vertical alignment
            if (nrect.top != trect.top) {
                float dblw =  nrect.top - trect.bottom;
                if (dblw < min_below && dblw > 0.0f) {
                    t->setNeighbor(SQ::dir4::down, n);
                    min_below = dblw;
                }
            }
        }
    }

    this->__cur_target = __targets[0];
}

}
