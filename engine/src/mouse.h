#pragma once
#include "window.h"

namespace king::worksample {
struct mouse {
	mouse(window& inputWindow)
		: mWindow(inputWindow) {
	}

	bool isButtonDown(int button = sf::Mouse::Left) const {
		return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
	}

	sf::Vector2f getPosition() const {
		return mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
	}

	float getPositionX() const {
		return getPosition().x;
	}

	float getPositionY() const {
		return getPosition().y;
	}

private:
	const window& mWindow;
};
}  // namespace king::worksample