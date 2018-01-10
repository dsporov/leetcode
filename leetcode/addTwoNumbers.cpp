// leetcode.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>

/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x, ListNode *n = nullptr) : val(x), next(n) {}
};

void print(ListNode *l) {
	while (l != nullptr) {
		std::cout << l->val;
		l = l->next;
	}

	std::cout << std::endl;
}

class Solution_numbers_based {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		NumType val1 = listToNumber(l1);
		NumType val2 = listToNumber(l2);

		return numberToList(val1 + val2);
	}

private:
	typedef unsigned long long NumType;

	NumType revertNumber(NumType val) {
		NumType revVal = 0;
		while (val != 0) {
			revVal = revVal * 10 + (val % 10);
			val = val / 10;
		}

		return revVal;
	}

	NumType listToNumber(ListNode* l) {
		NumType leadingZeroes = 0;
		while (l != nullptr && l->val == 0) {
			++leadingZeroes;
			l = l->next;
		}

		NumType revVal = 0;
		while (l != nullptr) {
			revVal = revVal * 10 + l->val;
			l = l->next;
		}

		NumType val = revertNumber(revVal);
		while (leadingZeroes != 0) {
			val *= 10;
			--leadingZeroes;
		}

		return val;
	}

	ListNode* numberToList(NumType val) {
		if (0 == val)
			return new ListNode(val);

		NumType leadingZeroes = 0;
		while ((val % 10) == 0) {
			val /= 10;
			++leadingZeroes;
		}

		val = revertNumber(val);

		ListNode *next = nullptr;
		while (val != 0) {
			auto l = new ListNode(val % 10);
			l->next = next;
			next = l;
			val = val / 10;
		}

		while (leadingZeroes != 0) {
			auto l = new ListNode(0);
			l->next = next;
			next = l;
			--leadingZeroes;
		}

		return next;
	}
};

ListNode *vecToList(std::vector<int> const& vec) {
	ListNode *l = nullptr;
	ListNode **prev = &l;
	for (int val : vec) {
		*prev = new ListNode(val);
		prev = &((*prev)->next);
	}

	return l;
}

static class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode *l = nullptr;
		ListNode **prev = &l;

		int over = 0;
		while (l1 || l2 || over) {
			int val = over;
			if (l1) val += l1->val;
			if (l2) val += l2->val;

			over = 0;
			while (val >= 10) {
				val -= 10;
				++over;
			}

			*prev = new ListNode(val);

			prev = &((*prev)->next);

			if (l1) l1 = l1->next;
			if (l2) l2 = l2->next;
		}

		return l;
	}

private:
	ListNode *listOffs(ListNode *l, size_t i) {
		while (i != 0) {
			--i;
			l = l->next;
		}
		return l;
	}

	ListNode *addReversed(ListNode *l1, ListNode *l2) {
		ListNode *l = nullptr;
		ListNode **prev = &l;

		size_t len1 = listLen(l1);
		size_t len2 = listLen(l2);
		ListNode *storeList = nullptr;
		if (len1 > len2) {
			storeList = l1;
			l1 = listOffs(l1, len1 - len2);
		}
		else {
			storeList = l2;
			l2 = listOffs(l2, len2 - len1);
		}

		int over = 0;
		while (l1 || l2 || over) {
			int val = over;
			if (l1) val += l1->val;
			if (l2) val += l2->val;

			over = 0;
			while (val > 10) {
				val -= 10;
				++over;
			}

			*prev = new ListNode(val);

			prev = &((*prev)->next);

			if (l1) l1 = l1->next;
			if (l2) l2 = l2->next;
		}

		return l;
	}

	size_t listLen(ListNode *l) {
		size_t len = 0;

		while (l != nullptr) {
			++len;
			l = l->next;
		}

		return len;
	}

	ListNode *reverse(ListNode *l) {
		ListNode *newList = nullptr;

		while (l != nullptr) {
			ListNode *next = l->next;
			l->next = newList;
			newList = l;
			l = next;
		}

		return newList;
	}
};

void test_addTwoNumbers() {
	std::vector<int> v1 = { 2, 4, 3 };
	ListNode *l1 = vecToList(v1);
	print(l1);

	std::vector<int> v2 = { 5, 6, 4 };
	ListNode *l2 = vecToList(v2);
	print(l2);

	ListNode *l3 = Solution().addTwoNumbers(l1, l2);

	print(l3);
}
