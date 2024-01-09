
#include "tile_logic.h"
#include <iostream>
#include <cstdlib>

const int OBJECT_T_WEAPON = 0;
const int OBJECT_T_TOOL = 1;
const int OBJECT_T_FOOD = 2;
const int OBJECT_T_NATURE = 3;

class object {
	private:
		point coords = point(0,0);
		int type;
		int index;
	public:
		object(int x, int y, int object_type, int ind) {
			type = object_type;
			index = ind; 
			coords = point(x, y);
		}
		point get_coords() {
			return coords;
		}
		int get_type() {
			return type;
		}
		int get_index() {
			return index;
		}
};

const int ENTITY_T_STONE = 0;
const int ENTITY_T_PLANT = 1;
const int ENTITY_T_ANIMAL = 2;

class entity {
	private:
		int entity_type;
		int index;
		int health;
		bool living;
	public:
		entity(type, ind) {
			int set_health = 100;
			if (type > ENTITY_T_STONE) {
				living = true;
			} else {
				living = false;
				health += 100;
			}
			
			entity_type = type;
			index = ind;
		}
		void damage(int amount, int type) {
			health -= amount*type;
		}
		void process(int seed) {
			if (health <= 0) {
				living = false;
			}
			
			if (living) {
				health += seed;
			
				if (entity_type > ENTITY_T_PLANT) {
					move(seed);
				}
			}
		}
		void move(int seed) {
			//move around, or something
		}
		
	
};

class area_map {
	private:
		int AREA_WIDTH;
		int AREA_HEIGHT;
		int terrain_type;
		
		std::vector<object> object_list;
		
		//dyn_map lower_y;
		dyn_map middle_y;
		dyn_map middle_entity;
		dyn_map middle_oxygen;
		//dyn_map upper_y;
		//-1 = lower, 0 = mid, 1 = upper
		int current_z;
	public:
		area_map(int width, int height, int terrain) {
			populate_tiles(width, height, middle_y);
			terrain_type = terrain;
			current_z = 0;
		}
		void load_map() {
			//load an already generated area from save
		}
		void generate_map() {
			//generate a map using the given terrain parameters
			
		}
		void spawn_object(int x, int y, int item_type, int item_index) {
			if (not is_solid(x, y)) {
				object new_object = object(x, y, item_type, item_index);
				object_list.push_back(new_object);
			} else {
				std::cout<<"Could not spawn object inside solid surface"<<std::endl;
			}
		}
		bool is_solid (int x, int y) {
			bool solid = false;
			point loc = point(x, y);
			if (current_z == 0) {
				if (not out_of_bounds(loc, middle_y)) {
					if (middle_y[y][x] >= 20) {
						solid = true;
					}
				}
			}
			
			return solid;
		}
		void remove_objects_at(int x, int y) {
			//remove all objects within these coordinates
		}
		
	
};

int main(int argc, char **argv) {
	
	return 0;
}
