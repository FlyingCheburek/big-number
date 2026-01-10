#include <iostream>

import big_number_handler;

int main() {
	try {
		BigInteger a;
		a.set_value<int>(102);
		std::cout << (a.is_equal_or_greater_than("102.0") ? "TRUE" : "FALSE");
	}
	catch (std::exception err) {
		std::cerr << err.what();
	}
	return 0;
}