#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Game.h"

void ResourceManager::init()
{
    // ������ �ʿ��� �ؽ�ó�� ���ؼ� �ε��Ѵ�.
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
    // ��ü������ �����ϰ� �ִ� ��� ���� �޽��߿� meshName�� �ش��ϴ� ���ҽ� ��ȯ
    auto iter = _textures.find(meshName);
    if (iter != _textures.end())
    {
        return iter->second;
    }
    // �ε��� �ȵưų�, �̸��� �߸��ưų�
    return nullptr;
}

void ResourceManager::loadTexture(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount)
{
    Texture* texture = new Texture();
    texture->load(key, texturePath, transparent, xFrameCount, yFrameCount);
    _textures[key] = texture;
}