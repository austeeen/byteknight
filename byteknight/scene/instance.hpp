#ifndef SCN_INSTANCE_HPP
#define SCN_INSTANCE_HPP

#include "common.hpp"
#include "scene.hpp"
#include "context/scene_context.hpp"
#include "assets/scene_assets.hpp"
#include "properties/stateful.hpp"
#include "states/instance_states.hpp"
#include "layers/object_layer.hpp"
#include "layers/tile_layer.hpp"
#include "layers/backdrop_layer.hpp"

namespace bt
{
class Instance: public Scene, public Stateful<Instance>
{
    friend class StartUp<Instance>;
    friend class Running<Instance>;
    friend class TearDown<Instance>;
public:
    Instance(SceneContext* scene_context, const InstanceAsset* inst_ast);
    ~Instance() override;
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

private:
    const InstanceAsset* inst_ast;
    std::vector<LayerBase*> layers;
    std::vector<LayerBase*> event_layers;
    std::vector<LayerBase*> rendered_layers;
    BackdropLayer* board_layer;
    TileLayer* tile_layer;
    ObjectLayer* object_layer;
};
}
#endif // SCN_INSTANCE_HPP
