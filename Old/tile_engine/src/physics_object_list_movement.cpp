/*
 * physics.cpp
 *
 * Copyright 2023 Kayla Gray
 *
 */


#include "physics.hpp"
#include <cmath>
#include <algorithm>	//std::find_if
#include <functional>	//std::equal_to
#include <iostream>

using namespace scene::physics;

namespace scene::physics {
// physics START BRACE

 	static double delta_speed(double& delta, double& speed)
	//returns the speed adjusted for delta time
	{
		double result = speed * delta;

		if (result > TILE_SIZE)
			result = TILE_SIZE;	//cap the maximum change per frame to 1 Position

		return result;
	}

	static bool id_equals(Physics_Object& obj, uint64 id)
	// returns true if the id of the Physics_Object matches the id passed
	{
		return obj.id == id;
	}

 	void Physics_Object_List::move(uint64 id, Position& pos, Position& new_pos)
	// moves to Physics_Object to a new Position in the map
	{
		// find the object
		auto obj_it = std::find_if(m_objects[pos].begin(), m_objects[pos].end(), std::bind(id_equals, std::placeholders::_1, id));
		
		m_objects[new_pos].push_back(*obj_it);
		m_objects[pos].erase(obj_it);

		auto new_it = std::find_if(m_objects[new_pos].begin(), m_objects[new_pos].end(), std::bind(id_equals, std::placeholders::_1, id));
		
		auto new_obj = *new_it; 

		if (new_obj.speed > 0.0) {
			m_commands.add({id, new_pos, new_obj.dir});
		}
	}

	bool Physics_Object_List::nudge_card(double delta,
										 Dir_3d_card d,
										 std::vector<Physics_Object>::iterator obj_it)
	// modifies the offset of an object in a cardinal direction
	// returns true if the object moves to a new Position
	{
 		//reference to the object
		Physics_Object& obj = *obj_it;

		// used to calculate rollover
		double excess;

		// the predicted next position if offset rolls over the maximum
		Position next;
		
		// the speed adjusted for delta time
		double old_speed = delta_speed(delta, obj.speed);

		switch(d) {
			case dirc_n:
				if ((obj.off.y - old_speed) >= 0.0) {
					obj.off.y -= old_speed;
				} else {
					//rollover
					//check for collision at the next Position
					next = obj.pos;
					next.y -= 1;

					Collide_Resistance r = resist_at_pos(next);
					apply_resistance(delta, r, obj.speed);				

					if ((r != resist_solid) && pos_in_bounds(next)) {
						excess = obj.off.y - old_speed;	//expected to be negative
						obj.off.y = TILE_SIZE + excess;

						obj.pos = next;	//change to next Position
						move(obj.id, obj.pos, next);
						return true;
					} else {
						obj.off.y = 0.0;
					}
				}
				break;
			case dirc_e:
				if ((obj.off.x + old_speed) <= TILE_SIZE) {
					obj.off.x += old_speed;
				} else {
					//rollover
					//check for collision at the next Position
					next = obj.pos;
					next.x += 1;

					Collide_Resistance r = resist_at_pos(next);
					apply_resistance(delta, r, obj.speed);

					if ((r != resist_solid) && pos_in_bounds(next)) {
						excess = (obj.off.x + old_speed) - TILE_SIZE; //expected to be positive
						obj.off.x = 0.0 + excess;
						
						move(obj.id, obj.pos, next);
						return true;
					} else {
						obj.off.x = TILE_SIZE;
					}
				}
				break;
			case dirc_s:
				if ((obj.off.y + old_speed) <= TILE_SIZE) {
					obj.off.y += old_speed;
				} else {
					//rollover
					//check for collision at next position
					next = obj.pos;
					next.y += 1;
					
					Collide_Resistance r = resist_at_pos(next);
					apply_resistance(delta, r, obj.speed);			

					if ((r != resist_solid) && pos_in_bounds(next)) {
						excess = (obj.off.y + old_speed) - TILE_SIZE; //expected to be positive
						
						obj.off.y = 0.0 + excess;
						move(obj.id, obj.pos, next);
						return true;
					} else {
						obj.off.y = TILE_SIZE;
					}
				}
				break;
			case dirc_w:
				if ((obj.off.x - old_speed) >= 0.0) {
					obj.off.x -= old_speed;
				} else {
					//rollover
					//check for collision at next Position
					next = obj.pos;
					next.x -= 1;

					Collide_Resistance r = resist_at_pos(next);
					apply_resistance(delta, r, obj.speed);

					if ((r != resist_solid) && pos_in_bounds(next)) {
						excess = obj.off.x - old_speed;	//expected to be negative
						
						obj.off.x = TILE_SIZE + excess;
						move(obj.id, obj.pos, next);
						return true;
					} else {
						obj.off.x = 0.0;
					}
				}
				break;
			case dirc_u:
				if ((obj.off.z + old_speed) <= TILE_SIZE) {
					obj.off.z += old_speed;
				} else {
					//rollover
					//check for collision at next Position
					next = obj.pos;
					next.z += 1;

					Collide_Resistance r = resist_at_pos(next);
					apply_resistance(delta, r, obj.speed);

					if ((r != resist_solid) && pos_in_bounds(next)) {
						excess = (obj.off.z + old_speed) - TILE_SIZE; //expected to be positive

						obj.off.z = 0.0 + excess;
						move(obj.id, obj.pos, next);
						return true;
					} else {
						obj.off.z = TILE_SIZE;
					}
				}
				break;
			case dirc_d:
				if ((obj.off.z - old_speed) >= 0.0) {
					obj.off.z -= old_speed;
				} else {
					//rollover
					//check for collision at next Position
					next = obj.pos;
					next.z -= 1;

					Collide_Resistance r = resist_at_pos(next);
					apply_resistance(delta, r, obj.speed);

					if ((r != resist_solid) && pos_in_bounds(next)) {
						excess = obj.off.z - old_speed;	//expected to be negative

						obj.off.z = TILE_SIZE;
						move(obj.id, obj.pos, next);
						return true;
					} else {
						obj.off.z = 0.0;
					}
				}
				break;
		}

		return false;
	}

