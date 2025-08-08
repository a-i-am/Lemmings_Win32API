#pragma once

#include "Singleton.h"

class Texture;

class ResourceManager : public Singleton<ResourceManager>
{
	friend Singleton<ResourceManager>;
	ResourceManager() {}
public:

	void init();
	void destory(); // 리소스 정리

	Texture* getTextureInfo(string meshName);
	void loadTexture(string key, string texturePath, int32 transparnet, int32 xFrameCount = 1, int32 yFrameCount = 1);

private:
	unordered_map<string, Texture*> _textures;
};