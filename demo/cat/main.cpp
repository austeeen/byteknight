#include "common.hpp"
#include "typedef.hpp"
#include "game_object.hpp"

// g++ components.cpp game_object.cpp main.cpp -lsfml-graphics -lsfml-window -lsfml-system

class Background
{
public:
    Background(const std::string img_fp) {
        img_texture.loadFromFile(img_fp);
        sprite.setTexture(img_texture);
    }

    void render(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Texture img_texture;
    sf::Sprite sprite;
};

void setLetterbox(sf::View &view, const sf::Vector2u win_size)
{
    float windowRatio = win_size.x / (float) win_size.y;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;
    if (windowRatio < viewRatio) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }
    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Cat", (sf::Style::Resize + sf::Style::Close));
    sf::View view(sf::FloatRect(0, 0, 300, 225));

    Background background("res/town_center.png");
    GameObject cat(sf::Vector2f(150, 150), "res/cat.png", sf::IntRect(0, 0, 32, 32));
    cat.setUp();

    view.setCenter(cat.getPosition());
    setLetterbox(view, window.getSize());

    sf::Clock frame_clock;
    float dt = frame_clock.restart().asSeconds();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                setLetterbox(view, sf::Vector2u(event.size.width, event.size.height));
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Q: {
                        window.close();
                    }
                    case sf::Keyboard::Escape: {
                        window.close();
                    }
                    default: { break; }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            cat.move(DIR_UP);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            cat.move(DIR_DOWN);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            cat.move(DIR_LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            cat.move(DIR_RIGHT);
        }

        cat.update(dt);
        view.setCenter(cat.getPosition());
        window.clear();
        window.setView(view);
        background.render(window);
        cat.render(window);
        window.display();
        dt = frame_clock.restart().asSeconds();
    }
    return 1;
}
