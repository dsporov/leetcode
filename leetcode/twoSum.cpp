#include <vector>

/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

#include <unordered_map>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
	std::vector<int> res;

	if (nums.size() < 2)
		return res;

	std::unordered_map<int, int> processed;

	processed[nums.front()] = 0;

	for (size_t i = 1; i < nums.size(); ++i) {
		int val = target - nums[i];
		auto it = processed.find(val);
		if (it != processed.end()) {
			res.push_back(it->second);
			res.push_back(i);
			continue;
		}

		processed[nums[i]] = i;
	}

	return res;
}

void test_twoSum() {
	std::vector<int> nums = { 2, 7, 11, 15 };
	auto res = twoSum(nums, 9);
}

