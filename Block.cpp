#include "Block.h"


void Block::Draw()
{
    DrawCube3D(
        minPos,
        maxPos,
        GetColor(0, 255, 0),
        GetColor(255, 255, 255),
        FALSE
    );
}

bool Block::CheckHit(VECTOR playerPos)
{
    //プレイヤーの足元
    float playerBottom = playerPos.y - 50;

    if (
        playerPos.x + 50 > minPos.x &&
        playerPos.x - 50 < maxPos.x &&
        playerPos.z + 50 > minPos.z &&
        playerPos.z - 50 < maxPos.z &&
        playerBottom < maxPos.z
        )
    {
        return true;
    }
    return false;
}

bool Block::CheckLanding(VECTOR playerPos, float oldY)
{
    float blockTop = maxPos.y;

    if (
        playerPos.x + 50 > minPos.x &&
        playerPos.x - 50 < maxPos.x &&
        playerPos.z + 50 > minPos.z &&
        playerPos.z - 50 < maxPos.z &&
        oldY - 50 > blockTop &&
        playerPos.y - 50 <= blockTop
        )
    {
        return true;
    }

    return false;
}