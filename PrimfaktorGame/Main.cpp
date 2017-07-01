#include <iostream>
#include "Game.h"
#include "GameDifficulty.h"

int main() {
	Game g;
	g.init();
	g.run();
	std::cin.get();
	return 0;
}

