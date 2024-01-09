/*
 * world_drawing.cpp
 * 
 */
 
#include "alg.hpp"
#include "world_drawing.hpp"
#include "global_RNG.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

double pi = 3.14159;
double euler = 2.71828;

point::point(int a, int b) {
	int_x = a;
	int_y = b;
}

int point::x() {
	return int_x;
}

int point::y() {
	return int_y;
} 

bool point::operator== (point other)
// compares two points
{
	return ((this->x()==other.x()) && (this->y()==other.y()));
}

direction rand_weighted_direction(weight_map m)
// gets a random direction according to a weight map
{
	direction result;
	std::vector<directional_weight> dirs;
	
	dirs.push_back( directional_weight{dir_nw, m.nw} );
	dirs.push_back( directional_weight{dir_n , m.n } );
	dirs.push_back( directional_weight{dir_ne, m.ne} );
	dirs.push_back( directional_weight{dir_e , m.e } );
	dirs.push_back( directional_weight{dir_se, m.se} );
	dirs.push_back( directional_weight{dir_s , m.s } );
	dirs.push_back( directional_weight{dir_sw, m.sw} );
	dirs.push_back( directional_weight{dir_w , m.w } );
	
	dirs.push_back( directional_weight{dir_self, m.self} );
	
	double sum = 0;
	
	for (auto d : dirs) {
		sum += d.weight;
	}
	
	double choice = global_RNG::rand_double(0.0, sum);
	
	for (auto d : dirs) {
		if (choice < d.weight) {
			result = d.dir;
			break;
		}
		choice -= d.weight;
	}
		
	return result;
}

double to_radians(double degrees)
// converts an angle from degrees to radian
{
	return degrees*pi/180;
} 

point find_point_from (point origin, double angle, double distance) 
// finds the point at distance and angle from origin
{
	// angle is given in degrees
	// convert to radians
	double angle_rads = to_radians(angle);

	double xd = origin.x() + (distance * cos(angle_rads));
	double yd = origin.y() + (distance * sin(angle_rads));
	
	int x = alg::to_int(xd);
	int y = alg::to_int(yd);

	return point(x,y);
}


bool out_of_bounds(point p, point dims)
// checks if a point p is out of bounds of dimensions
{
	bool result = false;
	
	int width = dims.x()-1;
	int height = dims.y()-1;
	
	if ((p.x() < 0) or (p.x() > width))
		result = true;
		
	if ((p.y() < 0) or (p.y() > height))
		result = true;
			
	return result;
}
 
int distance(point p1, point p2)
// gets tile distance between two points (Chebyshev distance)
{
	int result;
	
	int difx = abs(p2.x()-p1.x());
	int dify = abs(p2.y()-p1.y());
	
	result = std::max(difx, dify);
	 
	return result;
}

std::vector<point> find_neighbors(point p, point dims)
// finds all points in neighborhood
{
	std::vector<point> result;
	
	point n  = point(p.x()  , p.y()-1);
	point ne = point(p.x()+1, p.y()-1);
	point e  = point(p.x()+1, p.y()  );
	point se = point(p.x()+1, p.y()+1);
	point s  = point(p.x()  , p.y()+1);
	point sw = point(p.x()-1, p.y()+1);
	point w  = point(p.x()-1, p.y()  );
	point nw = point(p.x()-1, p.y()-1);
	
	std::vector<point> points = { n, ne, e, se, s, sw, w, nw };
	
	for (auto p : points) {
		if (not out_of_bounds(p, dims))
			result.push_back(p);
	}
	
	return result;
}

void add_unique(std::vector<point> &vec1, std::vector<point> &vec2)
// adds only unique points from vec2 to vec1
{
	bool unique = true;
	
	for (point p2 : vec2) {
		
		for (point p1 : vec1) {
			
			if (p1==p2) {
				unique = false;
			}
			
		}
		
		if (unique) {
			vec1.push_back(p2);
		}
		
		unique = true;
	}
}

