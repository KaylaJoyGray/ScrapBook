
#include "physics.hpp"
#include <iostream>

namespace scene::physics {
// physics START BRACE

	Physics_Object_List::Physics_Object_List()
	// constructor
	{
		auto it = m_objects.begin();
		for (uint8 z = 0; z <= CHUNK_SIZE; ++z) {
			for (uint8 y = 0; y <= CHUNK_SIZE; ++y) {
				for (uint8 x = 0; x <= CHUNK_SIZE; ++x) {
					m_objects.emplace_hint(it, std::pair<Position, std::vector<Physics_Object>>({x, y, z}, { }));
					it = m_objects.end();
				}
			}
		}

		std::cout << "Map size is " << m_objects.size() << std::endl;
	}

	Physics_Object_List::~Physics_Object_List()

	{
		auto percent = ((double)rejected / ((double)m_objects.size()+rejected)) * 100.0;

		std::cout << "Rejected " << rejected << " objects (" << percent << "%)" << std::endl;
	}

	void Physics_Object_List::update(double delta)
	// called every frame
	{
 		std::cout << "Delta time: " << delta << std::endl;

		int cmd_cnt = 0;

		// make a copy of nudge_ctr and reset to 0
		auto nudge_ctr = m_commands.nudge_ctr;
		m_commands.nudge_ctr = 0;

		for (auto i = 0; i < nudge_ctr; ++i) {
			++cmd_cnt;
			auto C = m_commands.nudge_commands.front();

			nudge(delta, C.id, C.pos, C.dir);
			
			m_commands.nudge_commands.pop();
		}

		std::cout << "Executed " << cmd_cnt << " command(s)" << std::endl; 
	}

	uint64 Physics_Object_List::add_object(Physics_Data data)
	// add a Physics_Object to the list and return its id if successful, otherwise return 0
	{
		if (resist_at_pos(data.pos) == resist_solid) {
			std::cout << "Object spawn blocked at " << +data.pos.x << ", " << +data.pos.y << ", " << +data.pos.z << std::endl;
			rejected++;
			return 0;
		}

		m_obj_ctr++;

		Physics_Object obj = {
			m_obj_ctr,
			data.pos,
			data.off,
			data.dir,
			data.collider,
			data.mass,
			data.speed
		};

		// add a nudge command to the queue
		m_commands.add({m_obj_ctr, data.pos, data.dir});

		// add the object to the map
		m_objects.at(data.pos).push_back(obj);

		return m_obj_ctr;
	
	}

 	Collide_Resistance Physics_Object_List::resist_at_pos(Position& p)
	// returns the highest Collide_Resistance found at p
	{
		Collide_Resistance highest = resist_air;

		for (auto obj : m_objects.at(p)) {
			if (obj.collider.resistance > highest)
				highest = obj.collider.resistance;
		}

		return highest;
	}
 
// physics END BRACE
}