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

#include <unordered_map>
#include <vector>

#include <cassert>

class LRUCache {
public:
	LRUCache(int capacity) : m_capicity(capacity) {}

	int get(int key) {
		auto it = m_cache.find(key);
		if (it == m_cache.end())
			return -1;
		
		addUse(key);
		return it->second;
	}

	void put(int key, int value) {
		if (m_cache.size() >= m_capicity)
			removeLru();

		m_cache[key] = value;
		addUse(key);
	}

private:
	void addUse(int key) {
		auto it = std::find(std::begin(m_lru), std::end(m_lru), key);
		if (it != m_lru.end())
			m_lru.erase(it);
		m_lru.insert(m_lru.begin(), key);
	}

	void removeLru() {
		int lruKey = m_lru.back();
		m_cache.erase(m_cache.find(lruKey));
		m_lru.pop_back();
	}

	int m_capicity;

	std::unordered_map<int, int> m_cache;
	std::vector<int> m_lru;
};

void main() {
	LRUCache cache = LRUCache(2);

	cache.put(1, 1);
	cache.put(2, 2);
	assert(1 == cache.get(1));

	cache.put(3, 3);    // evicts key 2
	assert(-1 == cache.get(2));       // returns -1 (not found)

	cache.put(4, 4);    // evicts key 1

	assert(-1 == cache.get(1));       // returns -1 (not found)
	assert(3 == cache.get(3));       // returns 3
	assert(4 == cache.get(4));       // returns 4
}
