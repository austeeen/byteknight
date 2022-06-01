#include <iostream>
#include <exception>
#include <vector>
#include "utils/logging.hpp"
#include "utils/exceptions.hpp"
#include "utils/benchmark.hpp"
#include "engine/engine.hpp"

typedef void(bt::ByteEngine::*btstep)();

int return_state = 0;
bt::LOG::loglevel bt::LOG::lvl = bt::LOG::loglevel::dbg;

void handle_exception(bt::ByteEngine *bt_eng, const std::string& msg) {
    bt_eng->exceptionThrown(return_state);
    std::cout << "----- EXCEPTION -----" << std::endl;
    std::cout << msg << std::endl;
    std::cout << "----- --------- -----" << std::endl;
}


bool proc(btstep func, bt::ByteEngine *bt_eng) {
    try {
        (bt_eng->*func)();
    } catch (bt::SquareExceptionBase &e) {
        handle_exception(bt_eng, e.what());
        return false;
    } catch (const std::exception& ex) {
        handle_exception(bt_eng, ex.what());
        throw ex;
        return false;
    } catch (const std::string& ex) {
        handle_exception(bt_eng, ex);
        throw ex;
        return false;
    } catch (...) {
        handle_exception(bt_eng, "main.cpp -- caught unknown exception");
        return false;
    }
    return true;
}

bool proc_no_excep(btstep func, bt::ByteEngine *bt_eng) {
    (bt_eng->*func)();
    return true;
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        bt::LOG::setlvl(bt::LOG::lvl, std::stoi(argv[1]));
    }

    std::vector<btstep> main_sequence = {
        &bt::ByteEngine::build,
        &bt::ByteEngine::startUp,
        &bt::ByteEngine::run
    };
    bt::ByteEngine *bt_eng = new bt::ByteEngine();
    for (auto p : main_sequence) {
        if (!proc_no_excep(p, bt_eng))
            break;
    }
    proc_no_excep(&bt::ByteEngine::exit, bt_eng);

    delete bt_eng;
    bt_eng = nullptr;

    bt::Benchmarker::report();

    return return_state;
}
