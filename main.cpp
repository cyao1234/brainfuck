#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

/*
> 	Increment the data pointer by one (to point to the next cell to the right).
< 	Decrement the data pointer by one (to point to the next cell to the left).
+ 	Increment the byte at the data pointer by one.
- 	Decrement the byte at the data pointer by one.
. 	Output the byte at the data pointer.
, 	Accept one byte of input, storing its value in the byte at the data pointer.
[ 	If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next
command, jump it forward to the command after the matching ] command. ] 	If the byte at the data pointer is
nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after
the matching [ command.
*/

uint64_t DP = 0;
uint64_t PP = 0;

std::unordered_map<uint64_t, char> memory;

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage:\n";
		std::cout << argv[0] << " [filename]" << std::endl;
	}

	std::string code;

	{
		std::ifstream file(argv[1]);

		if (!file.is_open()) {
			std::cerr << "Error opening file!" << std::endl;
			return 1;
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		code = buffer.str();
	}

	char ch;

	while (PP < code.size()) {
		switch (code[PP]) {
			case '>':
				if (DP == UINT64_MAX) {
					std::cerr << "Data pointer overflow" << std::endl;
					return 1;
				}

				++DP;

				break;
			case '<':
				[[unlikely]] if (DP == 0) {
					std::cerr << "Data pointer underflow" << std::endl;
					return 1;
				}

				--DP;

				break;
			case '+':
				if (!memory.contains(DP)) {
					memory[DP] = 1;
				}

				[[unlikely]] if (memory.at(DP) == UINT64_MAX) {
					std::cerr << "Memory overflow" << std::endl;
					return 1;
				}

				++memory.at(DP);

				break;
			case '-':
				if (!memory.contains(DP) || memory.at(DP) == 0) {
					std::cerr << "Memory underflow" << std::endl;
					return 1;
				}

				--memory.at(DP);

				break;
			case '.':
				if (!memory.contains(DP)) {
					memory[DP] = 0;
				}

				std::cout << memory.at(DP);

				break;
			case ',':
				std::cin >> memory[DP];

				break;
			case '[':
				if (!memory.contains(DP)) {
					memory[DP] = 0;
				}

				if (memory.at(DP) == 0) {
				}

				uint64_t loop = 0;

				break;
			case ']':
				if (!memory.contains(DP)) {
					memory[DP] = 0;
				}

				break;

			default:
				break;
		}
		
		++PP;
	}
}
