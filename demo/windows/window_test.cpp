#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdint>

// g++ window.cpp -lsfml-graphics -lsfml-window -lsfml-system


void loop(sf::Window& window)
{
    while (window.isOpen()) {
        sf::Event event;
        if (window.waitEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
    }
}

namespace AspectRatio
{
    void matchWindowToView(sf::RenderWindow& window, sf::View& view)
    {
        // calculate window's ratio
        const float windowRatio = static_cast<float>(window.getSize().x) / window.getSize().y;

        // calculate a new view width so that the view's ratio would match the window's ratio
        const float newViewWidth = view.getSize().y * windowRatio;

        // apply the new width. You may wish to also adjust the view's centre; this depends on how you're using the view.
        view.setSize({ newViewWidth, view.getSize().y });

        // use the new, adjusted view
        window.setView(view);
    }
}

void setStyle(sf::Window& window)
{
    /*
    sf::Style::None	        No decoration at all (useful for splash screens, for example); this style
                            cannot be combined with others
    sf::Style::Titlebar	    The window has a titlebar
    sf::Style::Resize	    The window can be resized and has a maximize button
    sf::Style::Close	    The window has a close button
    sf::Style::Fullscreen	The window is shown in fullscreen mode; this style cannot be combined with
                            others, and requires a valid video mode
    sf::Style::Default	    The default style, which is a shortcut for Titlebar | Resize | Close
    */
}

void setIcon(sf::Window& window)
{
    const std::string icon_fp = "res/icon.png";
    const int icon_w = 0, icon_h = 0;
    const sf::Uint8* pixels;
    window.setIcon(icon_w, icon_h, pixels);
}

void setUpWindow(sf::Window& window)
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    window.setMouseCursorVisible(true);
    window.setMouseCursorGrabbed(true);
    window.setKeyRepeatEnabled(false);

    setIcon(window);

    // sf::Cursor::loadFromSystem;
    // sf::Cursor::loadFromPixels;
}

void createDefaultWindow(sf::Window& window)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    std::cout << "Desktop Mode: " << desktop.width << "x" << desktop.height << " - "
                << desktop.bitsPerPixel << " bpp" << std::endl;
    window.create(desktop, "default window");
}

void displayVideoModes()
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i) {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": " << mode.width << "x" << mode.height << " - "
                << mode.bitsPerPixel << " bpp" << std::endl;
    }
}

int main()
{
    // displayVideoModes();

    sf::Window window;
    createDefaultWindow(window);
    setUpWindow(window);
    loop(window);

    return 0;
}
