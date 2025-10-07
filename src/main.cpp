#include "shapes.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Ultimate Shapes", sf::Style::Close);

	us::RoundedRectangleShape roundedRect({300, 200}, 30, 2);
	roundedRect.setFillColor(sf::Color::White);
	roundedRect.setPosition({50, 100});

	us::RoundedRectangleShape roundedRect2({ 300, 200 }, 30);
	roundedRect2.setFillColor(sf::Color::White);
	roundedRect2.setPosition({ 400, 100 });

	while (window.isOpen()) {
		while (auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear(sf::Color(70, 70, 70));
		window.draw(roundedRect);
		window.draw(roundedRect2);
		window.display();
	}

	return 0;
}