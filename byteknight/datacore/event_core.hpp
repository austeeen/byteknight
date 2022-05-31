#ifndef CORE_EVENT_HPP
#define CORE_EVENT_HPP

#include "common.hpp"
#include "math/math.hpp"
#include "object_core.hpp"
#include "io_core.hpp"

enum class MSG {
    NO_EVENT,
    WINDOW_QUIT,
    NEW_GAME,
    EXIT_GAME,
    GAME_OVER,
    RESUME_GAME,
    POP_MENU,
    POP_MENU_RESTORE,
    TEAM_WINS,
    OPEN_PAUSE_MENU,
    OPEN_OPTIONS,
    TOGGLE_PAUSE_MENU,
    EXIT_MAIN_MENU,
    CTLR_PRESSED,
    CTLR_RELEASED,
    TEAM_LOST,
    TURN_DONE,
    CURSOR_MOVE,
    CURSOR_STOP,
    CURSOR_HOVER,
    CURSOR_NOT_HOVERING,
    CURSOR_SELECTED,
    CURSOR_DESELECTED,
    SET_HOVERED,
    SET_NOT_HOVERED,
    SET_SELECTED,
    SET_DESELECTED,
    MOVE_GAME_PIECE,
    GAME_PIECE_IDLE,
    KILL_GAME_PIECE
};

static const std::map<std::string, MSG> MSGTBL {
    {"NO_EVENT", MSG::NO_EVENT},
    {"WINDOW_QUIT", MSG::WINDOW_QUIT},
    {"NEW_GAME", MSG::NEW_GAME},
    {"EXIT_GAME", MSG::EXIT_GAME},
    {"GAME_OVER", MSG::GAME_OVER},
    {"RESUME_GAME", MSG::RESUME_GAME},
    {"POP_MENU", MSG::POP_MENU},
    {"POP_MENU_RESTORE", MSG::POP_MENU_RESTORE},
    {"TEAM_WINS", MSG::TEAM_WINS},
    {"OPEN_PAUSE_MENU", MSG::OPEN_PAUSE_MENU},
    {"OPEN_OPTIONS", MSG::OPEN_OPTIONS},
    {"TOGGLE_PAUSE_MENU", MSG::TOGGLE_PAUSE_MENU},
    {"EXIT_MAIN_MENU", MSG::EXIT_MAIN_MENU},
    {"CTLR_PRESSED", MSG::CTLR_PRESSED},
    {"CTLR_RELEASED", MSG::CTLR_RELEASED},
    {"TEAM_LOST", MSG::TEAM_LOST},
    {"TURN_DONE", MSG::TURN_DONE},
    {"CURSOR_MOVE", MSG::CURSOR_MOVE},
    {"CURSOR_STOP", MSG::CURSOR_STOP},
    {"CURSOR_HOVER", MSG::CURSOR_HOVER},
    {"CURSOR_NOT_HOVERING", MSG::CURSOR_NOT_HOVERING},
    {"CURSOR_SELECTED", MSG::CURSOR_SELECTED},
    {"CURSOR_DESELECTED", MSG::CURSOR_DESELECTED},
    {"SET_HOVERED", MSG::SET_HOVERED},
    {"SET_NOT_HOVERED", MSG::SET_NOT_HOVERED},
    {"SET_SELECTED", MSG::SET_SELECTED},
    {"SET_DESELECTED", MSG::SET_DESELECTED},
    {"MOVE_GAME_PIECE", MSG::MOVE_GAME_PIECE},
    {"GAME_PIECE_IDLE", MSG::GAME_PIECE_IDLE},
    {"KILL_GAME_PIECE", MSG::KILL_GAME_PIECE}
};

struct BindingEvent
{
    BindingEvent(): binding(io::none), dir(SQ::dir4::none) {}
    BindingEvent(io::binding b): binding(b), dir(SQ::dir4::none) {
        switch (b) {
            case io::up: { dir = SQ::dir4::up; break; }
            case io::down: { dir = SQ::dir4::down; break; }
            case io::left: { dir = SQ::dir4::left; break; }
            case io::right: { dir = SQ::dir4::right; break; }
            default: { dir = SQ::dir4::none; break; }
        }
    }
    io::binding binding;
    SQ::dir4 dir;
};

class Tile;

struct SquareEvent
{
    const MSG msg;
    const std::string msg_str;
    const BindingEvent binding;
    const Object::ID object_id;
    Tile* const tile;

    SquareEvent():
        msg(MSG::NO_EVENT),
        msg_str(""),
        binding(BindingEvent()),
        object_id(0),
        tile(nullptr)
    {}

    SquareEvent(MSG msg):
        msg(msg),
        msg_str(""),
        binding(BindingEvent()),
        object_id(0),
        tile(nullptr)
    {}

    SquareEvent(MSG msg, const std::string msg_str):
        msg(msg),
        msg_str(msg_str),
        binding(BindingEvent()),
        object_id(0),
        tile(nullptr)
    {}

    SquareEvent(MSG msg, Object::ID obj_id):
        msg(msg),
        msg_str(""),
        binding(BindingEvent()),
        object_id(obj_id),
        tile(nullptr)
    {}

    SquareEvent(MSG msg, BindingEvent b):
        msg(msg),
        msg_str(""),
        binding(b),
        object_id(0),
        tile(nullptr)
    {}

    SquareEvent(MSG msg, Tile *t):
        msg(msg),
        msg_str(""),
        binding(BindingEvent()),
        object_id(0),
        tile(t)
    {}

    SquareEvent(const std::string& msg_str):
        msg(MSG::NO_EVENT),
        msg_str(msg_str),
        binding(BindingEvent()),
        object_id(0),
        tile(nullptr)
    {}

    SquareEvent(const SquareEvent& other):
        msg(other.msg),
        msg_str(other.msg_str),
        binding(other.binding),
        object_id(other.object_id),
        tile(other.tile)
    {}

    // ~SquareEvent() {}

    const std::string tostr() const;
    std::ostream &operator<<(std::ostream &os);
};



#endif // DT_TYPE_HPP
