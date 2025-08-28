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
    jobSprite->getTexture()->GenerateCollisionData(256, 224);

    jobSprite->SetLemmingAnimationData(WALKING_LEFT, 1, 9, false, true);
    jobSprite->SetLemmingAnimationData(WALKING_RIGHT, 1, 9, false, true);
    jobSprite->SetLemmingAnimationData(FALLING, 32, 4, false, true);

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
		jobSprite->PlayLemmingAnimation(WALKING_LEFT);
		state = WALKING_LEFT_STATE;
	}
}

void Walker::UpdateStateMachine(float deltaTime)
{
    char buffer[128];
    sprintf_s(buffer, sizeof(buffer),
        "Walker::UpdateStateMachine called, state=%d\n", static_cast<int>(state));
    OutputDebugStringA(buffer);

	GameScene* gameScene = Game::getGameScene();
	if (!gameScene || !gameScene->GetTerrain()) return;

    Vector nextPos = jobActor->GetPosition();
	int32 fall;

    switch (state)
    {
    case WALKING_LEFT_STATE:
        nextPos += Vector(-1, 0) * deltaTime * walkSpeed; // ← 수평 이동

        if (IsCollisionFront(nextPos)) {
            jobSprite->PlayLemmingAnimation(WALKING_RIGHT);
            // Step Over 로직
            bool climbed = false;
            const int32 stepHeight = 3; // 최대 3픽셀까지만 올라감

            for (int32 dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!IsCollisionWall(tryPos)) {
                    int32 fall = CollideFloor(tryPos, 2);
                    if (fall <= stepHeight) {
                        // 발이 바닥보다 1픽셀 위에 오도록 조정
                        nextPos = tryPos + Vector(0, fall - groundClearance);
                        climbed = true;
                        break;
                    }
                }
            }

            if (!climbed) {
                // 못 올라감 → 방향 전환
                nextPos = jobActor->GetPosition();
                SetWalkingRight(true);
            }
        }
        else {
            int32 fallCheck = CollideFloor(nextPos, 2);
            if (fallCheck < 2) {
                nextPos.y += fallCheck - groundClearance; // 바닥 위 1픽셀
                fallSpeed = 0;
                state = isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;
            }
            else
            {
                if (state != FALLING_STATE) {  // 이미 낙하중이 아니면 전환
                    state = FALLING_STATE;
                    jobSprite->PlayLemmingAnimation(FALLING);
                }
                //nextJob = JobFactory::instance().CreateFallerJob();
            }

            // 레밍 탈출
            RECT escape = gameScene->GetDoor()->GetEscapeBounds();
            // 레밍 발 위치 기준으로 체크
            POINT lemmingFoot = { static_cast<int64>(nextPos.x), static_cast<int64>(nextPos.y + footOffsetY) };

            if (IsInPoint(escape, lemmingFoot))
            {
                isFinished = true;
                //jobsprite = _spriteEscaper;
                //nextJob = JobFactory::instance().CreateEscaperJob();
                nextPos = jobActor->GetPosition();
            }
        }
        break;

    case WALKING_RIGHT_STATE:
        nextPos += Vector(1, 0) * deltaTime * walkSpeed; // → 수평 이동

        if (IsCollisionFront(nextPos)) {
            // Step Over 로직
            jobSprite->PlayLemmingAnimation(WALKING_LEFT);
            bool climbed = false;
            const int32 stepHeight = 3;

            for (int32 dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!IsCollisionWall(tryPos)) {
                    int32 fall = CollideFloor(tryPos, 2);
                    if (fall <= stepHeight) {
                        // 발이 바닥보다 1픽셀 위에 오도록 조정
                        nextPos = tryPos + Vector(0, fall - groundClearance);
                        climbed = true;
                        break;
                    }
                }
            }

            if (!climbed) {
                nextPos = jobActor->GetPosition();
                SetWalkingRight(false);
            }
        }
        else {
            int32 fallCheck = CollideFloor(nextPos, 2);
            if (fallCheck < 2) {
                nextPos.y += fallCheck - groundClearance; // 바닥 위 1픽셀
                fallSpeed = 0;
                state = isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;
            }
            else
            {
                if (state != FALLING_STATE) {  // 이미 낙하중이 아니면 전환
                    state = FALLING_STATE;
                    jobSprite->PlayLemmingAnimation(FALLING);
                }
                //nextJob = JobFactory::instance().CreateFallerJob();
            }

            // 레밍 탈출
            RECT escape = gameScene->GetDoor()->GetEscapeBounds();
            // 레밍 발 위치 기준으로 체크
            POINT lemmingFoot = { static_cast<int64>(nextPos.x), static_cast<int64>(nextPos.y + footOffsetY) };

            if (IsInPoint(escape, lemmingFoot))
            {
                isFinished = true;
                //jobsprite = _spriteEscaper;
                //nextJob = JobFactory::instance().CreateEscaperJob();
                nextPos = jobActor->GetPosition();
            }

        }
        break;

    case FALLING_STATE:
        nextPos.y += deltaTime * fallSpeed;

        int32 fallCheck = CollideFloor(nextPos, 2);
        if (fallCheck < 2) {
            // 아직 공중
            jobSprite->PlayLemmingAnimation(FALLING);
        }
        else {
            // 땅 도착
            nextPos.y += fallCheck;
            fallSpeed = 0;
            // 착지 후 걷기 상태 복귀
            if (isWalkingRight) state = WALKING_RIGHT_STATE;
            else state = WALKING_LEFT_STATE;
        }
        break;
    }

    jobActor->GetPosition() = nextPos;
    jobSprite->UpdateComponent(deltaTime);
}

string Walker::GetName()
{
	return "WALKER";
}