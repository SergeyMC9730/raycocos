#pragma once

#include "CCSpriteCacheItem.h"
#include <vector>

namespace CCSpriteCache {
	extern std::vector<CCSpriteCacheItem> cache;

	bool exists(const char* filename);
	Texture2D getByFilename(const char* filename);
}