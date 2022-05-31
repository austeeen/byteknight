#ifndef CORE_WDGT_HPP
#define CORE_WDGT_HPP

#include "common.hpp"

namespace Widgets {
    const float GUI_SCALE_FACTOR = 0.5;
    typedef unsigned int ID;
    const ID BUTTON = 0;
    const ID CANVAS = 1;
    const ID CURSOR = 2;
    static const std::map<std::string, ID> IDMAP {
        {"button", Widgets::BUTTON},
        {"canvas", Widgets::CANVAS},
        {"cursor", Widgets::CURSOR}
    };

    typedef unsigned int anchor;
    const anchor TOPLEFT = 0;
    const anchor TOP = 1;
    const anchor TOPRIGHT = 2;
    const anchor LEFT = 3;
    const anchor CENTER = 4;
    const anchor RIGHT = 5;
    const anchor BOTTOMLEFT = 6;
    const anchor BOTTOM = 7;
    const anchor BOTTOMRIGHT = 8;
    const anchor NONE = 9;
    static const std::map<std::string, anchor> ANCHORTBL {
        {"TOPLEFT", TOPLEFT},
        {"TOP", TOP},
        {"TOPRIGHT", TOPRIGHT},
        {"LEFT", LEFT},
        {"CENTER", CENTER},
        {"RIGHT", RIGHT},
        {"BOTTOMLEFT", BOTTOMLEFT},
        {"BOTTOM", BOTTOM},
        {"BOTTOMRIGHT", BOTTOMRIGHT}
    };
}

#endif // CORE_WDGT_HPP
