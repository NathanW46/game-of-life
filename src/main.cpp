#include "globals.h"
#include "grid.h"
#include "renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: filename" << endl;
    return 1;
  }

  string filename = argv[1];

  Grid grid(Globals::WIDTH/Globals::CELL_SIZE, Globals::HEIGHT/Globals::CELL_SIZE);
  grid.grid_from_file(filename);

  Renderer renderer(grid);


  while (renderer.window.isOpen()) {

    renderer.display();

  }

  return 0;
}
