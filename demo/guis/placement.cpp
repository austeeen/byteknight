#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{

    const int WIN_W = 800;
    const int WIN_H = 600;

    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "SFML works!");

    sf::RenderTexture main_surface;
    if (!main_surface.create(WIN_W, WIN_H))
        return -1;

    sf::View minimap_view(window.getView());
    minimap_view.setViewport(sf::FloatRect(.75f, 0.f, .25f, .25f));

    sf::View instance_view = sf::View(sf::FloatRect(0, 0, 96, 96));

    sf::RectangleShape background(sf::Vector2f(100, 100));
    background.setFillColor(sf::Color::Blue);
    background.setPosition(sf::Vector2f(5, 5));

    sf::RectangleShape player(sf::Vector2f(16, 16));
    player.setFillColor(sf::Color::Green);

    sf::RectangleShape gui(sf::Vector2f(50, 100));
    gui.setFillColor(sf::Color::Magenta);
    gui.setPosition(sf::Vector2f(-100, -150)); // gui rect would be [-100, -150, 50, 100]

    // should be centered on gui rect with extra size to create a 5 pxl border?
    sf::View gui_view(sf::Vector2f(-75, -100), sf::Vector2f(60, 110));
    gui_view.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));

    bool show_gui = false;
    int px = 50, py = 50;
    player.setPosition(px, py);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    show_gui = !show_gui;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    py --;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    py ++;
                }
                if (event.key.code == sf::Keyboard::Left) {
                    px --;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    px ++;
                }
            }
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::Vector2f vsize = instance_view.getSize();
                vsize.x += event.size.width - vsize.x;
                vsize.y += event.size.height - vsize.y;
                instance_view.setSize(vsize);
            }

        }

        player.setPosition(px, py);
        instance_view.setCenter(px, py);

        main_surface.clear(sf::Color(100, 100, 100));
        main_surface.draw(background);
        main_surface.draw(player);
        main_surface.display();

        sf::Sprite msprite = sf::Sprite(main_surface.getTexture());

        window.clear();

        window.setView(instance_view);
        window.draw(msprite);

        window.setView(minimap_view);
        window.draw(msprite);

        if (show_gui) {
            window.setView(gui_view);
            window.draw(gui);
        }

        window.display();
    }

    return 0;
}
