#include <iostream>

import big_number_handler;

int main() {
	try {
		BigInteger a;
		a.set_value(-763l);
		std::cout << (a.is_equal_or_less_than("-764") ? "TRUE" : "FALSE");
	}
	catch (std::exception err) {
		std::cerr << err.what();
	}
	return 0;
}