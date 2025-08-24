#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Game.h"

// Game::init() �Ǵ� SceneManager �ʱ�ȭ �� ȣ���ϵ��� �ؾ� ��
void ResourceManager::init()
{
    loadTexture("map", "levels/fun1/map_Flat.bmp", -1, 1, 1);
    loadTexture("trapdoors", "levels/lemming_trapdoors1.bmp", RGB(255, 255, 255), 1, 10);
    loadTexture("doors", "levels/lemming_doors.bmp", RGB(255, 255, 255), 3, 8);
    loadTexture("lemming", "lemming_anim.bmp", RGB(255, 255, 255), 16, 14);
    loadTexture("rotated_lemming", "rotated_lemming_anim.bmp", RGB(255, 255, 255), 16, 14);
}

// ���� �Ҵ�� Texture ��ü�� ���� delete ��, map �ʱ�ȭ
void ResourceManager::destroy()
{
    for (auto iter : _textures)
    {
        delete iter.second;
    }
    _textures.clear();
}

// ���ҽ� �Ŵ����� ��ϵ� �ؽ�ó�� �߿��� key�� �ش��ϴ� �ؽ�ó ��ȯ

Texture* ResourceManager::getTexture(string key)
{
    auto iter = _textures.find(key);
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
    texture->Load(key, texturePath, transparent, xFrameCount, yFrameCount);
    _textures[key] = texture;
}
