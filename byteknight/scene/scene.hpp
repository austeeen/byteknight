#ifndef SCN_SCENE_HPP
#define SCN_SCENE_HPP

#include "common.hpp"
#include "context/scene_context.hpp"
#include "io/controller.hpp"

class Scene
{
public:
    Scene();
    Scene(SceneContext* scene_context, const std::string& name);
    virtual ~Scene();
    virtual void build() { };
    virtual void setUp() { };
    virtual void updateInput() { };
    virtual void processEvents() { };
    virtual void update(const float dt) { };
    virtual void lateUpdate() { };
    virtual void render(sf::RenderWindow* window) { };

    virtual void tearDown() { };

    virtual void onStart() { };
    virtual void onExit() { };
    virtual void onReset() { };

    virtual void setActive() { };
    virtual void setPaused() { };
    virtual void setFrozen() { };
    virtual void setInactive() { };

protected:
    SceneContext* scene_context;
    const std::string _name;
    Controller* controller;
    Node* node;
    sf::View _view;
    sf::RenderTexture _surface;
};

#endif // SCN_SCENE_HPP
