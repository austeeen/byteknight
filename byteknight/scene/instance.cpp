#include "instance.hpp"

namespace bt
{

Instance::Instance(SceneContext *scene_context, const InstanceAsset* inst_ast) :
Scene(scene_context, inst_ast->name), inst_ast(inst_ast)
{

    this->registerState(statekey::startup, new StartUp<Instance>(this));
    this->registerState(statekey::running, new Running<Instance>(this));
    this->registerState(statekey::teardown, new TearDown<Instance>(this));

    this->node = new Node("instance");
    this->node->subscribe("controller", "inst_channel");

    scene_context->setSceneData(inst_ast->scenedata);
    board_layer = new BackdropLayer(this->_name, scene_context, inst_ast->backdrop_lyr_ast);
    tile_layer = new TileLayer(this->_name, scene_context, inst_ast->tile_lyr_ast);
    object_layer = new ObjectLayer(this->_name, scene_context, inst_ast->object_lyr_ast);
    layers.push_back(board_layer);
    layers.push_back(tile_layer);
    layers.push_back(object_layer);
    event_layers.push_back(object_layer);
    rendered_layers.push_back(board_layer);
    rendered_layers.push_back(object_layer);

    this->switchState(statekey::startup);
}
Instance::~Instance()
{
    scene_context = nullptr;
    controller = nullptr;
    inst_ast = nullptr;
    event_layers.clear();
    rendered_layers.clear();
    for (auto lyr : layers)
        destroy(lyr);
    layers.clear();
    destroy(node);
}
void Instance::build()
{
    if(layers.empty())
        warn("Instance::build", "layers vector is empty");
    for (auto lyr : layers)
        lyr->build();
}
void Instance::setUp()
{
    if(layers.empty())
        warn("Instance::setUp", "layers vector is empty");

    this->_view = sf::View((sf::FloatRect) this->inst_ast->scenedata.pxl_size);
    std::vector<GameObject*> objs;
    object_layer->getAllObjects(objs);
    tile_layer->assign(objs);
    for (auto lyr : layers)
        lyr->setUp();
}
void Instance::updateInput()
{
    controller->emitInputState();
}
void Instance::processEvents()
{
    while (node->hasEvents()) {
        sptr<SquareEvent> e = this->node->pop();
        this->_cur_state->next(e);
    }

    for (auto lyr : event_layers)
        lyr->processEvents();
}
void Instance::update(const float dt)
{
    this->_cur_state->update(dt);
    for (auto lyr : layers)
        lyr->update(dt);
}
void Instance::lateUpdate()
{
    for (auto lyr : layers)
        lyr->lateUpdate();
}
void Instance::render(sf::RenderWindow* window)
{
    window->setView(this->_view);
    for (auto lyr : rendered_layers) {
        lyr->render(window);
    }
}
void Instance::onStart()
{
    if(layers.empty())
        warn("Instance::onStart", "layers vector is empty");
    for (auto lyr : layers) {
        lyr->onStart();
    }
    this->switchState(statekey::running);
}
void Instance::onExit()
{
    if(layers.empty())
        warn("Instance::onExit", "layers vector is empty");
    for (auto lyr : layers) {
        lyr->onExit();
    }
}
void Instance::onReset()
{
    if(layers.empty())
        warn("Instance::onReset", "layers vector is empty");
    for (auto lyr : layers) {
        lyr->onReset();
    }
}
void Instance::setActive()
{
    this->controller->switchNodeChannel("inst_channel");
    if(layers.empty())
        warn("Instance::setActive", "layers vector is empty");
    for (auto lyr : layers) {
        lyr->setActive();
    }
}
void Instance::setPaused()
{
    if(layers.empty())
        warn("Instance::setPaused", "layers vector is empty");
    for (auto lyr : layers) {
        lyr->setPaused();
    }
}
void Instance::setFrozen()
{
    if(layers.empty())
        warn("Instance::setFrozen", "layers vector is empty");
    for (auto lyr : layers) {
        lyr->setFrozen();
    }
}
void Instance::setInactive()
{
    if(layers.empty())
        warn("Instance::setInactive", "layers vector is empty");
    for (auto lyr : layers) {
        lyr->setInactive();
    }
}
}
