export module big_number_handler:big_integer;

import :big_number;
import <string>;
import <type_traits>;
import <ostream>;
import <stdexcept>;

export class BigInteger : public BigNumber {
public:

	void set_value(const char* value) override {
		Type _type = BigNumber::inspect_type(value);
		if (_type == INTEGER) {
			digits.whole.clear();
			const char* digit = value;
			sign = POSITIVE;
			if (*digit == '-') {
				sign = NEGATIVE;
				digit++;
			}
			while (*digit == '0') {
				digit++;
			}
			if (*digit == '\0') {
				digits.whole.push_back(0);
				sign = ZERO;
			}
			else {
				for (; *digit != '\0'; digit++) {
					digits.whole.push_back(*digit - '0');
				}
			}
		}
		else if (_type == DECIMAL) {
			digits.whole.clear();
			const char* digit = value;
			sign = POSITIVE;
			if (*digit == '-') {
				sign = NEGATIVE;
				digit++;
			}
			while (*digit == '0') {
				digit++;
			}
			if (*digit == '.') {
				digits.whole.push_back(0);
				sign = ZERO;
			}
			else {
				for (; *digit != '.'; digit++) {
					digits.whole.push_back(*digit - '0');
				}
			}
		}
		else {
			throw std::invalid_argument("Error in BigInteger::set_value: invalid number formatting provided.");
		}
	}
	void set_value(const std::string& value) override {
		return set_value(value.c_str());
	}

	template<typename T> requires std::is_arithmetic_v<T>
	void set_value(const T value) {
		return set_value(std::to_string(value).c_str());
	}

	std::string to_string() const noexcept override {
		std::string ret = sign == NEGATIVE ? "-" : "";
		for (auto d : digits.whole) {
			ret.push_back(d + '0');
		}
		return ret;
	}

// std::cout<< overloading
	friend std::ostream& operator<<(std::ostream& os, const BigInteger& obj) {
		os << obj.to_string();
		return os;
	}
};
