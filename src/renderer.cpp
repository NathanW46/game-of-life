#include "renderer.h"

Renderer::Renderer(Grid &grid)
    : grid(grid),
      window(sf::VideoMode(sf::Vector2u(Globals::WIDTH, Globals::HEIGHT)),
             "Conway's Game of Life") {
  window.setFramerateLimit(10);
}

void Renderer::poll() {
  // locally access window for lambda functions
  auto &win = this->window;
  // lambda functions for each event

  const auto onClose = [&win](const sf::Event::Closed &) { win.close(); };

  // const auto onKeyPressed = [this](const sf::Event::KeyPressed&
  // keyPressed)
  // {
  //     if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
  //         window.close();
  // };
  //
  window.handleEvents(onClose /*, onKeyPressed*/);

  // if (event.type == sf::Event::MouseButtonPressed) {
  //     if (event.mouseButton.button == sf::Mouse::Left) {
  //         int x = event.mouseButton.x / Globals::CELL_SIZE;
  //         int y = event.mouseButton.y / Globals::CELL_SIZE;
  //         grid.toggle(x, y);
  //     }
  // }

  // sf::RectangleShape txt_bckg(sf::Vector2f(200, 50));
  // txt_bckg.setPosition(sf::Vector2f(window.getSize().x - 220, 10));
  // txt_bckg.setFillColor(sf::Color(170, 170, 170, 40));
  //
  // sf::Font font;
  // if (!font.openFromFile("assets/HackNerdFontMono-Regular.ttf")) {
  //   cerr << "Font not found";
  //   return -1;
  // }
  //
  // sf::Text text(font, "Iteration: 1", 25);
  // text.setFillColor(sf::Color::White);
  // text.setPosition(sf::Vector2f(window.getSize().x - 190, 20));
  // int iteration = 1;
  //
  // int alive = grid.get_alive();
  // window.draw(txt_bckg);
  // window.draw(text);
  //
  // window.display();
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

void Renderer::display() {
  poll();

  grid.update();
  // iteration += 1;
  // alive = grid.get_alive();

  window.clear(sf::Color::Black);

  draw_cells();

  window.display();

  // text.setString("Iteration: " + to_string(iteration) +
  //                "\nAlive: " + to_string(alive));
  // text.setPosition(sf::Vector2f(window.getSize().x - 50, 20));
  //
  // // display text
  // window.draw(text);
  //
  // window.draw(txt_bckg);
  // window.display();
}
