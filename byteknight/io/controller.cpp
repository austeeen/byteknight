#include "controller.hpp"

namespace bt
{
Controller::Controller(): node("controller")
{
    node.createChannel("gui_channel");
    node.createChannel("inst_channel");
}
Controller::~Controller()
{
    destroy(input_device);
}
void Controller::setUp()
{
    std::vector<int> cons;
    if (joy::connected_joys(cons)) {
        msg("Controller::setUp", "%d connected controller(s)", (int) cons.size());
        input_device = new Joystick(cons);
    }
    else {
        input_device = new Keyboard();
    }
}
void Controller::emitInputState()
{
    input_device->update();
    for (io::binding b = 0; b < io::NBINDS; b++) {
        switch(input_device->get(b)) {
            case io::pressed_s: {
                node.notifyChannel(mkptr<SquareEvent>(MSG::CTLR_PRESSED, BindingEvent{b}));
                break;
            }
            // dont care about released events right now
            /*
            case io::released_s: {
                node.notifyChannel(mkptr<SquareEvent>(MSG::CTLR_RELEASED, BindingEvent{b}));
                break;
            }
            */
        }
    }
}
void Controller::switchNodeChannel(const std::string& chn_name)
{
    this->node.setChannel(chn_name);
}
}
