#include "grid.h"

Grid::Grid(int w, int h)
    : w(w), h(h), alive(0), cells(h, vector<bool>(w, false)) {}

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
      if (x >= 0 && x < w && y >= 0 && y < h) {
        set(x, y, true);
      }
    }
  }
  file.close();
}

void Grid::update() {
  vector<vector<bool>> newcells = cells;
  int n;
  alive = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
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

// setters
void Grid::set(int x, int y, bool state) {
  if (x >= 0 && x < w && y >= 0 && y < h)
    cells[y][x] = state;
}

void Grid::toggle(int x, int y) {
	cells[y][x] = !(cells[y][x]);
}

// getters
bool Grid::get(int x, int y) const {
  if (x < 0 || x >= w || y < 0 || y >= h)
    return false;
  return cells[y][x];
}
int Grid::get_h() const { return h; }
int Grid::get_w() const { return w; }
int Grid::get_alive() const { return alive; }

void Grid::print_state() const {
  for (int i = 0; i < cells.size(); i++) {
    for (int j = 0; j < cells[i].size(); j++) {
      cout << cells[i][j] << " ";
    }
    cout << endl;
  }
}

void Grid::print_neighbors() const {
  for (int i = 0; i < cells.size(); i++) {
    for (int j = 0; j < cells[i].size(); j++) {
      cout << get_neighbors(i, j) << " ";
    }
    cout << endl;
  }
}
