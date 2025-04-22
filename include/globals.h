#pragma once
#include <SFML/Graphics.hpp>

namespace Globals {
extern unsigned int WIDTH;
extern unsigned int HEIGHT;
extern int CELL_SIZE;
extern int FPS;
extern bool SHOW_GRID_LINES;
extern sf::Font font;

void load_defaults();
} // namespace Globals
