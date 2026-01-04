#include <iostream>

import big_number_handler;

int main() {
	try {
		BigInteger x;
		x.set_value<float>(-11171.999f);
		std::cout << x;
	}
	catch (std::exception err) {
		std::cerr << err.what();
	}
	
	
	return 0;
}