void remove_duplicates(std::vector<point> &vec)
// removes duplicates from a vector of points
{
	auto end = vec.end();
    for (auto it = vec.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }
 
    vec.erase(end, vec.end());
}

void reflect_x(std::vector<point> &points, point dims)
// reflects a set of points reflected on the x-axis
{
	std::vector<point> result;
	int axis = (dims.x()/2)-1;	
	
	int axis_dist;
	
	for (point P : points) {
		point ref = point(axis, P.y());
		
		axis_dist = distance(P, ref);
		
		if (ref.x() == P.x()) {
			result.push_back(P);
		}
		
		if (ref.x() < P.x()) {
			int new_x = axis - axis_dist;
			
			point new_point = point(new_x, P.y());
			result.push_back(new_point);
		}
		
		if (ref.x() > P.x()) {
			int new_x = axis + axis_dist;
			
			point new_point = point(new_x, P.y());
			result.push_back(new_point);
		}
	}
	
	points = result;
}

void reflect_y(std::vector<point> &points, point dims)
// reflects a set of points reflected on the y-axis
{
	std::vector<point> result;
	int axis = (dims.y()/2)-1;	
	
	int axis_dist;
	
	for (point P : points) {
		point ref = point(P.x(), axis);
		
		axis_dist = distance(P, ref);
		
		if (ref.y() == P.y()) {
			result.push_back(P);
		}
		
		if (ref.y() < P.y()) {
			int new_y = axis - axis_dist;
			
			point new_point = point(P.x(), new_y);
			result.push_back(new_point);
		}
		
		if (ref.y() > P.y()) {
			int new_y = axis + axis_dist;
			
			point new_point = point(P.x(), new_y);
			result.push_back(new_point);
		}
	}
	
	points = result;
}

std::vector<point> get_vert_line(point p1, point p2, point dims)
// returns a set of points on a vertical line from p1 to p2
{
	std::vector<point> point_list;
	
	point_list.reserve(distance(p1,p2)+1);
	
	int start;
	int end;
	
	if (p2.y() >= p1.y()) {
		start = p2.y();
		end = p1.y();
	} else {
		start = p1.y();
		end = p2.y();
	}
	
	for (int y = start; y >= end; y--) {
		point new_point = point(p1.x(), y);
		
		if (not out_of_bounds(new_point, dims)) {
			point_list.push_back(new_point);
		} else {
			std::cerr << "Warning! Tried to get point out of bounds (get_vert_line)" << std::endl;
		}
	}
	
	return point_list;
}

std::vector<point> get_line(point p1, point p2, point dims)
// gets a set of points for a line
// returns result of get_vert_line if line is vertical
{
	std::vector<point> point_list;
	
	point_list.reserve(distance(p1,p2)+1);
	
	int difx = abs(p2.x()-p1.x());
	int dify = abs(p2.y()-p1.y());
	
	if (difx == 0) {
		point_list = get_vert_line(p1, p2, dims);
	} else {
		double f_y1 = p1.y();
		double f_y2 = p2.y();
		double f_x1 = p1.x();
		double f_x2 = p2.x();
		
		double m = (f_y2-f_y1) / (f_x2-f_x1);
		double b = (f_y1) - (m*f_x1);
		
		int scan;
		int endsc;
		
		if (difx >= dify)
		// draw from right to left
		{
			if (p2.x() >= p1.x()) {
				scan = p2.x();
				endsc = p1.x();
			} else {
				scan = p1.x();
				endsc = p2.x();
			}
			
			for (int i = scan; i >= endsc; i--) {
				int x = round(i);
				int y = round(m*x+b);
								
				point new_point = point(x,y);
				
				if (not out_of_bounds(new_point, dims)) {
					point_list.push_back(new_point);
				} else {
					std::cerr<<"Warning! tried to get point out of bounds (get_line)"<<std::endl;
				}
			}
		} else
		// draw from down to up
		{
			if (p2.y() >= p1.y()) {
				scan = p2.y();
				endsc = p1.y();
			} else {
				scan = p1.y();
				endsc = p2.y();
			}
			
			for (int i = scan; i >= endsc; i--) {
				int y = round(i);
				int x = round((y-b)/m);
					
				point new_point = point(x, y);
					
				if (not out_of_bounds(new_point, dims)) {
					point_list.push_back(new_point);
				} else {
					std::cerr<<"Warning! tried to get point out of bounds (get_line)"<<std::endl;
				}
			}
		}
	}
	
	return point_list;
}

