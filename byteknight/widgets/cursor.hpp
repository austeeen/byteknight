#ifndef WGT_CURSOR_HPP
#define WGT_CURSOR_HPP

#include "widget.hpp"

namespace gui
{

class Cursor: public EventfulWidget, public UpdatedWidget, public RenderedWidget
{
public:
    Cursor(Menu* menu, SceneContext* scene_context, const WidgetAsset& wdgt_ast);
    ~Cursor() override;
    void setUp() override;
    void onReset() override;
    void processEvents() override;
    void update(const float dt) override;
    void render(sf::RenderTexture& surface) override;
    void updatePosition() override;

    void setTarget(SQ::dir4 dir);

private:
    void __setUpTargets();
    std::vector<TargetableWidget*> __targets;
    TargetableWidget* __cur_target;
};

}

#endif // WGT_CURSOR_HPP
