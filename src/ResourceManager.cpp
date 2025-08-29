#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Game.h"

// Game::Init() 또는 SceneManager 초기화 시 호출하도록 해야 함
void ResourceManager::Init()
{
    LoadTexture("map", "levels/fun1/map_Flat.bmp", -1, 1, 1);
    LoadTexture("trapdoors", "levels/lemming_trapdoors1.bmp", RGB(255, 255, 255), 1, 10);
    LoadTexture("doors", "levels/lemming_doors.bmp", RGB(255, 255, 255), 3, 8);
    LoadTexture("lemming", "lemming_anim.bmp", RGB(255, 255, 255), 16, 14);
    LoadTexture("rotated_lemming", "rotated_lemming_anim.bmp", RGB(255, 255, 255), 16, 14);
}

void ResourceManager::LoadTexture(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount)
{
    Texture* texture = new Texture();
    texture->Load(key, texturePath, transparent, xFrameCount, yFrameCount);

    _textures[key] = texture;
}

// 동적 할당된 Texture 객체를 전부 delete 후, map 초기화
void ResourceManager::Destroy()
{
    for (auto iter : _textures)
    {
        delete iter.second;
    }
    _textures.clear();
}

// 리소스 매니저에 등록된 텍스처들 중에서 key에 해당하는 텍스처 반환
Texture* ResourceManager::GetTexture(string key)
{
    auto iter = _textures.find(key);
    if (iter != _textures.end())
    {
        return iter->second;
    }
    // 로딩이 안됐거나, 이름이 잘못됐거나
    return nullptr;
}

