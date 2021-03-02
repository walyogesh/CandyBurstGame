#pragma once
#include "SFML/Graphics.hpp"

namespace king::worksample {
struct text : public sf::Text {
	text() = default;
	text(const std::string& string, const std::string& font) {
		if (!mFont.loadFromFile(font)) {
			throw std::runtime_error("failed to load font: " + font);
		} else {
			setFont(mFont);
			setString(string);
		}
	}

private:
	sf::Font mFont;
};
}  // namespace king::worksample