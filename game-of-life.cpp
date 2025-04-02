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

  // setters
  void set(int x, int y, bool state);

  // getters
  bool get(int x, int y) const;
  int get_height() const { return height; }
  int get_width() const { return width; }
};

int Grid::get_neighbors(int x, int y) const {
  int n = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if ((0 == j) && (0 == i)) {
        continue;
      } else if (get(y + i, x + j)) {
        n += 1;
      }
    }
  }
  return n;
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
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      n = get_neighbors(j, i);

      // if alive
      if (cells[i][j]) {
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
  grid.print_state();

  sf::RenderWindow window = grid.create();

  sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  cellShape.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    grid.update();

    window.clear(sf::Color::Black);

    for (int y = 0; y < GRID_HEIGHT; ++y) {
      for (int x = 0; x < GRID_WIDTH; ++x) {
        if (grid.get(x, y)) {
          cellShape.setPosition({float(x * CELL_SIZE), float(y * CELL_SIZE)});
          window.draw(cellShape);
        }
      }
    }

    window.display();
  }

  return 0;
}
