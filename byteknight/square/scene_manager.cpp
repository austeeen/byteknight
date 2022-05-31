#include "scene_manager.hpp"

SceneManager::SceneManager(GameContext *game_context) :
node(new Node("scene_manager")),
game_context(game_context),
__scene_context(nullptr),
window(nullptr),
active_scene_name("")
{
    SQ::throwForNullPtr(this->game_context, GETNAME(this->game_context));
    window = &this->game_context->getWindow();
}
SceneManager::~SceneManager()
{
    SQ::destroy(node);

    for (auto& [name, scene] : this->__scene_table) {
        SQ::destroy(scene);
    }
    this->__scene_table.clear();
    paused.clear();
    frozen.clear();
    active_scene_name = "";

    SQ::destroy(__scene_context);
    window = nullptr;
    game_context = nullptr;
}
void SceneManager::build()
{
    SQ::throwForNullPtr(game_context, GETNAME(game_context));
    game_context->build();
}
void SceneManager::startUp()
{
    SQ::throwForNullPtr(game_context, GETNAME(game_context));
    game_context->setUp();
}
void SceneManager::onRun()
{
    SQ::throwForNullPtr(game_context, GETNAME(game_context));
    SQ::throwForNullPtr(window, GETNAME(window));
    SQ::throwForNullPtr(__scene_context, GETNAME(__scene_context));
    if (active_scene_name == "")
        throw SQ::BadValueException("SceneManager::onRun", "active_scene_id");
    SQ::throwForNullPtr(_active(), "active scene");

    __startScenes();
    dt = fClock.restart().asSeconds();
}
void SceneManager::onExit()
{
    __exitScenes();
    game_context->windowExited();
}
void SceneManager::onReset()
{
    __resetScenes();
}
void SceneManager::loadSceneGroup(const std::string& group_name)
{
    __scene_context =  new SceneContext(game_context, group_name);
    for (const std::string& scn_name : __scene_context->getSceneNames())
    {
        SceneAssetBase* scn_ast = game_context->ast_factory->get<SceneAssetBase>(scn_name);
        if (scn_ast->type == "instance") {
            this->__scene_table[scn_name] = new Instance(__scene_context, static_cast<InstanceAsset*>(scn_ast));
        } else if (scn_ast->type == "menu") {
            this->__scene_table[scn_name] = new gui::Menu(__scene_context, static_cast<MenuAsset*>(scn_ast));
        } else {
            SQ::warn("SceneManager::loadSceneGroup", "scene %s has unknown scene type '%s'", scn_name.c_str(), scn_ast->type.c_str());
        }
    }

    if(this->__scene_table.empty())
        SQ::warn("SceneManager::loadSceneGroup", "scene_table is empty");
}
void SceneManager::loadScenes()
{
    SQ::throwForNullPtr(__scene_context, GETNAME(__scene_context));
    for (auto& [id, scene] : this->__scene_table)
        scene->build();
    for (auto& [id, scene] : this->__scene_table)
        scene->setUp();
}
void SceneManager::__startScenes()
{
    for (auto [scn_name, scn] : this->__scene_table) {
        scn->onStart();
    }
}
void SceneManager::__exitScenes()
{
    for (auto [scn_name, scn] : this->__scene_table) {
        scn->onExit();
    }
}
void SceneManager::__resetScenes()
{
    for (auto [scn_name, scn] : this->__scene_table) {
        scn->onReset();
    }
}
void SceneManager::pushScene(const std::string& name)
{
    if (this->__scene_table.count(name) == 0) {
        SQ::warn("SceneManager::pushScene", "scene name '%s' not in scene table", name.c_str());
        return;
    }

    if (active_scene_name != "") {
        _active()->setPaused();
        paused.push_back(active_scene_name);
    }
    active_scene_name = name;
    _active()->setActive();
}
void SceneManager::popScene()
{
    _active()->setInactive();
    active_scene_name = "";
    if (!paused.empty()) {
        active_scene_name = paused.back();
        _active()->setActive();
        paused.pop_back();
    } else {
        SQ::debug("SceneManager::popScene", "scene group done");
    }
}
void SceneManager::freezePaused()
{
    while (!paused.empty()) {
        std::string n = paused.front();
        _get(n)->setFrozen();
        frozen.push_back(n);
        paused.pop_front();
    }
}
void SceneManager::restoreFrozen()
{
    while (!frozen.empty()) {
        std::string n = frozen.front();
        _get(n)->setPaused();
        paused.push_back(n);
        frozen.pop_front();
    }
}
bool SceneManager::__pollWindowEvents()
{
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            onExit();
            return false;
        }
    }
    return true;
}
void SceneManager::processFrame()
{
    if (!__pollWindowEvents()) {
        return;
    }
    _active()->updateInput();
    _active()->processEvents();
    _active()->update(dt);
    for (auto p : paused) {
        _get(p)->update(dt);
    }
    _active()->lateUpdate();

    while (node->hasEvents()) {
        sptr<SquareEvent> e = this->node->pop();
        switch(e->msg) {
            case MSG::EXIT_GAME: {
                onExit();
                break;
            }
            case MSG::OPEN_PAUSE_MENU: {
                pushScene("pause_menu");
                break;
            }
            case MSG::POP_MENU_RESTORE: {
                popScene();
                break;
            }
            default: break;
        }
    }

    Network::flipEvents();

    window->clear();
    window->setView(window->getDefaultView());
    for (auto f : frozen) {
        _get(f)->render(window);
    }
    for (auto p : paused) {
        _get(p)->render(window);
    }
    _active()->render(window);
    window->display();

    dt = fClock.restart().asSeconds();
}
