#ifndef WGT_CANVAS_HPP
#define WGT_CANVAS_HPP

#include "widget.hpp"

namespace bt::gui
{

class Canvas: public EventfulWidget
{
public:
    Canvas(Menu* menu, SceneContext* scene_context, const WidgetAsset& wdgt_ast);
    ~Canvas() override;
    void setUp() override;
    void onReset() override;
    void processEvents() override;
    void updatePosition() override;
    void renderAll(std::vector<RenderedWidget*>& to_render);
    const sf::Sprite& getSurfaceSprite() const;

private:
    sf::Sprite __img_sprite;
    sf::Sprite __sprite_surf;
    sf::RenderTexture __surface;
};

}
#endif // WGT_CANVAS_HPP
