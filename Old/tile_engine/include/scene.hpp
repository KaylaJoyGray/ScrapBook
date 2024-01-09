#ifndef SCENE_HPP
#define SCENE_HPP

#include "physics.hpp"
#include "entities.hpp"

namespace scene {
// scene START BRACE

	class scene : public physics::Physics_Observer {
		private:
			physics::Physics_Object_List m_physics;

		public:
			scene();

	};

// scene END BRACE
}

#endif