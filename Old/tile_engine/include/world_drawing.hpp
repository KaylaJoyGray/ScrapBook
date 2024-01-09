#ifndef WORLD_DRAWING_H
#define WORLD_DRAWING_H

#include <vector>

class point {
	private:
		int int_x, int_y;
	public:
		point () = default;
		point (int a, int b);
	
		int x();
		int y();
		
		bool operator== (point other);
};

enum direction {
	dir_nw, dir_n, dir_ne, dir_e, dir_se, dir_s, dir_sw, dir_w, dir_self
};

struct directional_weight {
	direction dir;
	double weight;
};

struct weight_map {
	double nw, n, ne, e, se, s, sw, w, self;
};

// gets a random direction according to a weight map
direction rand_weighted_direction(weight_map m);

// converts and angle from degrees to radian
double to_radians(double degrees);

// finds the point at distance and angle from origin
point find_point_from (point origin, double angle, double distance);

// checks if points is out of bound of dims
bool out_of_bounds(point p, point dims);

// gets tile distance between two points (Chebyshev distance)
int distance(point p1, point p2);

// finds all points in neighborhood
std::vector<point> find_neighbors(point p, point dims);

// adds only unique points from vec2 to vec1
void add_unique(std::vector<point> &vec1, std::vector<point> &vec2);

// removes duplicates from a vector of points
void remove_duplicates(std::vector<point> &vec);

//****************************************************
// Transformations for sets of points
//

// reflects a set of points reflected on the x-axis
void reflect_x(std::vector<point> &points, point dims);

// reflects a set of points reflected on the y-axis
void reflect_y(std::vector<point> &points, point dims);

//
// Transformations for sets of points
//****************************************************

// returns a set of points on a vertical line between p1 and p2
std::vector<point> get_vert_line(point p1, point p2, point dims);

// gets a set of points for a line between p1 and p2
std::vector<point> get_line(point p1, point p2, point dims);

// returns a vector of points for a rectangular area
// p1 is top left point, p2 is bottom right point
std::vector<point> get_area(point p1, point p2, point dims);

// returns a vector of points for a logarithmic spiral
std::vector<point> get_log_spiral(double a, double b, point origin, point dims, int step_size, double turns=360);

// returns a vector of points for a circle using Bresenham's Midpoint Circle algorithm
std::vector<point> get_circle(point origin, int radius, point dims);

// an alternate circle drawing algorithm using distance (produces a more boxy circle)
std::vector<point> get_dist_circle(point origin, int radius, point dims);

#endif
