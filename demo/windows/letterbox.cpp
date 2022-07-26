#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdint>

// g++ letterbox.cpp -lsfml-graphics -lsfml-window -lsfml-system

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

class Cat
{
public:
    int speed = 50;

    Cat(const sf::Vector2f start_pos, const std::string img_fp, const sf::IntRect texture_rect):
        start_pos(start_pos), cur_pos(start_pos)
    {
        img_texture.loadFromFile(img_fp);
        sprite.setTexture(img_texture);
        sprite.setTextureRect(texture_rect);
        sprite.setPosition(start_pos);
    }

    sf::Vector2f getPosition() const { return cur_pos; }

    void move(int dir) {
        switch(dir) {
            case DIR_UP: { cur_vel.y = -speed; break; }
            case DIR_DOWN: { cur_vel.y = speed; break; }
            case DIR_LEFT: { cur_vel.x = -speed; break; }
            case DIR_RIGHT: { cur_vel.x = speed; break; }
        }
    }

    void update(const float dt) {
        cur_pos.x += cur_vel.x * dt;
        cur_pos.y += cur_vel.y * dt;
        cur_vel.x = 0;
        cur_vel.y = 0;
        sprite.setPosition(cur_pos);
    }

    void lateUpdate() {
        // collision check
    }

    void render(sf::RenderWindow &window) {
        window.draw(sprite);
    }

private:
    sf::Texture img_texture;
    sf::Sprite sprite;
    const sf::Vector2f start_pos;
    sf::Vector2f cur_pos;
    sf::Vector2f cur_vel;
};

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

void disableLetterbox(sf::View &view)
{
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
}

void setLetterbox(sf::View &view, const sf::Vector2u win_size)
{
    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.
    float windowRatio = win_size.x / (float) win_size.y;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.
    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }
    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }
    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
}

void setFitted(sf::View &view, sf::FloatRect &view_rect, sf::Vector2f &aspect_ratio, sf::Vector2u win_size)
{
    view_rect.width = win_size.x * aspect_ratio.x;
    view_rect.height = win_size.y * aspect_ratio.y;
    sf::Vector2f view_center = view.getCenter();
    view = sf::View(view_rect);
    view.setCenter(view_center);
}

int main()
{
    sf::Vector2u win_size(640, 480);
    sf::FloatRect view_rect(0, 0, 300, 225);
    sf::Vector2f aspect_ratio(view_rect.width / win_size.x, view_rect.height / win_size.y);
    bool letterbox_enabled = false;

    Background background("town_center.png");
    Cat cat(sf::Vector2f(150, 150), "cat.png", sf::IntRect(0, 0, 32, 32));
    sf::Vector2f view_center = cat.getPosition();

    sf::RenderWindow window(sf::VideoMode(win_size.x, win_size.y), "Letterbox", (sf::Style::Resize + sf::Style::Close));
    sf::View view(view_center, sf::Vector2f(view_rect.width, view_rect.height));

    if (letterbox_enabled) {
        setLetterbox(view, win_size);
    } else {
        setFitted(view, view_rect, aspect_ratio, win_size);
    }

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
                win_size = sf::Vector2u(event.size.width, event.size.height);
                if (letterbox_enabled) {
                    setLetterbox(view, win_size);
                } else {
                    setFitted(view, view_rect, aspect_ratio, win_size);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Space: {
                        letterbox_enabled = !letterbox_enabled;
                        if (letterbox_enabled) {
                            win_size = window.getSize();
                            setLetterbox(view, win_size);
                        } else {
                            disableLetterbox(view);
                            setFitted(view, view_rect, aspect_ratio, win_size);
                        }
                        break;
                    }
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
