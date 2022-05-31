#ifndef CTL_SCENE_HPP
#define CTL_SCENE_HPP

#include "common.hpp"
#include "context/game_context.hpp"
#include "context/scene_context.hpp"
#include "scene/scene.hpp"
#include "scene/instance.hpp"
#include "scene/menus.hpp"

class GameManager;

class SceneManager
{
public:
    SceneManager(GameContext *game_context);
    ~SceneManager();
    void build();
    void startUp();
    void onRun();
    void onExit();
    void onReset();

    void loadSceneGroup(const std::string &group_name);
    void loadScenes();

    void pushScene(const std::string& name);
    void popScene();
    void freezePaused();
    void restoreFrozen();

    void processFrame();

private:
    inline Scene* _get(const std::string& name) const { return __scene_table.at(name); };
    inline Scene* _active() { return __scene_table[active_scene_name]; };

    void __startScenes();
    void __exitScenes();
    void __resetScenes();

    bool __pollWindowEvents();

    Node* node;
    GameContext* game_context;
    SceneContext* __scene_context;

    sf::Clock fClock;
    float dt;
    sf::RenderWindow* window;

    std::map<const std::string, Scene*> __scene_table;
    std::deque<std::string> paused;
    std::deque<std::string> frozen;
    std::string active_scene_name;

};

#endif // CTL_SCENE_HPP
