#ifndef INP_TYPES_H
#define INP_TYPES_H

#include <string>
#include <iostream>

// idea - break messages up into categories based on what they do / who cares about them

enum class Messages {
    NO_EVENT = 0,
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
    A,
    B,
    X,
    Y,
    L,
    R,
    SL,
    ST,
    DPAD_PRESSED,
    DPAD_RELEASED,
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

struct SquareEvent
{
    // SquareEvent();
    // Messages msg;
    std::string msg_str;
    // DIR4 dir;
    // kwargs ... ?

    std::ostream& operator<<(std::ostream& os) { os << msg_str; return os; }
};

#endif // INP_TYPES_H
