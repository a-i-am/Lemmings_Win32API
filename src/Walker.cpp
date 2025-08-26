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
    jobSprite = owner->CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
    jobSprite->SetAnimationClip(0, 10);

    state = WALKING_RIGHT_STATE;
}

void Walker::SetWalkingRight(bool value)
{
	isWalkingRight = value;

	if (isWalkingRight) {
		jobSprite->changeAnimation(WALKING_RIGHT);
		state = WALKING_RIGHT_STATE;
	}
	else {
		jobSprite->changeAnimation(WALKING_LEFT);
		state = WALKING_LEFT_STATE;
	}
}

void Walker::UpdateStateMachine(int deltaTime)
{
	GameScene* gameScene = Game::getGameScene();
	if (!gameScene || !gameScene->GetTerrain()) return;

    Vector nextPos = lemming->GetPosition();
	int32 fall;

    switch (state)
    {
    case WALKING_LEFT_STATE:
        nextPos += Vector(-1, 0) * deltaTime * walkSpeed; // ← 수평 이동

        if (IsCollisionFront(nextPos)) {
            // Step Over 로직
            bool climbed = false;
            const int stepHeight = 3; // 최대 3픽셀까지만 올라감

            for (int dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!IsCollisionWall(tryPos)) {
                    int fall = CollideFloor(tryPos, 2);
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
                nextPos = lemming->GetPosition();
                SetWalkingRight(true);
            }
        }
        else {
            int fallCheck = CollideFloor(nextPos, 2);
            if (fallCheck > 0) {
                nextPos.y += fallCheck - groundClearance; // 바닥 위 1픽셀
                fallSpeed = 0;
                state = isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;

                RECT escape = gameScene->GetDoor()->GetEscapeBounds();

                // 레밍 발 위치 기준으로 체크
                POINT lemmingFoot = { static_cast<LONG>(nextPos.x), static_cast<LONG>(nextPos.y + footOffsetY) };

                if (IsInPoint(escape, lemmingFoot))
                {
                    //isFinished = true;
                    //_sprite = _spriteEscaper;
                    //nextJob = JobFactory::instance().createEscaperJob();
                    nextPos = lemming->GetPosition();
                }
            }
            else
            {
                //isFinished = true;
                //nextJob = JobFactory::instance().createFallerJob();
            }
        }
        break;

    case WALKING_RIGHT_STATE:
        nextPos += Vector(1, 0) * deltaTime * walkSpeed; // → 수평 이동

        if (IsCollisionFront(nextPos)) {
            // Step Over 로직
            bool climbed = false;
            const int stepHeight = 3;

            for (int dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!IsCollisionWall(tryPos)) {
                    int fall = CollideFloor(tryPos, 2);
                    if (fall <= stepHeight) {
                        // 발이 바닥보다 1픽셀 위에 오도록 조정
                        nextPos = tryPos + Vector(0, fall - groundClearance);
                        climbed = true;
                        break;
                    }
                }
            }

            if (!climbed) {
                nextPos = lemming->GetPosition();
                SetWalkingRight(false);
            }
        }
        else {
            int fallCheck = CollideFloor(nextPos, 2);
            if (fallCheck > 0) {
                nextPos.y += fallCheck - groundClearance; // 바닥 위 1픽셀
                fallSpeed = 0;
                state = isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;

                RECT escape = gameScene->GetDoor()->GetEscapeBounds();

                // 레밍 발 위치 기준으로 체크
                POINT lemmingFoot = { static_cast<LONG>(nextPos.x), static_cast<LONG>(nextPos.y + footOffsetY) };

                if (IsInPoint(escape, lemmingFoot))
                {
                    //isFinished = true;
                    //_sprite = _spriteEscaper;
                    //nextJob = JobFactory::instance().CreateEscaperJob();
                    nextPos = lemming->GetPosition();
                }
            }
            else
            {
                //isFinished = true;
                //nextJob = JobFactory::instance().CreateFallerJob();
            }
        }
        break;

    case FALLING:
        nextPos.y += 1 * fallSpeed;

        int fallCheck = CollideFloor(nextPos, 2);
        if (fallCheck == 0) {
            // 아직 공중
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

    lemming->GetPosition() = nextPos;
    jobSprite->UpdateComponent(deltaTime);
}

string Walker::GetName()
{
	return "WALKER";
}