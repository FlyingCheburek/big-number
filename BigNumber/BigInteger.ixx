export module big_number_handler:big_integer;

import :big_number;
import <string>;
import <type_traits>;
import <ostream>;
import <stdexcept>;

import <iostream>;

export class BigInteger : public BigNumber {
public:
	BigInteger() noexcept { type = INTEGER; }

	// set_value
	void set_value(const char* value) override {
		Type _type = inspect_type(value);
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
				sign = POSITIVE;
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
				sign = POSITIVE;
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
		set_value(value.c_str());
	}

	template<typename T> requires std::is_arithmetic_v<T>
	void set_value(const T value) {
		set_value(std::to_string(value).c_str());
	}
	//

	// is_equal operation
	bool is_equal(const char* value) override {
		Type _type = inspect_type(value);
		if (_type == INTEGER) {
			BigInteger _value;
			_value.set_value(value);
			return is_equal(_value);
		}
		else if (_type == DECIMAL) {
			std::string whole = "";
			while (*value != '.') {
				whole.push_back(*value);
				value++;
			}
			value++;
			while (*value != '\0') {
				if (*value != '0')
					return false;
				value++;
			}
			BigInteger _value;
			_value.set_value(whole);
			return is_equal(_value);
		}
		else {
			throw std::invalid_argument("Error in BigInteger::is_equal: invalid number formatting provided.");
		}
		return false;
	}
	bool is_equal(const std::string& value) override {
		return is_equal(value.c_str());
	}

	template<typename T> requires std::is_arithmetic_v<T>
	bool is_equal(const T value) {
		return is_equal(std::to_string(value).c_str());
	}
	bool is_equal(const BigInteger value) {
		if (sign != value.get_sign())
			return false;

		DIGIT_LIST _value = value.get_digits_whole();

		if (digits.whole.size() != _value.size())
			return false;

		for (auto it_a = digits.whole.cbegin(), it_b = _value.cbegin(); it_b != _value.cend(); it_a++, it_b++) {
			if (*it_a != *it_b)
				return false;
		}
		return true;
	}
	//

	// is_not_equal operation
	bool is_not_equal(const char* value) override {
		bool ret = true;
		try {
			ret = !is_equal(value);
		}
		catch (std::exception err) {
			throw std::invalid_argument("Error in BigInteger::is_not_equal: invalid number formatting provided.");
		}
		return ret;
	}	
	bool is_not_equal(const std::string& value) override {
		return is_not_equal(value.c_str());
	}

	template<typename T> requires std::is_arithmetic_v<T>
	bool is_not_equal(const T value) {
		return !is_equal(std::to_string(value).c_str());
	}
	bool is_not_equal(const BigInteger value) {
		return !is_equal(value);
	}
	//

	// is_greater_than operation
	bool is_greater_than(const char* value) override {
		Type _type = inspect_type(value);
		if (_type == INTEGER) {
			BigInteger _value;
			_value.set_value(value);
			return is_greater_than(_value);
		}
		else if (_type == DECIMAL) {
			std::string whole = "";
			while (*value != '.') {
				whole.push_back(*value);
				value++;
			}
			value++;
			while (*value != '\0') {
				if (*value != '0')
					return false;
				value++;
			}
			BigInteger _value;
			_value.set_value(whole);
			return is_greater_than(_value);
		}
		else {
			throw std::invalid_argument("Error in BigInteger::is_greater_than: invalid number formatting provided.");
		}
		return true;
	}
	bool is_greater_than(const std::string& value) override {
		return is_greater_than(value.c_str());
	}

	template<typename T> requires std::is_arithmetic_v<T>
	bool is_greater_than(const T value) {
		return is_greater_than(std::to_string(value).c_str());
	}
	bool is_greater_than(const BigInteger value) {
		DIGIT_LIST _value = value.get_digits_whole();

		if (sign == NEGATIVE) {
			if (value.get_sign() == POSITIVE)
				return false;

			if (digits.whole.size() != _value.size())
				return digits.whole.size() < _value.size();
			else {
				size_t eq_len = 0;
				for (auto it_a = digits.whole.cbegin(), it_b = _value.cbegin(); it_a != digits.whole.cend(); it_a++, it_b++) {
					if (*it_a > *it_b)
						return false;
					if (*it_a == *it_b) {
						eq_len++;
					}
				}
				return eq_len != _value.size();
			}
		}
		else {
			if (value.get_sign() == NEGATIVE)
				return true;

			if (digits.whole.size() != _value.size())
				return digits.whole.size() > _value.size();
			else {
				size_t eq_len = 0;
				for (auto it_a = digits.whole.cbegin(), it_b = _value.cbegin(); it_a != digits.whole.cend(); it_a++, it_b++) {
					if (*it_a < *it_b)
						return false;
					if (*it_a == *it_b) {
						eq_len++;
					}
				}
				return eq_len != _value.size();
			}
		}
	}
	//
		
	// sum operation
	void sum(const char* value) override {
		BigInteger _value;
		try {
			_value.set_value(value);
			sum(_value);
		}
		catch (const std::exception err) {
			throw std::invalid_argument("Error in BigInteger::sum: invalid number formatting provided.");
		}
	}
	void sum(const std::string& value) override {
		sum(value.c_str());
	}

	template<typename T> requires std::is_arithmetic_v<T>
	void sum(const T value) {
		sum(std::to_string(value).c_str());
	}

	void sum(const BigInteger value) noexcept {
		if (sign == value.get_sign()) {
			DIGIT_LIST a = get_digits_whole(), b = value.get_digits_whole();
			DIGIT_LIST* _a = nullptr, * _b = nullptr;
			if (a.size() >= b.size()) {
				_a = &a;
				_b = &b;
			}
			else {
				_a = &b;
				_b = &a;
			}
			size_t max_num_len = _b->size(), i = 0;
			for (auto a_it = _a->rbegin(), b_it = _b->rbegin(); a_it != _a->rend(); i++, a_it++) {
				if (i < max_num_len) {
					*a_it += *b_it;
					if ((a_it + 1) != _a->rend()) {
						*(a_it + 1) += *a_it / 10;
						*a_it %= 10;
					}
					b_it++;
				}
				else if (*a_it > 9 && (a_it + 1) != _a->rend()) {
					*(a_it + 1) += *a_it / 10;
					*a_it %= 10;				
				}
			}
			digits.whole.clear();
			for (auto a_it = _a->begin(); a_it != _a->end(); a_it++) {
				if (*a_it > 9) {
					digits.whole.push_back(*a_it / 10);
					digits.whole.push_back(*a_it % 10);
				} 
				else {
					digits.whole.push_back(*a_it);
				}
			}
		}
		else {
			// TODO (subtraction)...
		}
	}
	//

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
