#pragma once
#include "window.h"

namespace king::worksample {

struct game {
	virtual ~game() = default;
	virtual void update(float deltaTime) = 0;
	virtual void render(window& renderTarget) = 0;
	virtual bool isFinished() const = 0;
};

struct gameRunner {
	static int run(game& someGame, window& someWindow) {
		sf::Clock timer;
		while (!someGame.isFinished() && someWindow.isOpen()) {
			const auto deltaTime = timer.restart().asSeconds();
			someWindow.update();
			someGame.update(deltaTime);

			someWindow.clear();
			someGame.render(someWindow);
			someWindow.display();
		}

		return 0;
	}
};

}  // namespace king::worksample