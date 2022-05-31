#ifndef INP_CONTROLLER_H
#define INP_CONTROLLER_H

#include "common.hpp"
// #include "utils/util.hpp"
#include "input_types.hpp"
#include "io_devices.hpp"

class Controller
{
public:
    Controller();
    ~Controller();
    void setUp();
    void emitInputState();
    io::state* getInputState();

private:
    bool __joystickConnected(std::vector<int> &cons);

    InputDevice* input_device;
    io::state* input_states;
};


#endif // INP_CONTROLLER_H
