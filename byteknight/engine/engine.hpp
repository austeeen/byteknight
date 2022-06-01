#ifndef BYTE_ENGINE_HPP
#define BYTE_ENGINE_HPP

#include "common.hpp"
#include "managers/game_manager.hpp"

namespace bt
{
class ByteEngine
{
public:
    ByteEngine();
    ~ByteEngine();
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
}

#endif // BYTE_ENGINE_HPP
