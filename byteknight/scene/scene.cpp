#include "scene.hpp"

namespace bt
{
Scene::Scene() : _name("NO NAME"), node(nullptr)
{}
Scene::Scene(SceneContext* scene_context, const std::string& name) :
scene_context(scene_context),
_name(name),
controller(scene_context->getController())
{}
Scene::~Scene()
{
    scene_context = nullptr;
    controller = nullptr;
    destroy(node);
}
}
