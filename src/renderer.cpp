#include "renderer.h"

Renderer::Renderer(Grid &grid)
    : grid(grid),
      window(sf::VideoMode(sf::Vector2u(Globals::WIDTH, Globals::HEIGHT)),
             "Conway's Game of Life") {
  window.setFramerateLimit(Globals::FPS);
}

void Renderer::poll() {
  // locally access window for lambda functions
  auto &win = this->window;
  // lambda functions for each event

  const auto onClose = [&win](const sf::Event::Closed &) { win.close(); };

  const auto onKeyPressed = [this](const sf::Event::KeyPressed &keyPressed) {
    if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
      window.close();
    if (keyPressed.scancode == sf::Keyboard::Scancode::P)
      pause = !pause;
    if (keyPressed.scancode == sf::Keyboard::Scancode::Space)
      if (pause)
        grid.update();

    if (keyPressed.scancode == sf::Keyboard::Scancode::Right) {
      Globals::FPS += 1;
      window.setFramerateLimit(Globals::FPS);
    }

    if (keyPressed.scancode == sf::Keyboard::Scancode::Left) {
      Globals::FPS -= 1;
      window.setFramerateLimit(Globals::FPS);
    }
  };

  window.handleEvents(onClose, onKeyPressed);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    int x = sf::Mouse::getPosition(window).x / Globals::CELL_SIZE;
    int y = sf::Mouse::getPosition(window).y / Globals::CELL_SIZE;
    grid.set(x, y, true);
  }

  else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
    int x = sf::Mouse::getPosition(window).x / Globals::CELL_SIZE;
    int y = sf::Mouse::getPosition(window).y / Globals::CELL_SIZE;
    grid.set(x, y, false);
  }
}

void Renderer::draw_text() {
  sf::RectangleShape txt_bckg(sf::Vector2f(200, 100));
  txt_bckg.setPosition(sf::Vector2f(window.getSize().x - 220, 10));
  txt_bckg.setFillColor(sf::Color(170, 170, 170, 40));

  sf::Text text(Globals::font, "Iteration: 1", 15);
  text.setFillColor(sf::Color::White);
  text.setPosition(sf::Vector2f(window.getSize().x - 190, 20));
  text.setString("Iteration: " + to_string(grid.iteration) + "\nAlive: " +
                 to_string(grid.alive) + "\nFPS: " + to_string(game_fps));
  text.setPosition(sf::Vector2f(window.getSize().x - 175, 20));

  window.draw(txt_bckg);
  window.draw(text);
}

void Renderer::draw_cells() {

  sf::RectangleShape cellShape(
      sf::Vector2f(Globals::CELL_SIZE, Globals::CELL_SIZE));
  cellShape.setFillColor(sf::Color::Green);

  for (int y = 0; y < grid.get_h(); ++y) {
    for (int x = 0; x < grid.get_w(); ++x) {
      if (grid.get(x, y)) {
        cellShape.setPosition(sf::Vector2f(float(x * Globals::CELL_SIZE),
                                           float(y * Globals::CELL_SIZE)));
        window.draw(cellShape);
      }
    }
  }
}

int Renderer::calc_fps() {
  game_fps = 1 / dt;
  return game_fps;
}

void Renderer::render() {
  // grid.print_state();
  dt = 0.0;
  poll();

  if (!pause)
    grid.update();

  window.clear(sf::Color::Black);

  draw_cells();
  draw_text();

  window.display();
  dt = clock.restart().asSeconds();
  calc_fps();
}
