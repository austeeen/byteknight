#ifndef SQR_ENGINE_HPP
#define SQR_ENGINE_HPP

#include "common.hpp"
#include "game_manager.hpp"

class SquareEngine
{
public:
    SquareEngine();
    ~SquareEngine();
    void build();
    void startUp();
    void run();
    void exit();

    void exceptionThrown(int &cur_state);

private:
    GameManager *m_game_manager;
    int __errstate;

    void __printError(const std::string &str_state);

};

#endif // SQR_ENGINE_HPP
