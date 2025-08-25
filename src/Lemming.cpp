#include "pch.h"
#include "Lemming.h"
#include "ResourceManager.h"
#include "Game.h"
#include "GameScene.h"

Lemming::Lemming(Vector pos) : Super(pos)
{
    _spriteMoveRight = CreateSpriteComponent("lemming", 1.0f, 16 * 3.f, 14 * 3.f);
    _spriteMoveRight->setAnimationClip(0, 10);

    _spriteMoveLeft = CreateSpriteComponent("rotated_lemming", 1.0f, 16 * 3.f, 14 * 3.f);
    _spriteMoveLeft->setAnimationClip(6, 15);

    _spriteMoveRight->getTexture()->GenerateCollisionData(256, 224);
    _spriteMoveLeft->getTexture()->GenerateCollisionData(256, 224);

    setWalkingRight(true);
    _sprite = _spriteMoveRight;

    state = WALKING_RIGHT_STATE;
    _fallSpeed = 0;
}

enum WalkerAnims
{
    WALKING_LEFT, WALKING_RIGHT, FALLING
};

void Lemming::setWalkingRight(bool value)
{
    _isWalkingRight = value;

    if (_isWalkingRight) {
        state = WALKING_RIGHT_STATE;
        _sprite = _spriteMoveRight;
    }
    else {
        state = WALKING_LEFT_STATE;
        _sprite = _spriteMoveLeft;
    }
}

void Lemming::update(float deltaTime)
{
    GameScene* gameScene = Game::getGameScene();
    if (!gameScene || !gameScene->GetTerrain()) return;

    Vector nextPos = _pos;

    switch (state)
    {
    case WALKING_LEFT_STATE:
        nextPos += Vector(-1, 0) * deltaTime * _speed; // ← 수평 이동

        if (isSolid(nextPos)) {
            // Step Over 로직
            bool climbed = false;
            const int stepHeight = 3; // 최대 3픽셀까지만 올라감

            for (int dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!isSolidWall(tryPos)) {
                    int fall = isSolidFloor(tryPos, 2);
                    if (fall <= stepHeight) {
                        // 발이 바닥보다 1픽셀 위에 오도록 조정
                        nextPos = tryPos + Vector(0, fall - _groundClearance);
                        climbed = true;
                        break;
                    }
                }
            }

            if (!climbed) {
                // 못 올라감 → 방향 전환
                nextPos = _pos;
                setWalkingRight(true);
            }
        }
        else {
            int fallCheck = isSolidFloor(nextPos, 2);
            if (fallCheck > 0) {
                nextPos.y += fallCheck - _groundClearance; // 바닥 위 1픽셀
                _fallSpeed = 0;
                state = _isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;
            }
        }
        break;

    case WALKING_RIGHT_STATE:
        nextPos += Vector(1, 0) * deltaTime * _speed; // → 수평 이동

        if (isSolid(nextPos)) {
            // Step Over 로직
            bool climbed = false;
            const int stepHeight = 3;

            for (int dy = 1; dy <= stepHeight; ++dy) {
                Vector tryPos = nextPos - Vector(0, dy);
                if (!isSolidWall(tryPos)) {
                    int fall = isSolidFloor(tryPos, 2);
                    if (fall <= stepHeight) {
                        // 발이 바닥보다 1픽셀 위에 오도록 조정
                        nextPos = tryPos + Vector(0, fall - _groundClearance);
                        climbed = true;
                        break;
                    }
                }
            }

            if (!climbed) {
                nextPos = _pos;
                setWalkingRight(false);
            }
        }
        else {
            int fallCheck = isSolidFloor(nextPos, 2);
            if (fallCheck > 0) {
                nextPos.y += fallCheck - _groundClearance; // 바닥 위 1픽셀
                _fallSpeed = 0;
                state = _isWalkingRight ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;
            }
        }
        break;

    case FALLING:
        nextPos.y += 1 * _fallSpeed;

        int fallCheck = isSolidFloor(nextPos, 2);
        if (fallCheck == 0) {
            // 아직 공중
        }
        else {
            // 땅 도착
            nextPos.y += fallCheck;
            _fallSpeed = 0;
            // 착지 후 걷기 상태 복귀
            if (_isWalkingRight) state = WALKING_RIGHT_STATE;
            else state = WALKING_LEFT_STATE;
        }
        break;
    }

    _pos = nextPos;
    _sprite->updateComponent(deltaTime);
}


