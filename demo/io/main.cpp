#include "common.hpp"
#include "controller.hpp"

// g++ main.cpp bitmask.cpp controller.cpp io_devices.cpp input_types.cpp -lsfml-graphics -lsfml-window -lsfml-system

int main()
{

    Controller ctl;
    ctl.setUp();
    io::state* inputs;

    sf::Clock fps_clock;
    sf::Clock sleep_clock;
    float fps = 1000 / 30; // 60 frames in 1000 ms = duration of frame per ms
    sf::Time felapsed;

    int quit_counter = 0;
    while (quit_counter < 10) {
        inputs = ctl.getInputState();

        for (int i = 0; i < io::NBINDS; i++)
        {
            if (inputs[i] != io::up_s)
            {
                printf("%s -> %s ", io::str_bindings[i], io::str_states[inputs[i]]);
                if (i == io::quit) {
                    quit_counter ++;
                    if (inputs[i] == io::released_s)
                        quit_counter = 0;
                    printf("%d", quit_counter);
                }
                std::cout << std::endl;
                std::cout << std::flush;
            }
        }

        felapsed = fps_clock.restart();

        while (felapsed.asMilliseconds() < fps) {
            felapsed += fps_clock.restart();
        }

        felapsed = sf::Time::Zero;
    }
    std::cout << std::flush;
}
