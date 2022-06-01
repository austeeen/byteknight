#include "engine.hpp"
#include "utils/benchmark.hpp"

namespace bt
{
ByteEngine::ByteEngine() : __errstate(ENGINESTATE::NO_STATE)
{
    Benchmarker::start();
    m_game_manager = new GameManager();
}
ByteEngine::~ByteEngine()
{
    destroy(m_game_manager);
}
void ByteEngine::build()
{
    __errstate = ENGINESTATE::BUILD;
    msg("ByteEngine::build", "building...");
    Benchmarker::startBuild();
    throwForNullPtr(m_game_manager, GETNAME(m_game_manager));
    m_game_manager->build();
}
void ByteEngine::startUp()
{
    __errstate = ENGINESTATE::STARTUP;
    msg("ByteEngine::startUp", "starting up...");
    throwForNullPtr(m_game_manager, GETNAME(m_game_manager));
    m_game_manager->startUp();
    Benchmarker::stopBuild();
}
void ByteEngine::run()
{
    __errstate = ENGINESTATE::RUN;
    msg("ByteEngine::run", "running...");
    throwForNullPtr(m_game_manager, GETNAME(m_game_manager));
    m_game_manager->onRun();
}
void ByteEngine::exit()
{
    __errstate = ENGINESTATE::EXIT;
    msg("ByteEngine::exit", "exiting...");
    throwForNullPtr(m_game_manager, GETNAME(m_game_manager));
    m_game_manager->onExit();
    Benchmarker::stop();
}
void ByteEngine::exceptionThrown(int &cur_state)
{
    cur_state = __errstate;
    switch(__errstate)
    {
        case ENGINESTATE::NO_STATE: __printError("NO STATE"); break;
        case ENGINESTATE::BUILD:    __printError("BUILD STATE"); break;
        case ENGINESTATE::STARTUP:  __printError("STARTUP STATE"); break;
        case ENGINESTATE::RUN:      __printError("RUN STATE"); break;
        case ENGINESTATE::EXIT:     __printError("EXIT STATE"); break;
        default: __printError("UNKNOWN STATE");
    }
}
void ByteEngine::__printError(const std::string &str_state)
{
    err("ByteEngine", "%d >> %s", __errstate, str_state.c_str());
}
}
