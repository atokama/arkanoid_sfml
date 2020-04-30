#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

const std::vector<sf::Color> palette{
        sf::Color(0x264653ff),
        sf::Color(0x2a9d8fff),
        sf::Color(0xe9c46aff),
        sf::Color(0xf4a261ff),
        sf::Color(0xe76f51ff)
};

class Padle {
public:
    float x, y, width, height;
    float speed;
    const sf::Color color = palette[1];

    void draw(sf::RenderWindow &app) {
        sf::RectangleShape r(sf::Vector2f(width, height));
        r.setFillColor(color);
        r.setPosition(x, y);
        app.draw(r);
    }

    void moveLeft(const sf::Time &elapsed) { x -= speed * elapsed.asSeconds(); }

    void moveRight(const sf::Time &elapsed) { x += speed * elapsed.asSeconds(); }

    Padle(float x, float y, float width, float height, float speed)
            : x(x), y(y), width(width), height(height), speed(speed) {}
};

int main() {
    sf::RenderWindow app(sf::VideoMode(640, 480), "Arkanoid", sf::Style::Default);

    float pw = 160;
    float ph = 16;
    Padle padle((app.getSize().x - pw) / 2, app.getSize().y - ph - 20, pw, ph, 1000);

    sf::Clock clock;

    while (app.isOpen()) {
        auto elapsed = clock.restart();

        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                app.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            padle.moveLeft(elapsed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            padle.moveRight(elapsed);
        }

        app.clear(palette[0]);

        padle.draw(app);

        app.display();
    }

    return 0;
}
