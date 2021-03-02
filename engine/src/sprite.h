#pragma once
#include "SFML/Graphics.hpp"

namespace king::worksample {
struct sprite : public sf::Sprite {
	sprite() = default;
	sprite(const std::string& filename) {
		if (!m_texture.loadFromFile(filename)) {
			throw std::runtime_error("failed to load sprite: " + filename);
		} else {
			setTexture(m_texture);
		}
	}

private:
	sf::Texture m_texture;
};
}  // namespace king::worksample