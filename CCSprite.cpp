#include "CCSprite.h"

#include "CCSpriteCache.h"

CCSprite::CCSprite(Texture2D tex) {
	this->texture = tex;
	type = ATSPRITE;
	this->contentSize = { (float)this->texture.width, (float)this->texture.height };
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
	this->contentSize = { (float)this->texture.width, (float)this->texture.height };
}

void CCSprite::draw() {
	//DrawTextureEx(this->texture, getPosition(), getRotation(), getScale(), WHITE);
	DrawTexturePro(this->texture,
		{ 0, 0, getContentSize().x, getContentSize().y },
		{ getPositionX(), getPositionY(), getContentSize().x * getScaleX() * getScale(), getContentSize().y * getScaleY() * getScale() },
		{ getContentSize().x * getAnchorPoint().x, getContentSize().y * getAnchorPoint().y }, getRotation(), WHITE);
}