#ifndef MAPGEN_H
#define MAPGEN_H

#include <vector>

using dyn_map = std::vector<std::vector<int>>;
using dyn_row = std::vector<int>;

class point {
	private:
		int int_x, int_y;
	public:
		point(int a, int b);
		int x();
		int y();
};

int populate_tiles(int width, int height, dyn_map &map);

int get_max_x(dyn_map &map);

int get_max_y(dyn_map &map);

bool out_of_bounds(point &p, dyn_map &map);

int push_points(int value, std::vector<point> &list, dyn_map &map);

int distance(point &p1, point &p2);

std::vector<point> get_vert_line(point &p1, point &p2, dyn_map &map);

std::vector<point> get_line(point &p1, point &p2, dyn_map &map);

int draw_line(int value, point &start, point &end, dyn_map &map);

int print_map(dyn_map &map);

#endif
