
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

sf::RenderWindow Window;

int main() {
    /////////////////////////////////////////////////// WINDOW INIT ////////////////////////////////////////////
    Window.create(sf::VideoMode(800, 600, 32), "5!");
    Window.setActive(true);
    Window.setKeyRepeatEnabled(true);
    Window.setFramerateLimit(60);
    Window.setPosition(sf::Vector2i(300, 30));

    /////////////////////////////////////////////////// CREATE OBJECTS ////////////////////////////////////////////
    sf::CircleShape c(10);
    c.setFillColor(sf::Color(100, 100, 100));
    c.setOrigin(0, 0);
    c.setPosition(200, 300);

    std::vector<std::shared_ptr<sf::CircleShape>> Enemy;

    sf::Event Event;
    /////////////////////////////////////////////////// MAIN LOOP ////////////////////////////////////////////
    while (Window.isOpen()) {
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Window.close();
            };
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            c.move(sf::Vector2f(0, -10));
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            c.move(sf::Vector2f(0, 10));
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            static int i = 0;
            static int counter = 0;
            std::shared_ptr<sf::CircleShape> en = std::make_shared<sf::CircleShape>(10);
            std::shared_ptr<sf::CircleShape> en2 = std::make_shared<sf::CircleShape>(30);
            en->setFillColor(sf::Color(255, 100, 100));
            en->setOrigin(0, 0);
            en->setPosition(sf::Vector2f(600 - (i / 2), 200 + i));
            en2->setOrigin(0, 0);
            en2->setPosition(sf::Vector2f(600 - (i / 2), 220 + i));
            switch(counter)
            {
            case 0: {en2->setFillColor(sf::Color(148, 0, 211)); break;};
            case 1: {en2->setFillColor(sf::Color(0, 0, 255)); break;};
            case 2: {en2->setFillColor(sf::Color(0, 255, 0)); break;};
            case 3: {en2->setFillColor(sf::Color(255, 255, 0)); break;};
            case 4: {en2->setFillColor(sf::Color(255, 127, 0)); break;};
            case 5: {en2->setFillColor(sf::Color(255, 0 , 0)); break;};
            default: {en2->setFillColor(sf::Color(0xFFFFFF)); }
            }
            i += 50;
            counter++;
            Enemy.push_back(en2);
            Enemy.push_back(en);

            if (counter >= 6) {
                counter = 0;
                i = 0;
            }
        };

        Window.clear();

        if (!Enemy.empty()) {
            std::for_each(Enemy.begin(), Enemy.end(), [](auto& en) mutable {
                en->setPosition(sf::Vector2f(en->getPosition().x - 1, en->getPosition().y));

                Window.draw(*en);
            });

            Enemy.erase(std::remove_if(Enemy.begin(),
                                       Enemy.end(),
                                       [](auto& en) { return en->getPosition().x < 20; }),
                        Enemy.end());
        };

        Window.draw(c);

        Window.display();
    }
}
