export module big_number_handler:big_number;

import <vector>;

using DIGIT_LIST = std::vector<short>;

export class BigNumber {

public:

	enum Type {
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
};