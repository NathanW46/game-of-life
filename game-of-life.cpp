#include<iostream>
#include<vector>
#include<ctime>
#include<SFML/Graphics.hpp>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 800;
const int CELL_SIZE = 10;
const int GRID_WIDTH = WIDTH / CELL_SIZE;
const int GRID_HEIGHT = HEIGHT / CELL_SIZE;
const int FPS = 2;


class Grid {
	private:
		vector<vector<bool>> cells;
		int height, width;

	public:
		int get_neighbors(int x, int y) const;
		
		//setters
		void set_pos(int x, int y);

		//getters
		bool get_status(int x, int y);
		int get_height() const {return height;}
		int get_width() const {return width;}

};
Grid initializeGrid(){
	


}
