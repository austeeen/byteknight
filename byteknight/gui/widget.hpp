#ifndef WGT_BASE_HPP
#define WGT_BASE_HPP

#include "common.hpp"
#include "utils/math.hpp"
#include "context/scene_context.hpp"
#include "assets/gui_assets.hpp"
#include "scene/menus.hpp"
#include "events/event_node.hpp"

namespace bt::gui
{

class Widget
{
public:
    Widget(Menu* menu, SceneContext* scene_context, const WidgetAsset& wdgt_ast);
    virtual ~Widget();
    virtual void setUp() = 0;
    virtual void lateUpdate() { };
    virtual void onActivate() {};
    virtual void onDeactivate() {};
    virtual void onReset() {};
    virtual void updatePosition();
    const rect& getRect() const;

protected:
    Menu* _menu;
    SceneContext* _scene_context;
    WidgetAsset _ast;
    rect _rect;
    sf::Vector2i _padding;
};

/**************************************************************************************************/
class ReactiveWidget: virtual public Widget
{
public:
    ReactiveWidget(const WidgetAsset& wdgt_ast);
    virtual ~ReactiveWidget() override;
    virtual const sptr<SquareEvent> getEvent() const;

protected:
    const SquareEvent* _action;
};

/**************************************************************************************************/
class TargetableWidget: public ReactiveWidget
{
public:
    TargetableWidget(const WidgetAsset& wdgt_ast);
    virtual ~TargetableWidget() override;
    void setNeighbor(dir4 d, TargetableWidget* t);
    bool hasNeighbor(dir4 d);
    TargetableWidget* getNeighbor(dir4 d);
    const std::string& getName() const;

protected:
    TargetableWidget* _neighbors[4];

private:
    const std::string _name;
};

/**************************************************************************************************/
class EventfulWidget : virtual public Widget
{
public:
    EventfulWidget(const WidgetAsset& wdgt_ast);
    virtual ~EventfulWidget() override;
    virtual void processEvents() = 0;

protected:
    Node* _node;
};

/**************************************************************************************************/
class UpdatedWidget: virtual public Widget
{
public:
    virtual void update(const float dt) = 0;
};

/**************************************************************************************************/
class RenderedWidget: virtual public Widget
{
public:
    RenderedWidget(const WidgetAsset& wdgt_ast);
    virtual ~RenderedWidget() override;
    virtual void render(sf::RenderTexture& surface) = 0;

protected:
    sf::Sprite* _sprite;
};
}

#endif // SCN_MENU_HPP
