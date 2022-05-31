#include "input_types.hpp"

bool joy::connected_joys(std::vector<int> &cons)
{
    sf::Joystick::update();
    std::cout << "finding connected joysticks" << std::endl;
    for (int i = 0; i < joy::SFML_MAX_JOYS; i++) {
        if (sf::Joystick::isConnected(i)) {
            std::cout << i << " is connected" << std::endl;
            cons.push_back(i);
        }
    }
    return cons.size();
}
