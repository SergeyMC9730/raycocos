#include "CCSpriteCache.h"

#include <string>

std::vector<CCSpriteCacheItem> CCSpriteCache::cache;

bool CCSpriteCache::exists(std::string item) {
	int i = 0;
	while (i < cache.size()) {
		std::string item1 = item;
		std::string item2 = cache[i].filename;

		if (item1 == item2) {
			return true;
		}
		i++;
	}
	return false;
}

Texture2D CCSpriteCache::getByFilename(std::string item) {
	int i = 0;
	while (i < cache.size()) {
		std::string item1 = item;
		std::string item2 = cache[i].filename;

		if (item1 == item2) {
			return cache[i].texture;
		}
		i++;
	}
	return {};
}