	void Physics_Object_List::nudge(double delta, uint64 id, Position& pos, Dir_3d& d)
	// calls the nudge_card() function for each cardinal direction in a Dir_3d
	{	
		//find the iterator for the object
		auto obj_it
		= std::find_if(m_objects[pos].begin(), m_objects[pos].end(), std::bind(id_equals, std::placeholders::_1, id));

		bool moved = false;

	 	switch (d) {
			case dir_n:
				moved = (nudge_card(delta, dirc_n, obj_it)) ? true : moved;
				break;
			case dir_ne:
				moved = (nudge_card(delta, dirc_n, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_e, obj_it)) ? true : moved;
				break;
			case dir_e:
				moved = (nudge_card(delta, dirc_e, obj_it)) ? true : moved;
				break;
			case dir_se:
				moved = (nudge_card(delta, dirc_s, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_e, obj_it)) ? true : moved;
				break;
			case dir_s:
				moved = (nudge_card(delta, dirc_s, obj_it)) ? true : moved;
				break;
			case dir_sw:
				moved = (nudge_card(delta, dirc_s, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_w, obj_it)) ? true : moved;
				break;
			case dir_w:
				moved = (nudge_card(delta, dirc_w, obj_it)) ? true : moved;
				break;
			case dir_nw:
				moved = (nudge_card(delta, dirc_n, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_w, obj_it)) ? true : moved;
				break;
			case dir_u:
				moved = (nudge_card(delta, dirc_u, obj_it)) ? true : moved;
				break;
			case dir_un:
				moved = (nudge_card(delta, dirc_u, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_n, obj_it)) ? true : moved;
				break;
			case dir_une:
				moved = (nudge_card(delta, dirc_u, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_n, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_e, obj_it)) ? true : moved;
				break;
			case dir_ue:
				moved = (nudge_card(delta, dirc_u, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_e, obj_it)) ? true : moved;
				break;
			case dir_use:
				moved = (nudge_card(delta, dirc_u, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_s, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_e, obj_it)) ? true : moved;
				break;
			case dir_us:
				moved = (nudge_card(delta, dirc_u, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_s, obj_it)) ? true : moved;
				break;
			case dir_usw:
				moved = (nudge_card(delta, dirc_u, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_s, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_w, obj_it)) ? true : moved;
				break;
			case dir_uw:
				moved = (nudge_card(delta, dirc_u, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_w, obj_it)) ? true : moved;
				break;
			case dir_unw:
				moved = (nudge_card(delta, dirc_u, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_n, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_w, obj_it)) ? true : moved;
				break;
			case dir_d:
				moved = (nudge_card(delta, dirc_d, obj_it)) ? true : moved;
				break;
			case dir_dn:
				moved = (nudge_card(delta, dirc_d, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_n, obj_it)) ? true : moved;
				break;
			case dir_dne:
				moved = (nudge_card(delta, dirc_d, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_n, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_e, obj_it)) ? true : moved;
				break;
			case dir_de:
				moved = (nudge_card(delta, dirc_d, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_e, obj_it)) ? true : moved;
				break;
			case dir_dse:
				moved = (nudge_card(delta, dirc_d, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_s, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_e, obj_it)) ? true : moved;
				break;
			case dir_ds:
				moved = (nudge_card(delta, dirc_d, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_s, obj_it)) ? true : moved;
				break;
			case dir_dsw:
				moved = (nudge_card(delta, dirc_d, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_s, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_w, obj_it)) ? true : moved;
				break;
			case dir_dw:
				moved = (nudge_card(delta, dirc_d, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_w, obj_it)) ? true : moved;
				break;
			case dir_dnw:
				moved = (nudge_card(delta, dirc_d, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_n, obj_it)) ? true : moved;
				moved = (nudge_card(delta, dirc_w, obj_it)) ? true : moved;
				break;
		}

		// moving will invalidate the iterator, so do not create the move command here
		// the move command is created in the move function
		auto new_obj = *obj_it;

		if ((new_obj.speed > 0.0) && (moved == false)) {
			m_commands.add({new_obj.id, new_obj.pos, d});
		}
	}
 
// physics END BRACE
}
