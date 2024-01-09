/*
 * mapgen.cpp
 * 
 * Contains all of the functions and classes
 * for generating and manipulating tile maps
 * 
 */

#include "mapgen.h"

#include <iostream>
#include <cmath>

using dyn_map = std::vector<std::vector<int>>;
using dyn_row = std::vector<int>;

point::point (int a, int b) {
	int_x = a;
	int_y = b;
}

int point::x() {
	return int_x;
}

int point::y(){
	return int_y;
}

int populate_tiles(int width, int height, dyn_map &map)
// populates tiles in tile map to initial value of zero
{
	dyn_row row;
	
	for (int w = 0; w < width; w++) {
		row.push_back(0);
	}
	
	for (int h = 0; h < height; h++) {
		map.push_back(row);
	}
	
	return 0;
}

int get_max_x(dyn_map &map)
// gets max x that can fit on map
{
		return map[0].size()-1;
}

int get_max_y(dyn_map &map)
// gets max y that can fit on map
{
		return map.size()-1; 
}

bool out_of_bounds(point &p, dyn_map &map)
// returns TRUE if point is out of map bounds
{
	bool out = false;
	
	int xmax = get_max_x(map);
	int ymax = get_max_y(map);
	
	if ( (p.x()>xmax) || (p.x()<0) ) {
		out = true;
	} 
	
	if ( (p.y()>ymax) || (p.y()<0) ) {
		out = true;
	}
	
	return out;
}

int push_points(int value, std::vector<point> &list, dyn_map &map)
// pushes a set of points to the tile map
{
	int bound_flag = 0;
	
	for (int i=0; i<list.size(); i++) {
		int x = list[i].x();
		int y = list[i].y();
		
		if (not out_of_bounds(list[i], map)) {
			map[y][x] = value;
		} else {
			std::cout << "Tried to push points out of bounds! (push_points)" << std::endl;
			bound_flag = -1;
		}
	}
	
	return bound_flag;
}

int distance(point &p1, point &p2)
// gets tile distance between two points (Chebyshev distance)
{
	int result;
	
	int difx = abs(p2.x()-p1.x());
	int dify = abs(p2.y()-p1.y());
	
	result = std::max(difx, dify);
	 
	return result;
}

std::vector<point> get_vert_line(point &p1, point &p2, dyn_map &map)
// returns a set of points on a vertical line from y1-y2 at x
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
		
		if (not out_of_bounds(new_point, map)) {
			point_list.push_back(new_point);
		} else {
			std::cout << "Warning! Tried to get point out of bounds (get_vert_line)" << std::endl;
		}
	}
	
	return point_list;
}

std::vector<point> get_line(point &p1, point &p2, dyn_map &map)
// gets a set of points for a line
// returns result of get_vert_line if line is vertical
{
	std::vector<point> point_list;
	
	point_list.reserve(distance(p1,p2)+1);
	
	int difx = abs(p2.x()-p1.x());
	int dify = abs(p2.y()-p1.y());
	
	if (difx == 0) {
		point_list = get_vert_line(p1, p2, map);
	} else {
		float f_y1 = p1.y();
		float f_y2 = p2.y();
		float f_x1 = p1.x();
		float f_x2 = p2.x();
		
		float m = (f_y2-f_y1) / (f_x2-f_x1);
		float b = (f_y1) - (m*f_x1);
		
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
				
				if (not out_of_bounds(new_point, map)) {
					point_list.push_back(new_point);
				} else {
					std::cout<<"Warning! tried to get point out of bounds (get_line)"<<std::endl;
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
					
				if (not out_of_bounds(new_point, map)) {
					point_list.push_back(new_point);
				} else {
					std::cout<<"Warning! tried to get point out of bounds (get_line)"<<std::endl;
				}
			}
		}
	}
	
	return point_list;
}

int draw_line(int value, point &start, point &end, dyn_map &map)
// pushes a line to a tile map with value
{
	std::vector<point> point_list;
	
	point_list.reserve(distance(start,end)+1);
	
	point_list = get_line(start, end, map);
	
	push_points(value, point_list, map);

	return 0;
}

int print_map(dyn_map &map)
// prints a tile map to the console
// mostly for debugging
{
	for (int y = 0; y < map.size(); y++)
	{
		
		dyn_row row = map[y];
		
		for (std::size_t x = 0; x < row.size(); x++)
		{
			std::cout << row[x] << " ";		
		}
		
		std::cout << std::endl;
	}	

	return 0;
}
