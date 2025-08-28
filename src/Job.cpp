#include "pch.h"
#include "Job.h"
#include "Game.h"
#include "GameScene.h"

bool Job::IsCollisionWall(Vector nextPos)
{
    GameScene* gameScene = Game::getGameScene();
    if (!gameScene || !gameScene->GetTerrain()) return 0;

    Vector headOffset(7, 15);
    Vector checkPos = nextPos + (isWalkingRight ? headOffset : Vector(-headOffset.x, headOffset.y));
    debugFrontPoints.clear();
    debugFrontPoints.push_back(checkPos);

    return gameScene->GetTerrain()->isSolid((int32)checkPos.x, (int32)checkPos.y) != 0;
}

bool Job::IsCollisionFront(Vector nextPos)
{
    GameScene* gameScene = Game::getGameScene();
    if (!gameScene || !gameScene->GetTerrain()) return 0;

    debugFrontPoints.clear();

    Vector offsets[2] = {
        Vector(7, 5),   // �Ӹ� (����׿�)
        Vector(7, 23),  // ���� (�� ��ġ ����)
    };

    for (auto& off : offsets)
    {
        Vector checkPos = nextPos + (isWalkingRight ? off : Vector(-off.x, off.y));
        debugFrontPoints.push_back(checkPos);

        if (off.y != 23) // �Ӹ� ����
            continue;

        // ����/�� ��ó�� �ٴ� �浹 �뵵�� �Ǵ�
        if (gameScene->GetTerrain()->isSolid((int32)checkPos.x, (int32)checkPos.y) != 0)
            return true;
    }

    return false;
}

int32 Job::CollideFloor(Vector nextPos, int32 maxFall)
{
    GameScene* gameScene = Game::getGameScene();
    if (!gameScene || !gameScene->GetTerrain()) return 0;

    debugFloorPoints.clear();

    Vector foot1(-2, footOffsetY);
    Vector foot2(2,  footOffsetY);

    for (int32 dy = 0; dy < maxFall; ++dy) {
        Vector c1 = nextPos + foot1 + Vector(0, dy);
        Vector c2 = nextPos + foot2 + Vector(0, dy);

        debugFloorPoints.push_back(c1);
        debugFloorPoints.push_back(c2);

        if (gameScene->GetTerrain()->isSolid((int32)c1.x, (int32)c1.y) != 0 ||
            gameScene->GetTerrain()->isSolid((int32)c2.x, (int32)c2.y) != 0) {
            return dy; // �� ã��
        }
    }

    return maxFall; // �ٴ� ����
}
