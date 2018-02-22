#include <cmath>

int getDigit(int x, int idx, int radix) {
	return static_cast<int>(x / pow(radix, idx)) % radix;
}

bool isPalindrome(int x) {
	if (x < 0)
		return false;
	if (0 == x)
		return true;

	const int radix = 10;
	int len = 0;
	int storedX = x;
	while (x > 0) {
		x = x / radix;
		++len;
	}

	x = storedX;
	for (int idx1 = 0, idx2 = len - 1; idx1 < idx2; ++idx1, --idx2) {
		int digit1 = getDigit(x, idx1, radix);
		int digit2 = getDigit(x, idx2, radix);
		if (digit1 != digit2)
			return false;
	}

	return true;
}

void test_isPalindrome() {
	bool r0 = isPalindrome(11);
	bool r1 = isPalindrome(101);
	bool r2 = isPalindrome(10);
	bool r3 = isPalindrome(103);
	bool r4 = isPalindrome(1123211);
}
