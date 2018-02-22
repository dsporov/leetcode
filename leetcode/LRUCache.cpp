// leetcode.cpp : Defines the entry point for the console application.
//

/*
Design and implement a data structure for Least Recently Used (LRU) cache https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU.
It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 ); // 2 is capacity

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

*/

#include <cassert>
#define DEBUG_LRU

#include <unordered_map>

class LRUCache {
public:
	LRUCache(int capacity)
		: m_capicity(capacity)
		, m_lruTail(nullptr)
		, m_lruHead(nullptr)
	{}

	int get(int key) {
		auto it = m_cache.find(key);
		if (it == m_cache.end())
			return -1;

		it->second.lruNode = addUse(key, it->second.lruNode);

		checkConsistensy();

		return it->second.value;
	}

	void put(int key, int value) {
		auto it = m_cache.find(key);
		if (it != m_cache.end()) {
			m_cache[key].value = value;
			m_cache[key].lruNode = addUse(key, it->second.lruNode);

			checkConsistensy();

			return;
		}

		if (m_cache.size() >= m_capicity)
			removeLru();

		m_cache[key].value = value;
		m_cache[key].lruNode = addUse(key);

		checkConsistensy();
	}

private:
	struct LruNode {
		LruNode(int k) : key(k), prev(nullptr), next(nullptr) {}

		int key;
		LruNode *prev;
		LruNode *next;
	};

	LruNode * addUse(int key, LruNode *node = nullptr) {
		if (nullptr == node)
			return newNode(key);

		if (node == m_lruHead)
			return node;

		if (node == m_lruTail)
			m_lruTail = node->prev;

		if (node->prev != nullptr)
			node->prev->next = node->next;
		if (node->next != nullptr)
			node->next->prev = node->prev;

		node->next = m_lruHead;
		m_lruHead->prev = node;
		node->prev = nullptr;
		m_lruHead = node;
		return node;
	}

	void removeLru() {
		int lruKey = m_lruTail->key;
		m_cache.erase(m_cache.find(lruKey));
		popNode();
	}

	LruNode *newNode(int key) {
		if (m_lruTail == nullptr) {
			m_lruTail = m_lruHead = new LruNode(key);
			return m_lruTail;
		}

		m_lruHead->prev = new LruNode(key);
		m_lruHead->prev->next = m_lruHead;
		m_lruHead = m_lruHead->prev;
		return m_lruHead;
	}

	void popNode() {
		if (m_lruTail == m_lruHead) {
			if (m_lruTail != nullptr)
				delete m_lruTail;
			m_lruTail = m_lruHead = nullptr;
			return;
		}

		m_lruTail = m_lruTail->prev;
		delete m_lruTail->next;
		m_lruTail->next = nullptr;
	}

	int m_capicity;

	struct CacheValue {
		LruNode *lruNode;
		int value;
	};

	std::unordered_map<int, CacheValue> m_cache;
	LruNode *m_lruHead, *m_lruTail;

	void checkConsistensy() {
#ifdef DEBUG_LRU
		size_t i = 0;
		LruNode *node = m_lruHead;
		while (node != nullptr) {
			++i;
			if (node->next == nullptr)
				break;
			node = node->next;
		}

		assert(i == m_cache.size());
		assert(node == m_lruTail);
#endif
	}
};

void testCase1() {
	LRUCache cache = LRUCache(2);

	cache.put(1, 1);
	cache.put(2, 2);
	cache.put(3, 3);
	cache.put(4, 4);
	cache.put(2, 2);
	cache.put(1, 1);
	assert(1 == cache.get(1));

	cache.put(3, 3);    // evicts key 2
	assert(-1 == cache.get(2));       // returns -1 (not found)

	cache.put(4, 4);    // evicts key 1

	assert(-1 == cache.get(1));       // returns -1 (not found)
	assert(3 == cache.get(3));       // returns 3
	assert(4 == cache.get(4));       // returns 4
}

void testCase2() {
	LRUCache cache = LRUCache(1);
	cache.put(1, 1);
	cache.put(2, 2);
	cache.put(3, 3);
	assert(-1 == cache.get(1));
	assert(-1 == cache.get(2));
	assert(3 == cache.get(3));
	assert(3 == cache.get(3));

	cache.put(2, 2);
	assert(-1 == cache.get(3));
	assert(2 == cache.get(2));
}

void testCase3() {
	LRUCache cache = LRUCache(3);
	cache.put(1, 1);
	cache.put(2, 2);
	cache.put(3, 3);
	assert(1 == cache.get(1));
	assert(2 == cache.get(2));
	assert(3 == cache.get(3));

	cache.put(2, 22);
	assert(1 == cache.get(1));
	assert(22 == cache.get(2));
	assert(3 == cache.get(3));

	cache.put(4, 4);
	cache.put(5, 5);
	cache.put(6, 6);
	assert(-1 == cache.get(1));
	assert(-1 == cache.get(2));
	assert(-1 == cache.get(3));
	assert(6 == cache.get(6));
	assert(5 == cache.get(5));
	assert(4 == cache.get(4));

	cache.put(11, 11);
	assert(-1 == cache.get(6));
}

void test_LRUCache() {
	testCase1();
	testCase2();
	testCase3();
}
