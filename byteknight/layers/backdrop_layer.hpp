#ifndef LYR_BACKGROUND_HPP
#define LYR_BACKGROUND_HPP

#include "common.hpp"
#include "layer_base.hpp"
#include "utils/math.hpp"

class BackdropLayer: public LayerBase
{
public:
    BackdropLayer(const std::string& name, bt::SceneContext* scene_context, const LayerAsset& lyr_ast);
    ~BackdropLayer() override {};
    void build() override;
    void setUp() override {};
    void setActive() override {};
    void setPaused() override {};
    void setFrozen() override {};
    void setInactive() override {};
    void onReset() override {};
    void processEvents() override {};
    void update(const float dt) override {};
    void lateUpdate() override {};
    void render(sf::RenderWindow* window) override {
        window->draw(vertices, render_texture);
    };

private:
    sf::VertexArray vertices;
    sf::Texture tileset;
    sf::RenderStates render_texture;
};

#endif // LYR_BACKGROUND_HPP
