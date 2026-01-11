#include <iostream>

import big_number_handler;

int main() {
	try {
		BigInteger a;
		a.set_value<int>(-1);
		std::cout << (a.is_less_than("-2") ? "TRUE" : "FALSE");
	}
	catch (std::exception err) {
		std::cerr << err.what();
	}
	return 0;
}