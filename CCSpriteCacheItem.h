#pragma once

#include  "raylib/src/raylib.h"

// typedef struct CCSpriteCacheItem {
// 	std::string filename;
// 	Texture2D texture;
// } CCSpriteCacheItem;

#include <string>

class CCSpriteCacheItem {
public:
	std::string filename;
	Texture2D texture;
};