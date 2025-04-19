#pragma once
#include "globals.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Grid {
private:
  vector<vector<bool>> cells;
  int w, h, alive;

public:
  // constructor
  Grid(int w, int h);

  void grid_from_file(const string filename);
  int get_neighbors(int x, int y) const;
  void update();

  // setters
  void set(int x, int y, bool state);

  // getters
  bool get(int x, int y) const;
  int get_h() const;
  int get_w() const;
  int get_alive() const;

  void print_state() const;
  void print_neighbors() const;
};
