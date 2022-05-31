#include "game_context.hpp"

GameContext::GameContext()
{
    rsrc_factory = new ResourceFactory("res/meta.cfg.json");
    ast_factory = new AssetFactory(rsrc_factory);
    ctlr = new Controller();
}
GameContext::~GameContext()
{
    SQ::destroy(ast_factory);
    SQ::destroy(rsrc_factory);
    SQ::destroy(ctlr);
}
void GameContext::build()
{
    SQ::msg("GameContext::build", "building...");
    rsrc_factory->build();
    ast_factory->build();

    // from config file:
        // set icon
    // m_window.create(sf::VideoMode(800, 600), root.get("window_name", "NO TITLE").asString());

    m_window.create(sf::VideoMode(800, 600), "NO TITLE");
    m_window.setVerticalSyncEnabled(true);
    m_window.setKeyRepeatEnabled(false);
}
void GameContext::setUp()
{
    ctlr->setUp();
}
void GameContext::windowExited()
{
    if(m_window.isOpen())
        m_window.close();
    else
        SQ::err("GameContext::windowExited", "tried to close window, but window is not open");
}
