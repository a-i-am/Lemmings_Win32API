#include "pch.h"
#include "Walker.h"
#include "Game.h"
#include "GameScene.h"
#include "JobFactory.h"
enum WalkerAnims
{
    WALKING_LEFT, WALKING_RIGHT, FALLING
};

void Walker::InitAnims(Actor* owner)
{
    jobActor = owner;
    jobSprite = jobActor->CreateSpriteComponent("lemming", 2.f, 16 * 3.f, 14 * 3.f);
    jobSprite_rotated = jobActor->CreateSpriteComponent("rotated_lemming", 2.f, 16 * 3.f, 14 * 3.f);

    jobSprite->getTexture()->GenerateCollisionData(256, 224);
    jobSprite_rotated->getTexture()->GenerateCollisionData(256, 224);

    jobSprite->SetLemmingAnimationData(WALKING_RIGHT, 0, 9, false, true);
    jobSprite->SetLemmingAnimationData(FALLING, 32, 4, false, true);
      
    jobSprite_rotated->SetLemmingAnimationData(WALKING_LEFT, 15, 9, false, true);
    jobSprite_rotated->SetLemmingAnimationData(FALLING, 47, 4, true, true);

    SetWalkingRight(true);
}

void Walker::SetWalkingRight(bool value)
{
	isWalkingRight = value;

	if (isWalkingRight) {
        jobSprite->PlayLemmingAnimation(WALKING_RIGHT);
		state = WALKING_RIGHT_STATE;
	}
	else {
        jobSprite_rotated->PlayLemmingAnimation(WALKING_LEFT);
		state = WALKING_LEFT_STATE;
	}
}

SpriteRenderer* Walker::GetCurrentJobSprite() const
{
    if (state == WALKING_LEFT_STATE) {
        return jobSprite_rotated;
    }
    return jobSprite; // WALKING_RIGHT_STATE, FALLING_STATE 포함
}


void Walker::CheckEscape(const Vector& pos)
{
    GameScene* gameScene = Game::getGameScene();
    if (!gameScene || !gameScene->GetTerrain()) return;
    
    // 레밍 탈출
    RECT escape = gameScene->GetDoor()->GetEscapeBounds();
    // 레밍 발 위치 기준으로 체크
    POINT lemmingFoot = { static_cast<int64>(pos.x), static_cast<int64>(pos.y + footOffsetY) };

    if (IsInPoint(escape, lemmingFoot))
    {
        isFinished = true;
        //jobsprite = _spriteEscaper;
        //nextJob = JobFactory::instance().CreateEscaperJob();
    }
}

bool Walker::TryStepOver(Vector& nextPos, bool right)
{
    const int32 stepHeight = 3;

    for (int32 dy = 1; dy <= stepHeight; ++dy) {
        Vector tryPos = nextPos - Vector(0, dy);
        if (!IsCollisionWall(tryPos)) {
            int32 fall = CollideFloor(tryPos, 2);
            if (fall <= stepHeight) {
                // 발이 바닥보다 1픽셀 위에 오도록 조정
                nextPos = tryPos + Vector(0, fall - groundClearance);
                return true;
            }
        }
    }
    return false;
}

void Walker::HandleWalking(bool right, float deltaTime, Vector& nextPos)
{
    // 수평 이동
    nextPos += Vector(right ? 1 : -1, 0) * deltaTime * walkSpeed;

    if (IsCollisionFront(nextPos)) {
        // Step Over
        if (!TryStepOver(nextPos, right)) {
            // 못 올라감 → 방향 전환
            nextPos = jobActor->GetPosition();
            SetWalkingRight(!right);
        }
        return;
    }

    // 낙하 여부 확인
    int32 fallCheck = CollideFloor(nextPos, 2);
    if (fallCheck > 0) {
        nextPos.y += fallCheck - groundClearance; // 바닥 위 1픽셀
    }
    else {
        if (state != FALLING_STATE) {
            state = FALLING_STATE;
            // isWalkingRight에 따라 올바른 스프라이트에 FALLING 애니메이션 재생
            if (isWalkingRight) {
                jobSprite->PlayLemmingAnimation(FALLING);
            }
            else {
                jobSprite_rotated->PlayLemmingAnimation(FALLING);
            }
        }
    }

    // 탈출 확인
    CheckEscape(nextPos);
}
void Walker::HandleFalling(float deltaTime, Vector& nextPos)
{
    nextPos.y +=  deltaTime * fallSpeed;

    int32 fallCheck = CollideFloor(nextPos, 2);
    
    if (fallCheck > 0) {
        // 아직 공중
        jobSprite->PlayLemmingAnimation(FALLING);
    }
    else {
        // 착지
        nextPos.y += fallCheck;
        //fallSpeed = 0;
        // 착지 후 걷기 상태 복귀
        if (isWalkingRight) {
            jobSprite->PlayLemmingAnimation(WALKING_RIGHT);
        }
        else {
            jobSprite_rotated->PlayLemmingAnimation(WALKING_LEFT);
        }
    }
}

void Walker::UpdateStateMachine(float deltaTime)
{
    GameScene* gameScene = Game::getGameScene();
    if (!gameScene || !gameScene->GetTerrain()) return;

    Vector nextPos = jobActor->GetPosition();

    switch (state)
    {
    case WALKING_LEFT_STATE:
        HandleWalking(false, deltaTime, nextPos);
        break;

    case WALKING_RIGHT_STATE:
        HandleWalking(true, deltaTime, nextPos);
        break;

    case FALLING_STATE:
        HandleFalling(deltaTime, nextPos);
        break;
    }
    jobActor->SetPosition(nextPos);
    GetCurrentJobSprite()->UpdateComponent(deltaTime);
}

string Walker::GetName()
{
	return "WALKER";
}