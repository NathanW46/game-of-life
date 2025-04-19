#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 800;
const int CELL_SIZE = 10;
const int GRID_WIDTH = WIDTH / CELL_SIZE;
const int GRID_HEIGHT = HEIGHT / CELL_SIZE;
const int FPS = 5;

class Grid {
private:
  vector<vector<bool>> cells;
  int width, height;
  int alive = 0;

public:
  // constructor
  Grid(int w, int h) {
    width = w;
    height = h;
    cells.resize(height, vector<bool>(width, false));
  }

  sf::RenderWindow create();

  void grid_from_file(const string filename);
  int get_neighbors(int x, int y) const;
  void update();

  void print_state() const;
  void print_neighbors() const;

  // setters
  void set(int x, int y, bool state);

  // getters
  bool get(int x, int y) const;
  int get_height() const { return height; }
  int get_width() const { return width; }
  int get_alive() const { return alive; }
};

int Grid::get_neighbors(int x, int y) const {
  int n = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if ((0 == j) && (0 == i)) {
        continue;
      } else if (get(y + j, x + i)) {
        n += 1;
      }
    }
  }
  return n;
}

void Grid::print_neighbors() const {
  for (int i = 0; i < cells.size(); i++) {
    for (int j = 0; j < cells[i].size(); j++) {
      cout << get_neighbors(i, j) << " ";
    }
    cout << endl;
  }
}

bool Grid::get(int x, int y) const {
  if (x < 0 || x >= width || y < 0 || y >= height)
    return false;
  return cells[y][x];
}

void Grid::print_state() const {
  for (int i = 0; i < cells.size(); i++) {
    for (int j = 0; j < cells[i].size(); j++) {
      cout << cells[i][j] << " ";
    }
    cout << endl;
  }
}

void Grid::update() {
  vector<vector<bool>> newcells = cells;
  int n;
  alive = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      n = get_neighbors(i, j);

      // if alive
      if (cells[i][j]) {
        alive += 1;
        // overpopulation or //underpopulation
        if ((n > 3) || (n < 2)) {
          newcells[i][j] = false;
        }
        // lives
      }
      // if dead
      else {
        // reproducton
        if (n == 3)
          newcells[i][j] = true;
      }
    }
  }
  cells = newcells;
}

void Grid::grid_from_file(const string filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "File Error" << endl;
    return;
  }

  string line;
  while (getline(file, line)) {
    if (line.empty() || line[0] == '#')
      continue; // ignore empty line and comments

    istringstream sin(line);
    int x, y;

    if (sin >> x >> y) {
      alive += 1;
      if (x >= 0 && x < width && y >= 0 && y < height) {
        set(x, y, true);
      }
    }
  }
  file.close();
}

void Grid::set(int x, int y, bool state) {
  if (x >= 0 && x < width && y >= 0 && y < height)
    cells[y][x] = state;
}

sf::RenderWindow Grid::create() {
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(GRID_WIDTH * CELL_SIZE,
                                                     GRID_HEIGHT * CELL_SIZE)),
                          "Conway's Game of Life");
  window.setFramerateLimit(10);

  return window;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: filename" << endl;
    return 1;
  }

  string filename = argv[1];

  Grid grid(GRID_WIDTH, GRID_HEIGHT);

  grid.grid_from_file(filename);
  grid.print_neighbors();

  sf::RenderWindow window = grid.create();

  sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

  sf::RectangleShape txt_bckg(sf::Vector2f(200, 50));
  txt_bckg.setPosition(sf::Vector2f(window.getSize().x - 220, 10));
  txt_bckg.setFillColor(sf::Color(170, 170, 170, 40));

  sf::Font font;
  if (!font.openFromFile("assets/HackNerdFontMono-Regular.ttf")) {
    cerr << "Font not found";
    return -1;
  }

  sf::Text text(font, "Iteration: 1", 25);
  text.setFillColor(sf::Color::White);
  text.setPosition(sf::Vector2f(window.getSize().x - 190, 20));
  int iteration = 1;

  cellShape.setFillColor(sf::Color::Green);

  for (int y = 0; y < GRID_HEIGHT; ++y) {
    for (int x = 0; x < GRID_WIDTH; ++x) {
      if (grid.get(x, y)) {
        cellShape.setPosition({float(x * CELL_SIZE), float(y * CELL_SIZE)});
        window.draw(cellShape);
      }
    }
  }

  int alive = grid.get_alive();
  window.draw(txt_bckg);
  window.draw(text);

  window.display();

  string wait;
  cin >> wait;

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    grid.update();
    iteration += 1;
    alive = grid.get_alive();

    window.clear(sf::Color::Black);

    for (int y = 0; y < GRID_HEIGHT; ++y) {
      for (int x = 0; x < GRID_WIDTH; ++x) {
        if (grid.get(x, y)) {
          cellShape.setPosition({float(x * CELL_SIZE), float(y * CELL_SIZE)});
          window.draw(cellShape);
        }
      }
    }

    text.setString("Iteration: " + to_string(iteration) +
                   "\nAlive: " + to_string(alive));
    text.setPosition(sf::Vector2f(window.getSize().x - 50, 20));

    // display text
    window.draw(text);

    window.draw(txt_bckg);
    window.display();
  }

  return 0;
}
