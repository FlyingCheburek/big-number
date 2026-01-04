#include <iostream>
#include <Windows.h>

import big_number_handler;

int main() {
	BigInteger a, b, x;
	x.set_value<int>(-1);
	a.set_value<int>(-999);
	b.set_value<int>(-7777);
	while (true) {
		try {
			x.sum(a);
			std::cout << x << "\n";
			a.sum(b);
		}
		catch (std::exception err) {
			std::cerr << err.what();
		}
		Sleep(100);
	}
	return 0;
}