// 벽 충돌 검사 (머리 점만)
bool Lemming::isSolidWall(Vector nextPos)
{
    GameScene* gameScene = Game::getGameScene();
    if (!gameScene || !gameScene->GetTerrain()) return false;

    Vector headOffset(7, 15);
    Vector checkPos = nextPos + (_isWalkingRight ? headOffset : Vector(-headOffset.x, headOffset.y));
    _debugFrontPoints.clear();
    _debugFrontPoints.push_back(checkPos);

    return gameScene->GetTerrain()->isSolid((int)checkPos.x, (int)checkPos.y) != 0;
}

// 바닥 / 발 근처 걷기용 충돌 체크
bool Lemming::isSolid(Vector nextPos)
{
    GameScene* gameScene = Game::getGameScene();
    if (!gameScene || !gameScene->GetTerrain()) return false;

    _debugFrontPoints.clear();

    Vector offsets[2] = {
        Vector(7, 5),   // 머리 (디버그용)
        Vector(7, 22),  // 몸통 (발 위치 포함)
    };

    for (auto& off : offsets)
    {
        Vector checkPos = nextPos + (_isWalkingRight ? off : Vector(-off.x, off.y));
        _debugFrontPoints.push_back(checkPos);

        if (off.y != 22) // 머리 제외
            continue;

        // 몸통/발 근처만 바닥 충돌 용도로 판단
        if (gameScene->GetTerrain()->isSolid((int)checkPos.x, (int)checkPos.y) != 0)
            return true;
    }

    return false;
}

int Lemming::isSolidFloor(Vector nextPos, int maxFall)
{
    GameScene* gameScene = Game::getGameScene();
    if (!gameScene || !gameScene->GetTerrain()) return 0;

    _debugFloorPoints.clear();

    Vector foot1(-2, _footOffsetY);
    Vector foot2(2, _footOffsetY);

    for (int dy = 0; dy < maxFall; ++dy) {
        Vector c1 = nextPos + foot1 + Vector(0, dy);
        Vector c2 = nextPos + foot2 + Vector(0, dy);

        _debugFloorPoints.push_back(c1);
        _debugFloorPoints.push_back(c2);

        if (gameScene->GetTerrain()->isSolid((int)c1.x, (int)c1.y) != 0 ||
            gameScene->GetTerrain()->isSolid((int)c2.x, (int)c2.y) != 0) {
            return dy; // 땅 찾음
        }
    }

    return maxFall; // 바닥 없음
}

void Lemming::Render(HDC hdc)
{
    if (_sprite)
    {
        _sprite->renderComponent(hdc, _pos);

        GameScene* gameScene = Game::getGameScene();
        if (!gameScene || !gameScene->GetTerrain()) return;
        Terrain* terrain = gameScene->GetTerrain();

        HBRUSH frontBrush = CreateSolidBrush(RGB(0, 255, 0));
        for (auto& p : _debugFrontPoints) {
            Vector local = terrain->worldToLocal(p.x, p.y);
            RECT rc = { (int)local.x, (int)local.y, (int)local.x + 2, (int)local.y + 2 };
            FillRect(hdc, &rc, frontBrush);
        }
        DeleteObject(frontBrush);

        HBRUSH floorBrush = CreateSolidBrush(RGB(255, 0, 0));
        for (auto& p : _debugFloorPoints) {
            Vector local = terrain->worldToLocal(p.x, p.y);
            RECT rc = { (int)local.x, (int)local.y, (int)local.x + 2, (int)local.y + 2 };
            FillRect(hdc, &rc, floorBrush);
        }
        DeleteObject(floorBrush);
    }
}

bool Lemming::outOfMap()
{
    Vector pos = getPosition();
    return (pos.x < 0 || pos.y < 0 || pos.x > GWinSizeX || pos.y > GWinSizeY);
}
