#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include "materials.hpp"
#include <memory>

namespace scene::entities {
// entities START BRACE

	struct sprite_data {
		// sprite data is defined here and not in sprites.hpp
		// because it is only used by entities
		int sprite_sheet_id;
		int sprite_index;
	};
	
	class entity {
		protected:
			bool alive = true;
		public:
			entity();
			bool is_alive();

			virtual void update(double delta) = 0;
	};

	class block : protected entity {
		private:
			uint16 health;
			double temp;

			int sprite_sheet_id;
			int sprite_index;

			materials::material material;
		public:
			block(materials::material		 set_material,
				  int						 set_sprite_sheet_id = 0,
				  int						 set_sprite_index	 = 0);

			sprite_data get_sprite();
			void update(double delta);
	};	


// entities END BRACE
}

#endif
