#include <iostream>

import big_number_handler;

int main() {
	try {
		BigInteger a;
		a.set_value<int>(-101);
		std::cout << (a.is_greater_than("-101") ? "TRUE" : "FALSE");
	}
	catch (std::exception err) {
		std::cerr << err.what();
	}
	return 0;
}