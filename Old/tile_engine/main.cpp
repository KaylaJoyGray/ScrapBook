/*
 * main.cpp
 *
 * Copyright 2023 Kayla Gray
 *
 */


#include "physics.hpp"
#include "timer.hpp"
#include "SDL2/SDL.h"
#include <iostream>

#include <cstdlib>

using namespace scene::physics;

float randomFloat()
{
    return (float)(std::rand()) / (float)(RAND_MAX);
}

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	delta_timer t = delta_timer();

	//std::cout.setstate(std::ios_base::failbit);

	Physics_Object_List list = Physics_Object_List();
 	Physics_Object_List list2 = Physics_Object_List();
	Physics_Object_List list3 = Physics_Object_List();
	Physics_Object_List list4 = Physics_Object_List();
	Physics_Object_List list5 = Physics_Object_List();
	Physics_Object_List list6 = Physics_Object_List();
	Physics_Object_List list7 = Physics_Object_List();
	Physics_Object_List list8 = Physics_Object_List();
	Physics_Object_List list9 = Physics_Object_List();
	std::cout << "Physics_Object_List created" << std::endl;

	std::srand(1147);

	t.get_delta();

	for (int i = 0; i < 10000; i++) {
		list.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			80.0
		});
	}


	for (int i = 0; i < 125000; i++) {
		list.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			0.0
		});
	}

		for (int i = 0; i < 10000; i++) {
		list2.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			80.0
		});
	}


	for (int i = 0; i < 125000; i++) {
		list2.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			0.0
		});
	}
	
	for (int i = 0; i < 10000; i++) {
		list3.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			80.0
		});
	}


	for (int i = 0; i < 125000; i++) {
		list3.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			0.0
		});
	}

	for (int i = 0; i < 10000; i++) {
		list4.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			80.0
		});
	}


	for (int i = 0; i < 125000; i++) {
		list4.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			0.0
		});
	}

	for (int i = 0; i < 10000; i++) {
		list5.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			80.0
		});
	}


	for (int i = 0; i < 125000; i++) {
		list5.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			0.0
		});
	}

	for (int i = 0; i < 10000; i++) {
		list6.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			80.0
		});
	}


	for (int i = 0; i < 125000; i++) {
		list6.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			0.0
		});
	}

	for (int i = 0; i < 10000; i++) {
		list7.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			80.0
		});
	}


	for (int i = 0; i < 125000; i++) {
		list7.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			0.0
		});
	}

	for (int i = 0; i < 10000; i++) {
		list8.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			80.0
		});
	}


	for (int i = 0; i < 125000; i++) {
		list8.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			0.0
		});
	}

	for (int i = 0; i < 10000; i++) {
		list9.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			80.0
		});
	}


	for (int i = 0; i < 125000; i++) {
		list9.add_object({
			{std::rand()%250, std::rand()%250, std::rand()%250},
			{20.0, 20.0, 20.0},
			Dir_3d(rand() % 26),
			{resist_solid, size_full},
			0.0,
			0.0
		});
	}

	double build_time = t.get_delta();

	double avg = 0.0;

	for (int x = 0; x < 1000; x++) {
		auto d = t.get_delta();
 
		list.update(d);
		list2.update(d);
		list3.update(d);
		list4.update(d);
		list5.update(d);
		list6.update(d);
		list7.update(d);
		list8.update(d);
		list9.update(d);
		avg = (avg > 0.0) ? ((avg + d) / 2.0) : (avg = d);
	}

	std::cout.clear();
	std::cout << "Map Build time: " << build_time << std::endl;
	std::cout << "Average delta time: " << avg << std::endl;
 
	SDL_Quit();

	return 0;
}

