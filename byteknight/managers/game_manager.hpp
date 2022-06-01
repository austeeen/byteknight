#ifndef CTL_GAME_HPP
#define CTL_GAME_HPP

#include "common.hpp"
#include "context/game_context.hpp"
#include "scene_manager.hpp"

namespace bt
{
class GameManager
{
public:
    GameManager();
    ~GameManager();
    void build();
    void startUp();
    void onRun();
    void onExit();
    void onReset();

private:
    std::string next_scene = "";
    GameContext *m_game_context;
    SceneManager *m_scene_manager;
};
}

#endif // CTL_GAME_HPP
