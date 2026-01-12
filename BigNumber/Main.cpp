#include <iostream>

import big_number_handler;

int main() {
	try {
		BigInteger a;
		a.set_value(765l);
		a.sum(15.0l);
		std::cout << a;
	}
	catch (std::exception err) {
		std::cerr << err.what();
	}
	return 0;
}