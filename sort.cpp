#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <chrono>

void bubble_sort(std::vector<int>& in)
// a bubble sort implementation
{
	bool swap = true;

	while (swap) {

		swap = false;
	
		for (auto i = 0; i < in.size()-1; ++i) {
			
			int tmp = in[i+1];

			if (in[i] > tmp) {
				// swap values
				in[i+1] = in[i];
				in[i]	= tmp;
				swap	= true;
			}
		}
	}

	return;
}

void selection_sort(std::vector<int>& in)
// selection sort implementation
{
	//only call vector::size() once
	auto limit = in.size();

	// index for lowest value;
	int lowest;

	for (auto i = 0; i < limit; ++i) {
		// outer loop over entire vector
		lowest = i;
		
		for (auto c = i+1; c < limit; ++c) {
			
			if (in[c] < in[lowest]) {
				lowest = c;
			}
		}

		// swap lowest value
		if (lowest != i) {
			int tmp = in[i];

			in[i]		= in[lowest];
			in[lowest]	= tmp;
		}
	} 

	return;
}

void insertion_sort(std::vector<int>& in)
// insertion sort implementation
{
	int tmp;
	for (auto i = 1; i < in.size(); ++i) {
		
		tmp = in[i];

		for (auto c = i-1; c >= 0; --c) {

			if (in[c] > tmp) {
				in[c+1] = in[c];
				in[c]	= tmp;
			}
		}
	}

	return;
}

int main(int arc, char** arv)
// main function
{
	std::srand(32);

	// make a vector for each sorting algorithm, with 100000 numbers
	std::vector<int> vec1;
	for (auto i = 0; i < 10000; ++i) {
		vec1.push_back(std::rand() % 10000);
	}

	auto vec2 = vec1; auto vec3 = vec1; auto vec4 = vec1;

	using clock = std::chrono::steady_clock;
	
	auto start = clock::now();
	auto end = clock::now();
	std::chrono::duration<double> time;

	//*** Bubble Sort ***//
	start = clock::now();
	bubble_sort(vec1);
	end = clock::now();
	time = (end - start);

	std::cout << "Bubble sort: " << time.count() << std::endl << std::endl;

	//*** Selection Sort ***//
	start = clock::now();
	selection_sort(vec2);
	end = clock::now();
	time = (end - start);

	std::cout << "Selection sort: " << time.count() << std::endl << std::endl;

	//*** Insertion Sort ***//
	start = clock::now();
	insertion_sort(vec3);
	end = clock::now();
	time = (end - start);

	std::cout << "Insertion sort: " << time.count() << std::endl << std::endl;

	//*** std::sort() ***//
	start = clock::now();
	std::sort(vec4.begin(), vec4.end());
	end = clock::now();
	time = (end - start);

	std::cout << "std::sort(): " << time.count() << std::endl << std::endl;
}