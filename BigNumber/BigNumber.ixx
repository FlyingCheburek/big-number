export module big_number_handler:big_number;

import <vector>;
import <regex>;

using DIGIT_LIST = std::vector<short>;

export class BigNumber {

public:

	enum Type {
		GENERIC,
		INTEGER,
		DECIMAL,
		INVALID
	};

	enum Sign {
		POSITIVE,
		NEGATIVE
	};

protected:

	struct Digits {
		DIGIT_LIST whole;
		DIGIT_LIST fractional;
	};
	
// class attributes and methods

	Type type;
	Sign sign;
	Digits digits;

public:

	BigNumber() noexcept : type(GENERIC), sign(POSITIVE), digits({ .whole = {0}, .fractional = {0} }) {  }

	Type get_type() const noexcept { return type; }
	Sign get_sign() const noexcept { return sign; }
	Digits get_digits() const noexcept { return digits; }
	DIGIT_LIST get_digits_whole() const noexcept { return digits.whole; }
	DIGIT_LIST get_digits_fractional() const noexcept { return digits.fractional; }

protected:

	void set_type(const Type type) noexcept { this->type = type; }
	void set_sign(const Sign sign) noexcept { this->sign = sign; }
	void set_digits(const Digits digits) noexcept { this->digits = digits; }
	void set_digits_whole(const DIGIT_LIST whole) noexcept { digits.whole = whole; }
	void set_digits_fractional(const DIGIT_LIST fractional) noexcept { digits.fractional = fractional; }

public:

	virtual void set_value(const char* value) = 0;
	virtual void set_value(const std::string& value) = 0;

	virtual void sum(const char* value) = 0;
	virtual void sum(const std::string& value) = 0;

	virtual std::string to_string() const noexcept = 0;
	

// static methods

	static Type inspect_type(const std::string& value) noexcept {
		return inspect_type(value.c_str());
	}

	static Type inspect_type(const char* value) noexcept {
		if (std::regex_match(value, std::regex("^-?\\d+$"))) {
			return INTEGER;
		}
		if (std::regex_match(value, std::regex("^-?\\d*\\.\\d+$"))) {
			return DECIMAL;
		}
		return INVALID;
	}

};