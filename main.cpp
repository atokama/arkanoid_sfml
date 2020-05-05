#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

const std::vector<sf::Color> palette{
        sf::Color(0x000000ff),
        sf::Color(0xfff100ff),
        sf::Color(0xff8c00ff),
        sf::Color(0xe81123ff),
        sf::Color(0xec008cff),
        sf::Color(0x68217aff),
        sf::Color(0x00188fff),
        sf::Color(0x00bcf2ff),
        sf::Color(0x00b294ff),
        sf::Color(0x009e49ff),
        sf::Color(0xbad80aff),
        sf::Color(0xffffffff)};

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

class Ball {
public:
    float x, y, radius;
    float speed_x, speed_y;
    const sf::Color color = palette[11];

    void draw(sf::RenderWindow &app) {
        sf::RectangleShape r(sf::Vector2f(radius, radius));
        r.setFillColor(color);
        r.setPosition(x, y);
        app.draw(r);
    }

    Ball(float x, float y, float radius, float speed)
            : x(x), y(y), radius(radius), speed_x(speed), speed_y(speed) {}

    void move(const sf::Time &elapsed) {
        float x_next = speed_x * elapsed.asSeconds();
        float y_next = speed_y * elapsed.asSeconds();
    }

};

int main() {
    sf::RenderWindow app(sf::VideoMode(640, 480), "Arkanoid", sf::Style::Default);
    app.setFramerateLimit(120);

    float gw = 640;
    float gh = 480;
    sf::RectangleShape gamebox(sf::Vector2f(gw, gh));
    gamebox.setFillColor(palette[3]);
    gamebox.setPosition(
            (app.getSize().x - gw) / 2,
            (app.getSize().y - gh) / 2);

    float pw = 160;
    float ph = 16;
    Padle padle(
            gamebox.getPosition().x + (gamebox.getSize().x - pw) / 2,
            gamebox.getPosition().y + gamebox.getSize().y - ph - 20, pw, ph, 1000);

    float br = 12;
    float bx = padle.x + padle.width / 2 - br / 2;
    float by = padle.y - br;
    Ball ball(bx, by, br, 60);

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

        ball.move(elapsed);

        app.clear(palette[0]);
        app.draw(gamebox);

        padle.draw(app);
        ball.draw(app);

        app.display();
    }

    return 0;
}
