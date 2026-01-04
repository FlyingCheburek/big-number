export module big_number_handler:big_number;

import <vector>;

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
		ZERO,
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

	BigNumber() noexcept : type(GENERIC), sign(ZERO), digits({ .whole = {0}, .fractional = {0} }) {  }

	Type get_type() const noexcept { return type; }
	Sign get_sign() const noexcept { return sign; }
	Digits get_digits() const noexcept { return digits; }

protected:

	void set_type(const Type type) noexcept { this->type = type; }
	void set_sign(const Sign sign) noexcept { this->sign = sign; }
	void set_digits(const Digits digits) noexcept { this->digits = digits; }
	void set_digits_whole(const DIGIT_LIST whole) { digits.whole = whole; }
	void set_digits_fractional(const DIGIT_LIST fractional) { digits.fractional = fractional; }
};