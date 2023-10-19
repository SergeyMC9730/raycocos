#pragma once

#include "CCSpriteCacheItem.h"
#include <vector>

namespace CCSpriteCache {
	extern std::vector<CCSpriteCacheItem> cache;

	bool exists(std::string filename);
	Texture2D getByFilename(std::string filename);
}