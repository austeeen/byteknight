#include "engine.hpp"
#include "utils/benchmark.hpp"

SquareEngine::SquareEngine() : __errstate(SQ::ENGINESTATE::NO_STATE)
{
    Benchmarker::start();
    m_game_manager = new GameManager();
}
SquareEngine::~SquareEngine()
{
    SQ::destroy(m_game_manager);
}
void SquareEngine::build()
{
    __errstate = SQ::ENGINESTATE::BUILD;
    SQ::msg("SquareEngine::build", "building...");
    Benchmarker::startBuild();
    SQ::throwForNullPtr(m_game_manager, GETNAME(m_game_manager));
    m_game_manager->build();
}
void SquareEngine::startUp()
{
    __errstate = SQ::ENGINESTATE::STARTUP;
    SQ::msg("SquareEngine::startUp", "starting up...");
    SQ::throwForNullPtr(m_game_manager, GETNAME(m_game_manager));
    m_game_manager->startUp();
    Benchmarker::stopBuild();
}
void SquareEngine::run()
{
    __errstate = SQ::ENGINESTATE::RUN;
    SQ::msg("SquareEngine::run", "running...");
    SQ::throwForNullPtr(m_game_manager, GETNAME(m_game_manager));
    m_game_manager->onRun();
}
void SquareEngine::exit()
{
    __errstate = SQ::ENGINESTATE::EXIT;
    SQ::msg("SquareEngine::exit", "exiting...");
    SQ::throwForNullPtr(m_game_manager, GETNAME(m_game_manager));
    m_game_manager->onExit();
    Benchmarker::stop();
}
void SquareEngine::exceptionThrown(int &cur_state)
{
    cur_state = __errstate;
    switch(__errstate)
    {
        case SQ::ENGINESTATE::NO_STATE: __printError("NO STATE"); break;
        case SQ::ENGINESTATE::BUILD:    __printError("BUILD STATE"); break;
        case SQ::ENGINESTATE::STARTUP:  __printError("STARTUP STATE"); break;
        case SQ::ENGINESTATE::RUN:      __printError("RUN STATE"); break;
        case SQ::ENGINESTATE::EXIT:     __printError("EXIT STATE"); break;
        default: __printError("UNKNOWN STATE");
    }
}
void SquareEngine::__printError(const std::string &str_state)
{
    SQ::err("SquareEngine", "%d >> %s", __errstate, str_state.c_str());
}
