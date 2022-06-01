#ifndef SCN_MENU_HPP
#define SCN_MENU_HPP

#include "common.hpp"
#include "scene.hpp"
#include "context/scene_context.hpp"
#include "assets/scene_assets.hpp"

namespace bt
{

namespace gui
{
    class Widget;
    class TargetableWidget;
    class ReactiveWidget;
    class EventfulWidget;
    class UpdatedWidget;
    class RenderedWidget;
    class Canvas;
}

class Menu: public Scene
{
public:
    Menu(SceneContext* scene_context, const MenuAsset* menu_ast);
    ~Menu() override;
    void build() override;
    void setUp() override;
    void updateInput() override;
    void processEvents() override;
    void update(const float dt) override;
    void lateUpdate() override;
    void render(sf::RenderWindow* window) override;

    void onStart() override;
    void onExit() override;
    void onReset() override;

    void setActive() override;
    void setPaused() override;
    void setFrozen() override;
    void setInactive() override;

    const std::string& getName() const;
    const sf::Vector2f& getCenter() const;
    template<class WDGT> void add(WDGT* wdgt);
    void createSurface(const sf::Vector2f size);
    void getTargetables(std::vector<gui::TargetableWidget*>& targets);

private:
    const MenuAsset* __menu_ast;
    gui::Canvas* __canvas; // menu must include canvas widget.
    std::map<Widgets::ID, gui::Widget*> __widgets;
    std::vector<gui::TargetableWidget*> __targetable_stack;
    std::vector<gui::ReactiveWidget*> __reactive_stack;
    std::vector<gui::EventfulWidget*> __event_stack;
    std::vector<gui::UpdatedWidget*> __update_stack;
    std::vector<gui::RenderedWidget*> __render_stack;

};

}

#endif // SCN_MENU_HPP
