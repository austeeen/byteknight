#ifndef CORE_OBJ_HPP
#define CORE_OBJ_HPP

#include "common.hpp"

namespace Groups {
    typedef unsigned int ID;
    const unsigned int TOTAL_TEAMS = 2;
    const ID RED_TEAM = 0;
    const ID BLUE_TEAM = 1;
    const ID NO_TEAM = -1;
    static const std::map<std::string, ID> IDMAP {
        {"red_team", Groups::RED_TEAM},
        {"blue_team", Groups::BLUE_TEAM}
    };
}

namespace Object {
    typedef unsigned int ID;
    const ID CURSOR    = 0;
    const ID GAMEPIECE = 1;
    static const std::map<std::string, ID> IDMAP {
        {"cursor", Object::CURSOR},
        {"game_piece", Object::GAMEPIECE}
    };
}

#endif //CORE_OBJ_HPP
