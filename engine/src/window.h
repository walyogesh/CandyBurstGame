#pragma once
#include "SFML/Graphics.hpp"

namespace {
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {
	float windowRatio = windowWidth / (float)windowHeight;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1.f;
	float sizeY = 1.f;
	float posX = 0.f;
	float posY = 0.f;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1.f - sizeX) / 2.f;
	} else {
		sizeY = windowRatio / viewRatio;
		posY = (1.f - sizeY) / 2.f;
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

	return view;
}
}  // namespace

namespace king::worksample {
struct window : public sf::RenderWindow {
	window(uint16_t width, uint16_t height)
		: sf::RenderWindow(sf::VideoMode(width, height), "king worksample") {
	}
	void update() {
		sf::Event event;
		while (pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					close();
					break;
				case sf::Event::Resized:
					setView(getLetterboxView(getView(), event.size.width, event.size.height));
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) {
						close();
					}
					break;

				default:
					break;
			}
		}
	}
};
}  // namespace king::worksample