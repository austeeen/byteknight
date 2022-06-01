#ifndef CTX_GAME_CONTEXT_HPP
#define CTX_GAME_CONTEXT_HPP

#include "common.hpp"
#include "scene_context.hpp"
#include "io/controller.hpp"
#include "factory/asset_factory.hpp"

namespace bt
{
class GameContext
{
public:
    GameContext();
    ~GameContext();
    void build();
    void setUp();
    void windowExited();

    bool windowStillOpen() {
        return  m_window.isOpen();
    };
    sf::RenderWindow& getWindow() {
        return m_window;
    };
    Controller* controller() { return ctlr; }
    ResourceFactory* rsrc_factory;
    AssetFactory* ast_factory;

private:
    std::string config_fp;
    sf::RenderWindow m_window;
    Controller* ctlr;
};
}

#endif // CTX_GAME_CONTEXT_HPP
