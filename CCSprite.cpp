#include "CCSprite.h"

#include "CCSpriteCache.h"

CCSprite::CCSprite(Texture2D tex) {
	this->texture = tex;
	type = ATSPRITE;
}

CCSprite::CCSprite(const char* filename) {
	if (CCSpriteCache::exists(filename)) {
		this->texture = CCSpriteCache::getByFilename(filename);
	}
	else {
		this->texture = LoadTexture("resources/raylib_logo.png");
		CCSpriteCacheItem item;
		item.filename = filename;
		item.texture = this->texture;
		CCSpriteCache::cache.push_back(item);
	}
	type = ATSPRITE;
}

void CCSprite::draw() {
	DrawTextureEx(this->texture, getPosition(), getRotation(), getScale(), WHITE);
}