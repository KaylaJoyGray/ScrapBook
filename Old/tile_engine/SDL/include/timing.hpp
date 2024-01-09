#ifndef TIMING_H
#define TIMING_H

class timer {
	private:
		double frame_delay;
		unsigned long long int frame_start;
		double frame_time;
		int FPS;
	public:
		timer(int set_FPS=30);
		void start_frame();
		void delay_frame();
		void new_FPS(int set_FPS);
};

#endif
