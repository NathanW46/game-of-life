#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"
#include "globals.h"

class Renderer {
private:
  sf::Font font;
  Grid &grid;
  int game_fps;
  float dt;
  sf::Clock clock;

public:
  bool pause;
  Renderer(Grid &grid);
  sf::RenderWindow window;
  void draw_cells();
  void draw_text();
  int calc_fps();
  void poll();
  void render();
};
