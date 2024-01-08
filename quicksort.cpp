#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <iostream>

inline int partition (std::vector<int>& in, int& begin, int& end)
// partition the vector for the quicksort algorithm
// returns the index of the new pivot
{
	int pivot = end - 1;

	int left = begin;
	int right = pivot-1;

	while (true) {	// loop will always eventually reach return statement
		
		while (in[left] <= in[pivot] && left < pivot) {
			++left;
		}

		while (in[right] >= in[pivot] && right > begin) {
			--right;
		}
		
		if (left >= right) {
			int tmp		= in[left];		// swap left and pivot values
			in[left]	= in[pivot];
			in[pivot]	= tmp;
			return left;				// change pivot to left index
		}

		int tmp		= in[left];		// swap left and right values
		in[left]	= in[right];
		in[right]	= tmp;

		left = begin;	right = pivot-1;
	}
}

void quicksort(std::vector<int>& in, int begin=0, int end=-1)
// quicksort implementation
{
	if (end == -1)
		end = in.size();

	if (end - begin <= 0)
		return;

	int pivot = partition(in, begin, end);

	quicksort(in, begin, pivot);
	quicksort(in, pivot+1, end);
}

int main(int argc, char** argv) {

	std::srand(109273);

	std::vector<int> us;

	// we will use an unsorted set to avoid any duplicate values
	std::unordered_set<int> values;

	int count = 0;

	while (count < 1000000) {

		int r = std::rand() % 1000000;
		
		if (!values.contains(r)) {
			us.push_back(r);
			values.emplace(r);
			++count;
		}
	}

	std::cout << "Created vector. Sorting..." << std::endl;

	quicksort(us);

/*   	for (auto i : us) {

		std::cout << i << ", ";
	}
	std::cout << std::endl;
 */ 
 }