#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"
#include "globals.h"

class Renderer {
private:
  sf::Font font;
  Grid &grid;

public:
  Renderer(Grid &grid);
  sf::RenderWindow window;
  void draw_cells();
  void poll();
  void display();
};
