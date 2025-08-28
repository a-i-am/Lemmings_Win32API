#include "pch.h"
#include "Lemming.h"
#include "Game.h"
#include "GameScene.h"
#include "JobFactory.h"
#include "Job.h"
#include <cassert>

Lemming::Lemming(Vector pos) : Super(pos)
{
    //job = JobFactory::instance().CreateFallerJob();
    job = JobFactory::instance().CreateWalkerJob();
    job->InitAnims(this);
    _jobSprite = job->GetCurrentJobSprite();
    SetPosition(pos);
    //countdown = NULL;
    _isAlive = true;
    _isSaved = false;
    _fallSpeed = 0;
}

void Lemming::SetWalkingRight(bool value)
{
     _isWalkingRight = value;
     job->SetWalkingRight(value);
}

void Lemming::WriteDestiny()
{

}

void Lemming::ChangeJob(Job* nextJob)
{
    if (job) {
        _isWalkingRight = job->GetIsWalkingRight();
        delete job;
    }

    delete this->job;
    this->job = nextJob;
    this->job->InitAnims(this);
    nextJob->SetWalkingRight(_isWalkingRight);

    Vector oldPosition = _pos;

    //_jobSprite = this->job->GetJobSprite();
    SetPosition(oldPosition);
}

bool Lemming::IsOutOfMap()
{
    Vector pos = GetPosition();
    return (pos.x < 0 || pos.y < 0 || pos.x > GWinSizeX || pos.y > GWinSizeY);
}

void Lemming::Update(float deltaTime)
{
    job->UpdateStateMachine(deltaTime);
    // TODO : digger 구현 후 Countdown 클래스 작성, 
    // 레밍 점수 계산 등 시스템 로직 작성 같이하기
    // 
    //if (IsOutOfMap()) {
    //    _isAlive = false;
    //    delete this->job;
    //}
    //else {
    //    if (/*countdown != NULL && countdown->isOver()*/) {
    //        //ChangeJob(JobFactory::instance().createExploderJob());
    //        //delete countdown;
    //        //countdown = NULL;
    //    }
    //    else {
    //        job->UpdateStateMachine(deltaTime);
    //        if (/*countdown != NULL*/) {
    //            /*countdown->setPosition(glm::vec2(6, -8) + sprite->position());
    //            countdown->Update(deltaTime);*/
    //        }
    //        if (job->IsFinished()) {
    //            if (job->GetNextJob() == NULL) {
    //                if (job->GetName() == "ESCAPER") {
    //                    _isSaved = true;
    //                }
    //                else {
    //                    _isAlive = false;
    //                }
    //            }
    //            if (_isAlive && !_isSaved) {
    //                ChangeJob(job->GetNextJob());
    //            }
    //        }
    //    }
    //}


}

void Lemming::Render(HDC hdc)
{
    _jobSprite->RenderComponent(hdc, GetPosition());
    SpriteRenderer* currentSprite = job->GetCurrentJobSprite();
    if (currentSprite) {
        // RenderComponent 함수를 호출하여 스프라이트 렌더링
        currentSprite->RenderComponent(hdc, GetPosition());

        GameScene* gameScene = Game::getGameScene();
        if (!gameScene || !gameScene->GetTerrain()) return;
        Terrain* terrain = gameScene->GetTerrain();

        HBRUSH frontBrush = CreateSolidBrush(RGB(0, 255, 0));
        for (auto& p : job->GetDebugFrontPoints()) {
            Vector local = terrain->worldToLocal(p.x, p.y);
            RECT rc = { (int32)local.x, (int32)local.y, (int32)local.x + 2, (int32)local.y + 2 };
            FillRect(hdc, &rc, frontBrush);
        }
        DeleteObject(frontBrush);

        HBRUSH floorBrush = CreateSolidBrush(RGB(255, 0, 0));
        for (auto& p : job->GetDebugFloorPoints()) {
            Vector local = terrain->worldToLocal(p.x, p.y);
            RECT rc = { (int32)local.x, (int32)local.y, (int32)local.x + 2, (int32)local.y + 2 };
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