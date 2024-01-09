#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "physics_coordinates.hpp"
#include "physics_collision.hpp"
#include <vector>
#include <queue>
#include <map>

namespace scene::physics {
// physics START BRACE

		//! Physics_Observer is an interface for objects that need to be notified of physics events
		class Physics_Observer {
			protected:
			
			public:
				Physics_Observer() = default;
				
				//! Notify the observer of movement
				virtual void notify(uint64 id, Position& p, Offset& o) = 0;

				//! Notify the observer of a collision
				virtual void notify(uint64 			id,		int				id2,
									double& 		speed,	double&		 	speed2,
									Collision_Data&	data, 	Collision_Data&	data2) = 0;
		};

		//! Physics_Data is a struct that contains all the data needed to create a Physics_Object
		struct Physics_Data {
			Position						pos;
			Offset							off;
			Dir_3d 							dir;
			Collision_Data 					collider;
			double							mass		= 0.0;
			double							speed		= 0.0;
		};

		struct Physics_Object {
			uint64 id;
			Position		pos;
			Offset			off;
			Dir_3d   		dir;
			Collision_Data	collider;
			double			mass;
			double			speed;
		};

		struct Nudge_Command {
			uint64 id;
			Position pos;
			Dir_3d dir;
		};

		struct Angle_Nudge_Command {
			Physics_Object* object;
			double angle;
		};

		struct Physics_Commands {
				uint64 nudge_ctr = 0;
				std::queue<Nudge_Command> nudge_commands;

				//uint64 angle_nudge_ctr = 0;	//TODO
				//std::queue<Angle_Nudge_Command> angle_nudge_commands;	//TODO

				void add(Nudge_Command C);
				//void add(Nudge_Command C);
		};

		class Physics_Object_List {
			private:
				std::vector<Physics_Observer*> m_observers;

				std::map<Position, std::vector<Physics_Object>> m_objects;
				uint64 m_obj_ctr = 0;

				Physics_Commands m_commands;

				//debug
				int rejected = 0;

				// Movement Functions

				//! Returns the highest Collide_Resistance at a given position
				Collide_Resistance resist_at_pos(Position& p);

				//! Modifies the offset of an object in a cardinal direction
				bool nudge_card	(double delta, Dir_3d_card d, std::vector<Physics_Object>::iterator obj_it);

				//! Calls nudge_card() for each cardinal direction in a Dir_3d
				void nudge (double delta, uint64 id, Position& pos, Dir_3d& d);

				//! Moves an object to a new position
				void move (uint64 id, Position& pos, Position& new_pos);
			public:
				Physics_Object_List();
				
				void update(double delta);

				uint64 add_object(Physics_Data data);
				//void remove_object(uint64 id, Position pos);

				~Physics_Object_List();
		};

// physics END BRACE
}

#endif