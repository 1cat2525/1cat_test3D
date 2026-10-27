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
    //プレイヤーの頭と下
    float playerTop = playerPos.y + 50;
    float playerBottom = playerPos.y - 50;

    if (
        playerPos.x + 50 > minPos.x &&
        playerPos.x - 50 < maxPos.x &&
        playerPos.z + 50 > minPos.z &&
        playerPos.z - 50 < maxPos.z &&
        playerTop > minPos.y &&
        playerBottom < maxPos.y
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

bool Block::CheckCeiling(VECTOR playerPos,float oldY)
{
    float blockBottom = minPos.y;


    if (
        playerPos.x + 49.9 > minPos.x &&
        playerPos.x - 49.9 < maxPos.x &&
        playerPos.z + 49.9 > minPos.z &&
        playerPos.z - 49.9 < maxPos.z &&
        oldY + 49.9 < blockBottom &&
        playerPos.y + 49.9 >= blockBottom
        )
    {
        return true;
    }

    //デバッグよう
    DrawString(
        10,
        150,
        "CEILING HIT",
        GetColor(255, 255, 0)
    );

    return false;
}