#include "menus.hpp"
#include "widgets/widget.hpp"
#include "widgets/button.hpp"
#include "widgets/canvas.hpp"
#include "widgets/cursor.hpp"

namespace gui
{

Menu::Menu(SceneContext *scene_context, const MenuAsset* menu_ast) :
Scene(scene_context, menu_ast->name), __menu_ast(menu_ast)
{
    this->node = new Node(this->_name);
    this->_view = scene_context->getWindowView();
    this->_view.zoom(Widgets::GUI_SCALE_FACTOR);
}
Menu::~Menu()
{
    scene_context = nullptr;
    controller = nullptr;
    __menu_ast = nullptr;
    __canvas = nullptr;

    SQ::destroy(node);

    for (auto [id, wdgt] : __widgets) {
        // TODO -- MAKE SURE WIDGETS HAVE PROPER DTOR
        SQ::destroy(wdgt);
    }
    __widgets.clear();
    __targetable_stack.clear();
    __reactive_stack.clear();
    __event_stack.clear();
    __update_stack.clear();
    __render_stack.clear();
}
void Menu::build()
{
    for (const WidgetAsset& wdgt_ast : __menu_ast->widget_assets)
    {
        switch(wdgt_ast.type_id)
        {
            case Widgets::BUTTON: {
                this->__widgets[wdgt_ast.id] = new SimpleButton(this, this->scene_context, wdgt_ast);
                break;
            }
            case Widgets::CANVAS: {
                this->__canvas = new Canvas(this, this->scene_context, wdgt_ast);
                this->__widgets[wdgt_ast.id] = this->__canvas;
                break;
            }
            case Widgets::CURSOR: {
                this->__widgets[wdgt_ast.id] = new Cursor(this, this->scene_context, wdgt_ast);
                break;
            }
            default: { break; }
        }
    }
}
void Menu::setUp()
{
    for (auto [id, wdgt] : __widgets) {
        wdgt->setUp();
    }
}
void Menu::updateInput()
{
    controller->emitInputState();
}
void Menu::processEvents()
{
    while (node->hasEvents()) {
        // todo -- handle menu events (usually events from its widgets)
        sptr<SquareEvent> e = this->node->pop();
        switch(e->msg) {
            case MSG::POP_MENU_RESTORE: {
                this->node->notifyNode(e, "scene_manager");
                break;
            }
            case MSG::OPEN_OPTIONS: {
                this->node->notifyNode(e, "scene_manager");
                break;
            }
            case MSG::EXIT_GAME: {
                this->node->notifyNode(e, "scene_manager");
                break;
            }
            case MSG::EXIT_MAIN_MENU: {
                this->node->notifyNode(e, "scene_manager");
                break;
            }
            default: break;
        }
    }
    for (auto wdgt : __event_stack)
        wdgt->processEvents();
}
void Menu::update(const float dt)
{
    for (auto wdgt : __update_stack)
        wdgt->update(dt);
}
void Menu::lateUpdate()
{
    for (auto [id, wdgt] : __widgets)
        wdgt->lateUpdate();
}
void Menu::render(sf::RenderWindow* window)
{
    this->__canvas->renderAll(__render_stack);
    window->setView(_view);
    window->draw(this->__canvas->getSurfaceSprite());
}
void Menu::onStart()
{}
void Menu::onExit()
{}
void Menu::onReset()
{}
void Menu::setActive()
{
    this->controller->switchNodeChannel("gui_channel");
}
void Menu::setPaused()
{}
void Menu::setFrozen()
{}
void Menu::setInactive()
{}
const std::string& Menu::getName() const
{
    return this->__menu_ast->name;
}
const sf::Vector2f& Menu::getCenter() const
{
    return this->_view.getCenter();
}
template<> void Menu::add<TargetableWidget>(TargetableWidget* wdgt)
{
    __targetable_stack.push_back(wdgt);
}
template<> void Menu::add<ReactiveWidget>(ReactiveWidget* wdgt)
{
    __reactive_stack.push_back(wdgt);
}
template<> void Menu::add<EventfulWidget>(EventfulWidget* wdgt)
{
    __event_stack.push_back(wdgt);
}
template<> void Menu::add<UpdatedWidget>(UpdatedWidget* wdgt)
{
    __update_stack.push_back(wdgt);
}
template<> void Menu::add<RenderedWidget>(RenderedWidget* wdgt)
{
    __render_stack.push_back(wdgt);
}
void Menu::getTargetables(std::vector<TargetableWidget*>& targets)
{
    targets = __targetable_stack;
}

}
