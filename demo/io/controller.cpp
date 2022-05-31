#include "controller.hpp"


Controller::Controller()
{
    input_states = new io::state[io::NBINDS];
}
Controller::~Controller()
{
    // SQ::destroy(input_device);
    delete input_device;
    input_device = nullptr;
    delete input_states;
    input_states = nullptr;
}
void Controller::setUp()
{
    std::vector<int> cons;
    if (joy::connected_joys(cons)) {
        std::cout << cons.size() << " connected controller(s).\n";
        input_device = new Joystick(cons);
    }
    else {
        input_device = new Keyboard();
    }
}
void Controller::emitInputState()
{
    input_device->update();
    input_states[io::left]   = input_device->get(io::left);
    input_states[io::right]  = input_device->get(io::right);
    input_states[io::down]   = input_device->get(io::down);
    input_states[io::up]     = input_device->get(io::up);
    input_states[io::select] = input_device->get(io::select);
    input_states[io::back]   = input_device->get(io::back);
    input_states[io::menu]   = input_device->get(io::menu);
    input_states[io::quit]   = input_device->get(io::quit);

    // emit input_states to the network
}
io::state* Controller::getInputState()
{
    emitInputState();
    return input_states;
}
