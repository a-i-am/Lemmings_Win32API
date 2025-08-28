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
        nextPos += Vector(-1, 0) * deltaTime * walkSpeed; // �� ���� �̵�

        if (IsCollisionFront(nextPos)) {
            jobSprite->PlayLemmingAnimation(WALKING_RIGHT);
            // Step Over ����
            bool climbed = false;
            const int32 stepHeight = 3; // �ִ� 3�ȼ������� �ö�

            for (int32 dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!IsCollisionWall(tryPos)) {
                    int32 fall = CollideFloor(tryPos, 2);
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
                nextPos = jobActor->GetPosition();
                SetWalkingRight(true);
            }
        }
        else {
            int32 fallCheck = CollideFloor(nextPos, 2);
            if (fallCheck < 2) {
                nextPos.y += fallCheck - groundClearance; // �ٴ� �� 1�ȼ�
                fallSpeed = 0;
                state = isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;
            }
            else
            {
                if (state != FALLING_STATE) {  // �̹� �������� �ƴϸ� ��ȯ
                    state = FALLING_STATE;
                    jobSprite->PlayLemmingAnimation(FALLING);
                }
                //nextJob = JobFactory::instance().CreateFallerJob();
            }

            // ���� Ż��
            RECT escape = gameScene->GetDoor()->GetEscapeBounds();
            // ���� �� ��ġ �������� üũ
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
        nextPos += Vector(1, 0) * deltaTime * walkSpeed; // �� ���� �̵�

        if (IsCollisionFront(nextPos)) {
            // Step Over ����
            jobSprite->PlayLemmingAnimation(WALKING_LEFT);
            bool climbed = false;
            const int32 stepHeight = 3;

            for (int32 dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!IsCollisionWall(tryPos)) {
                    int32 fall = CollideFloor(tryPos, 2);
                    if (fall <= stepHeight) {
                        // ���� �ٴں��� 1�ȼ� ���� ������ ����
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
                nextPos.y += fallCheck - groundClearance; // �ٴ� �� 1�ȼ�
                fallSpeed = 0;
                state = isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;
            }
            else
            {
                if (state != FALLING_STATE) {  // �̹� �������� �ƴϸ� ��ȯ
                    state = FALLING_STATE;
                    jobSprite->PlayLemmingAnimation(FALLING);
                }
                //nextJob = JobFactory::instance().CreateFallerJob();
            }

            // ���� Ż��
            RECT escape = gameScene->GetDoor()->GetEscapeBounds();
            // ���� �� ��ġ �������� üũ
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
            // ���� ����
            jobSprite->PlayLemmingAnimation(FALLING);
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

    jobActor->GetPosition() = nextPos;
    jobSprite->UpdateComponent(deltaTime);
}

string Walker::GetName()
{
	return "WALKER";
}