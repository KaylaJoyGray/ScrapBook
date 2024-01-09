#ifndef TIMER_HPP
#define TIMER_HPP

#include "fixed_int.hpp"

class delta_timer {
	private:
		uint64 last_time;
	public:
		delta_timer();
		double get_delta();
};

#endif
