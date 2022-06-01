#ifndef INP_CONTROLLER_H
#define INP_CONTROLLER_H

#include "common.hpp"
#include "events/event_node.hpp"
#include "io_devices.hpp"

namespace bt
{
class Controller
{
public:
    Controller();
    ~Controller();
    void setUp();
    void emitInputState();
    void switchNodeChannel(const std::string& chn_name);
private:
    bool __joystickConnected(std::vector<int> &cons);

    Node node;
    InputDevice* input_device;
};
}

#endif // INP_CONTROLLER_H
