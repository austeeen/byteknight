#include "event_core.hpp"

const std::string SquareEvent::tostr() const {
    std::string ret = "";

    if (msg_str != "")
        ret += msg_str;

    for (auto [msg_en_str, msg_en] : MSGTBL) {
        if (msg_en == this->msg) {
            ret += " " + msg_en_str;
            break;
        }
    }

    if (binding.binding != io::none)
        ret += " " + (std::string) io::str_bindings[binding.binding];

    switch (binding.dir) {
        case bt::dir4::up: { ret += " up"; break; }
        case bt::dir4::down: { ret += " down"; break; }
        case bt::dir4::left: { ret += " left"; break; }
        case bt::dir4::right: { ret += " right"; break; }
        default: break;
    }

    return ret;
}
std::ostream& SquareEvent::operator<<(std::ostream &os) {
    os << this->tostr();
    return os;
}
