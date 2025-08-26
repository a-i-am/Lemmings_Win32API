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
        nextPos += Vector(-1, 0) * deltaTime * walkSpeed; // �� ���� �̵�

        if (IsCollisionFront(nextPos)) {
            // Step Over ����
            bool climbed = false;
            const int stepHeight = 3; // �ִ� 3�ȼ������� �ö�

            for (int dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!IsCollisionWall(tryPos)) {
                    int fall = CollideFloor(tryPos, 2);
                    if (fall <= stepHeight) {
                        // ���� �ٴں��� 1�ȼ� ���� ������ ����
                        nextPos = tryPos + Vector(0, fall - groundClearance);
                        climbed = true;
                        break;
                    }
                }
            }

            if (!climbed) {
                // �� �ö� �� ���� ��ȯ
                nextPos = lemming->GetPosition();
                SetWalkingRight(true);
            }
        }
        else {
            int fallCheck = CollideFloor(nextPos, 2);
            if (fallCheck > 0) {
                nextPos.y += fallCheck - groundClearance; // �ٴ� �� 1�ȼ�
                fallSpeed = 0;
                state = isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;

                RECT escape = gameScene->GetDoor()->GetEscapeBounds();

                // ���� �� ��ġ �������� üũ
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
        nextPos += Vector(1, 0) * deltaTime * walkSpeed; // �� ���� �̵�

        if (IsCollisionFront(nextPos)) {
            // Step Over ����
            bool climbed = false;
            const int stepHeight = 3;

            for (int dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!IsCollisionWall(tryPos)) {
                    int fall = CollideFloor(tryPos, 2);
                    if (fall <= stepHeight) {
                        // ���� �ٴں��� 1�ȼ� ���� ������ ����
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
                nextPos.y += fallCheck - groundClearance; // �ٴ� �� 1�ȼ�
                fallSpeed = 0;
                state = isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;

                RECT escape = gameScene->GetDoor()->GetEscapeBounds();

                // ���� �� ��ġ �������� üũ
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
            // ���� ����
        }
        else {
            // �� ����
            nextPos.y += fallCheck;
            fallSpeed = 0;
            // ���� �� �ȱ� ���� ����
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