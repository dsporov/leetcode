/*
3. Longest Substring Without Repeating Characters

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <cassert>

class Solution {
public:
	int lengthOfLongestSubstring(std::string s) {
		std::unordered_map<char, size_t> curChars;

		size_t len = 0;

		size_t pos = 0;
		for (auto c : s) {
			auto it = curChars.find(c);
			if (it != curChars.end()) {
				len = std::max(len, curChars.size());

				size_t prevPos = it->second;
				auto itStart = curChars.begin();
				auto itEnd = curChars.end();
				for (it = itStart; it != itEnd; ) {
					if (it->second <= prevPos) {
						curChars.erase(it++);
					}
					else {
						++it;
					}
				}
			};

			curChars[c] = pos++;
		}

		return std::max(len, curChars.size());
	}
};

void test_LongestSubstringWithoutRepeatingCharacters() {
	Solution sln;

	assert(3 == sln.lengthOfLongestSubstring("dvdf"));

	assert(0 == sln.lengthOfLongestSubstring(""));
	assert(1 == sln.lengthOfLongestSubstring("c"));

	assert(3 == sln.lengthOfLongestSubstring("abcabcbb"));
	assert(1 == sln.lengthOfLongestSubstring("bbbbb"));
	assert(3 == sln.lengthOfLongestSubstring("pwwkew"));
}
