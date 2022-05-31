#ifndef WGT_BUTTON_HPP
#define WGT_BUTTON_HPP

#include "widget.hpp"

namespace gui
{

class SimpleButton: public TargetableWidget
{
public:
    SimpleButton(Menu* menu, SceneContext* scene_context, const WidgetAsset& wdgt_ast);
    ~SimpleButton() override;
    void setUp() override;
};

}
#endif // WGT_BUTTON_HPP
