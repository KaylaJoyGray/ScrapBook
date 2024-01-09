
#include "entities.hpp"

using namespace scene::entities;

namespace scene::entities {
// entities START BRACE

	entity::entity()
	// constructor for entity
	{

	}

	bool entity::is_alive()
	// returns whether or not the entity is alive
	{
		return this->alive;
	}

	block::block(materials::material 		set_material,
				 int 						set_sprite_sheet_id,
				 int 						set_sprite_index)
				 : entity ()
	// constructor for block
	{
		this->health 			= set_material.init_health;
		this->material 			= set_material;
		this->sprite_sheet_id 	= set_sprite_sheet_id;
		this->sprite_index 		= set_sprite_index;
	}

	sprite_data block::get_sprite()
	// returns the sprite data for the block
	{
		sprite_data result;
		result.sprite_sheet_id 	= this->sprite_sheet_id;
		result.sprite_index    	= this->sprite_index;

		return result;
	}

	void block::update(double delta)
	// called every frame to update the block
	{
		if (!this->is_alive())
			return;

		// apply temperature
		this->health -= materials::apply_temperature(delta, this->material, this->temp);

		return;
	}

// entities END BRACE
}