#ifndef BODY_PARTS_H
#define BODY_PARTS_H

#include <vector>
#include <string>

enum organ_type {
	type_none = -1,
	type_soft,
	type_bony,
	type_muscle,
	type_major,
	type_minor,
	type_combo,
	type_booster
};

organ_type string_to_organ_type(std::string input);

enum organ_trait {
	trait_none = -1,
	trait_cognitive,
	trait_nervous,
	trait_circulatory,
	trait_respiratory,
	trait_digestive,
	trait_filtration,
	trait_stomach,
	trait_immune,
	trait_vision,
	trait_hearing,
	trait_voice,
	trait_taste,
	trait_smell
};

organ_trait string_to_organ_trait(std::string input);

class base_part {
	protected:
		int id;
		std::string name;
		
		bool severable;
		bool attached;
	public:
		int get_id();
		std::string get_name();
		void sever();
		bool is_attached();
};

class organ: public base_part {
	protected:
		enum organ_type type;
		
		enum organ_trait system1;
		int system1_weight;
		enum organ_trait system2;
		int system2_weight;
				
		float health;
		float max_health;
		float mass;
		bool alive;
	public:
		organ(
			int set_id,
			std::string set_name,
			float set_mass = 0.0,
			enum organ_type set_type = type_none,
			enum organ_trait set_system1 = trait_none,
			int set_system1_weight = 0,
			enum organ_trait set_system2 = trait_none,
			int set_system2_weight = 0
			);
			
			
			
			
		bool add_system(enum organ_trait new_system, int new_weight);
		void idle(float healing_rate);
		bool damage(float damage_factor);
		enum organ_type get_type();
		float get_health();
		bool is_alive();
		float get_mass();
		int get_system1();
		int get_system1_weight();
		int get_system2();
		int get_system2_weight();
};

class part :public base_part {
	protected:
		//ids of parent parts
		std::vector<int> child_of;
		
		//list of organ ids
		std::vector<int> organ_ids;
	public:
		part(int set_id, std::vector<int> &set_depends, bool set_sever, std::vector<int> &set_organs);
		std::vector<int> get_ids();
		std::vector<int> get_parents();
};


#endif
