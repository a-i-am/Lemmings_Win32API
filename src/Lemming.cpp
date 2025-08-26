#include "pch.h"
#include "Lemming.h"
#include "Game.h"
#include "GameScene.h"

Lemming::Lemming(Vector pos) : Super(pos)
{
    //_spriteMoveRight = CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
    //_spriteMoveRight->SetAnimationClip(0, 10);

    //_spriteMoveLeft = CreateSpriteComponent("rotated_lemming", 1.0f, 16 * 3.f, 14 * 3.f);
    //_spriteMoveLeft->SetAnimationClip(6, 15);

    //_spriteEscape = CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
    //_spriteEscape->SetAnimationClip(18, 9);

    //_spriteFall = CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
    //_spriteFall->SetAnimationClip(3, 4);

    //_spriteDig = CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
    //_spriteDig->SetAnimationClip(9, 8);

    //_spriteMoveRight->getTexture()->GenerateCollisionData(256, 224);
    //_spriteMoveLeft->getTexture()->GenerateCollisionData(256, 224);
    //_spriteEscape->getTexture()->GenerateCollisionData(256, 224);
    //_spriteDig->getTexture()->GenerateCollisionData(256, 224);

    SetWalkingRight(true);
    _jobSprite = _spriteMoveRight;

    //state = WALKING_RIGHT_STATE;
    _fallSpeed = 0;

    //this->shaderProgram = &ShaderManager::getInstance().getShaderProgram();
    //this->job = JobFactory::instance().createFallerJob();
    //this->job->initAnims(*shaderProgram);
    //sprite = this->job->getJobSprite();
    //sprite->SetPosition(initialPosition);
    //countdown = NULL;
    //alive = true;
    //isSaved = false;
}


void Lemming::SetWalkingRight(bool value)
{
     _isWalkingRight = value;
     job->SetWalkingRight(value);
}

void Lemming::Update(float deltaTime)
{
    
}

void Lemming::Render(HDC hdc)
{
    if (_jobSprite)
    {
        _jobSprite->RenderComponent(hdc, GetPosition());

        GameScene* gameScene = Game::getGameScene();
        if (!gameScene || !gameScene->GetTerrain()) return;
        Terrain* terrain = gameScene->GetTerrain();

        HBRUSH frontBrush = CreateSolidBrush(RGB(0, 255, 0));
        for (auto& p : job->GetDebugFrontPoints()) {
            Vector local = terrain->worldToLocal(p.x, p.y);
            RECT rc = { (int)local.x, (int)local.y, (int)local.x + 2, (int)local.y + 2 };
            FillRect(hdc, &rc, frontBrush);
        }
        DeleteObject(frontBrush);

        HBRUSH floorBrush = CreateSolidBrush(RGB(255, 0, 0));
        for (auto& p : job->GetDebugFloorPoints()) {
            Vector local = terrain->worldToLocal(p.x, p.y);
            RECT rc = { (int)local.x, (int)local.y, (int)local.x + 2, (int)local.y + 2 };
            FillRect(hdc, &rc, floorBrush);
        }
        DeleteObject(floorBrush);
    
        Door* door = gameScene->GetDoor();
        if (door)
        {
            RECT escape = door->GetEscapeBounds();
            HBRUSH doorBrush = CreateSolidBrush(RGB(0, 0, 255)); // 파란색
            FillRect(hdc, &escape, doorBrush);
            DeleteObject(doorBrush);
        }
    }
}

bool Lemming::outOfMap()
{
    Vector pos = GetPosition();
    return (pos.x < 0 || pos.y < 0 || pos.x > GWinSizeX || pos.y > GWinSizeY);
}
