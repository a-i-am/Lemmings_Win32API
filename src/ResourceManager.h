#pragma once

#include "Singleton.h"

class Texture;

class ResourceManager : public Singleton<ResourceManager>
{
	friend Singleton<ResourceManager>;
	ResourceManager() {}
public:

	void Init();
	void Destroy(); // 리소스 정리
	void LoadTexture(string key, string texturePath, int32 transparnet, int32 xFrameCount = 1, int32 yFrameCount = 1);
	Texture* GetTexture(string key);

private:
	unordered_map<string, Texture*> _textures;
};