std::vector<point> get_area(point p1, point p2, point dims)
// returns a vector of points for a rectangular area
// p1 is top left point, p2 is bottom right point
{
	std::vector<point> area;
	
	int dist = distance(p1,p2)+1;
	
	area.reserve(dist*dist);
	
	int Start;
	int End;
	
	if (p2.y() > p1.y()) {
		Start = p2.y();
		End = p1.y();
	} else {
		Start = p1.y();
		End = p2.y();
	}
	
	std::vector<point> next_line;
	point next_p2 = point(0,0);
	point next_p1 = point(0,0);
	for (int y = Start; y >= End; y--) {
		next_p2 = point(p2.x(),y);
		next_p1 = point(p1.x(),y);
		
		next_line = get_line(next_p2, next_p1, dims);
		
		area.insert(area.end(), next_line.begin(), next_line.end());
	}
	
	return area;
}

std::vector<point> get_log_spiral (double a, double b, point origin, point dims, int step_size, double turns)
//  The polar coordinates of a logarithmic spiral can be written as:
//  r = ae pow (bO)
// 
//  r = distance from origin, O is the angle from the x-axis (in radians)
//  a and b are arbitrary constants
{
	// step_size tells how much to advance angle between line segments (resolution)
	// turns is the angle to draw to (in degrees)
	
	std::vector<point> result;
	
	std::vector<point> points;

	double angle = 0;
	while (angle <= (turns+step_size))
	{
		// find distance from the origin for that angle
		double p1 = (a * euler);
		double p2 = (b * to_radians(angle));
		
		double r = pow(p1,p2);

		point next_point = find_point_from(origin, angle, r);

		points.push_back(next_point);

		angle += step_size;
	}

	point last = origin;
	for (point p : points) {
		if (not out_of_bounds(p, dims)) {
			std::vector<point> next_line = get_line(last, p, dims);
				
			add_unique(result, next_line);
		}
		
		last = p;
	}
	
	return result;
}

std::vector<point> get_circle(point origin, int radius, point dims)
// returns a vector of points for a circle using Bresenham's Midpoint Circle algorithm
{
	std::vector<point> result;
	int d = 3 - (2 * radius);
	int y = radius;
	std::vector<point> next;
	
	for (int x=0; x<=radius; x++) {
		next.push_back(point(origin.x() + x, origin.y() + y));
        next.push_back(point(origin.x() + x, origin.y() - y));
        next.push_back(point(origin.x() - x, origin.y() + y));
        next.push_back(point(origin.x() - x, origin.y() - y));
        next.push_back(point(origin.x() + y, origin.y() + x));
        next.push_back(point(origin.x() + y, origin.y() - x));
        next.push_back(point(origin.x() - y, origin.y() + x));
        next.push_back(point(origin.x() - y, origin.y() - x));
        
        for (point p : next) {
			if (not out_of_bounds(p,dims)) {
				result.push_back(p);
			}
		}
	
		if (d<0) {
			d = d + (4 * x) + 6;
		} else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
	}
	
	remove_duplicates(result);
		
	return result;
}

std::vector<point> get_dist_circle(point origin, int radius, point dims)
// an alternate circle drawing algorithm using distance (produces a more boxy circle)
{
	std::vector<point> result;
	
	for (int ang=360; ang>0; ang--) {
		point next = find_point_from(origin, ang, radius);
		
		if (not out_of_bounds(next, dims))
			result.push_back(next);
	}
	
	remove_duplicates(result);
	
	return result;
}
