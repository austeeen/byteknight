#include <iostream>
#include <exception>
#include <vector>
#include "utils/logging.hpp"
#include "utils/exceptions.hpp"
#include "utils/benchmark.hpp"
#include "square/engine.hpp"

typedef void(SquareEngine::*sqstep)();

int return_state = 0;
SQ::LOG::loglevel SQ::LOG::lvl = SQ::LOG::loglevel::dbg;

void handle_exception(SquareEngine *sq, const std::string& msg) {
    sq->exceptionThrown(return_state);
    std::cout << "----- EXCEPTION -----" << std::endl;
    std::cout << msg << std::endl;
    std::cout << "----- --------- -----" << std::endl;
}


bool proc(sqstep func, SquareEngine *sq) {
    try {
        (sq->*func)();
    } catch (SQ::SquareExceptionBase &e) {
        handle_exception(sq, e.what());
        return false;
    } catch (const std::exception& ex) {
        handle_exception(sq, ex.what());
        throw ex;
        return false;
    } catch (const std::string& ex) {
        handle_exception(sq, ex);
        throw ex;
        return false;
    } catch (...) {
        handle_exception(sq, "battle.cpp -- caught unknown exception");
        return false;
    }
    return true;
}

bool proc_no_excep(sqstep func, SquareEngine *sq) {
    (sq->*func)();
    return true;
}

int main(int argc, char *argv[])
{

    if (argc > 1) {
        SQ::LOG::setlvl(SQ::LOG::lvl, std::stoi(argv[1]));
    }

    std::vector<sqstep> main_sequence = {
        &SquareEngine::build,
        &SquareEngine::startUp,
        &SquareEngine::run
    };
    SquareEngine *engine = new SquareEngine();
    for (auto p : main_sequence) {
        if (!proc_no_excep(p, engine))
            break;
    }
    proc_no_excep(&SquareEngine::exit, engine);

    delete engine;
    engine = nullptr;

    Benchmarker::report();

    return return_state;
}
