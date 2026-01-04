export module big_number_handler:big_integer;

import :big_number;
import <string>;

export class BigInteger : public BigNumber {
public:

	void set_value(const char* value) override {
		// TODO...
	}
	void set_value(const std::string& value) override {
		return set_value(value.c_str());
	}

	template<typename T> requires std::is_arithmetic_v<T>
	void set_value(const T value) {
		return set_value(std::to_string(value).c_str());
	}
};
