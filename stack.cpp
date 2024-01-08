#include <vector>
#include <string>
#include <iostream>

class cstack
// there is an STL stack, but we'll use this one for the exercise
{
	private:
		std::vector<char> data;
	public:
		cstack() = default;
		
		void insert(char c)
		// insert
		{
			data.push_back(c);
		}
		
		void pop()
		// pop
		{
			data.pop_back();
		}
 
		char read()
		// read
		{
			return data.back();		
		}

		bool empty()
		// check if stack is empty
		{
			return data.empty();
		}
};

std::string reverseString(std::string s)
// reverse a string using our stack implementation 
{
	cstack stack = cstack();
	std::string result;

	for (auto c : s) {
	
		stack.insert(c);
	}

	while (!stack.empty()) {
	
		result += stack.read();
		stack.pop();
	}

	return result;
}

int main(int argc, char** argv) {
	
	std::string reversed = reverseString("reversed");	

	std::cout << reversed << std::endl;
}