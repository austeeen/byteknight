#include "game_manager.hpp"
#include "utils/benchmark.hpp"

namespace bt
{
GameManager::GameManager()
{
    m_game_context = new GameContext();
    m_scene_manager = new SceneManager(m_game_context);
}
GameManager::~GameManager()
{
    destroy(m_game_context);
    destroy(m_scene_manager);
    Network::shutdown();
}
void GameManager::build()
{
    throwForNullPtr(m_scene_manager, GETNAME(m_scene_manager));
    m_scene_manager->build();
}
void GameManager::startUp()
{
    throwForNullPtr(m_scene_manager, GETNAME(m_scene_manager));
    m_scene_manager->startUp();
    m_scene_manager->loadSceneGroup("test");
    m_scene_manager->loadScenes();
}
void GameManager::onRun()
{
    throwForNullPtr(m_scene_manager, GETNAME(m_scene_manager));
    throwForNullPtr(m_game_context, GETNAME(m_game_context));
    m_scene_manager->pushScene("basic_game");
    m_scene_manager->onRun();
    Benchmarker::startRunning();
    while (m_game_context->windowStillOpen()) {
        Benchmarker::frame_clock.tick();
        m_scene_manager->processFrame();
        Benchmarker::frame_clock.tick();
        Benchmarker::updateFrame();
    }
    Benchmarker::stopRunning();
}
void GameManager::onExit()
{
    throwForNullPtr(m_scene_manager, GETNAME(m_scene_manager));
    // todo - scene manager calls onExit() itself, will want to workout the exit strategy eventually
    // m_scene_manager->onExit();
}
void GameManager::onReset()
{
    throwForNullPtr(m_scene_manager, GETNAME(m_scene_manager));
    m_scene_manager->onReset();
}
}
