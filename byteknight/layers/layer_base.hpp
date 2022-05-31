#ifndef LYR_LAYER_HPP
#define LYR_LAYER_HPP

#include "common.hpp"
#include "context/scene_context.hpp"
#include "assets/scene_assets.hpp"

class LayerBase
{
public:
    LayerBase(const std::string& name, SceneContext* scene_context, const LayerAsset &lyr_ast):
    scene_name(name), scene_context(scene_context), lyr_ast(lyr_ast)
    {};
    virtual ~LayerBase() {
        scene_context = nullptr;
    };
    virtual void build() { };
    virtual void setUp() { };
    virtual void processEvents() { };
    virtual void update(const float dt) { };
    virtual void lateUpdate() { };
    virtual void render(sf::RenderWindow* window) { };

    virtual void onStart() { };
    virtual bool canExit() { return true; }
    virtual void onExit() { };
    virtual void onReset() { };

    virtual void setActive() { };
    virtual void setPaused() { };
    virtual void setFrozen() { };
    virtual void setInactive() { };

    const std::string& name() const { return lyr_ast.name; }
    const LayerAsset* getAsset() { return &lyr_ast; }
    SceneContext* getContext() { return scene_context; }
    Meta::gamedata& getSceneData() { return scene_context->getSceneData(); }
protected:
    const std::string scene_name;
    SceneContext* scene_context;
    const LayerAsset lyr_ast;
};

#endif // LYR_LAYER_HPP
