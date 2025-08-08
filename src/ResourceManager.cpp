#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Game.h"

void ResourceManager::init()
{
    // 씬마다 필요한 텍스처를 정해서 로딩한다.
//{
//    Texture* texture = new Texture();
//    texture->Load(L"Player.bmp", RGB(252, 0, 255));
//    _textures["Player"] = texture;
//}
//{
//    Texture* texture = new Texture();
//    texture->Load(L"PlayerBullet.bmp", RGB(255, 0, 255));
//    _textures["PlayerBullet"] = texture;
//}
}

void ResourceManager::destory()
{
    for (auto iter : _textures)
    {
        delete iter.second;
    }
    _textures.clear();
}

Texture* ResourceManager::getTextureInfo(string meshName)
{
    // 전체적으로 관리하고 있는 모든 라인 메시중에 meshName에 해당하는 리소스 반환
    auto iter = _textures.find(meshName);
    if (iter != _textures.end())
    {
        return iter->second;
    }
    // 로딩이 안됐거나, 이름이 잘못됐거나
    return nullptr;
}

void ResourceManager::loadTexture(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount)
{
    Texture* texture = new Texture();
    texture->load(key, texturePath, transparent, xFrameCount, yFrameCount);
    _textures[key] = texture;
}