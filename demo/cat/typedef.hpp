#ifndef TYPE_DEF_HPP
#define TYPE_DEF_HPP

#include <SFML/Graphics.hpp>

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

// from cat.png
#define IDLE_ROW 0
#define IDLE_FRAMES 4
#define MOVING_ROW 4
#define MOVING_FRAMES 8

class GameObject;

enum class animstate { idle, moving };

#endif // TYPE_DEF_HPP
