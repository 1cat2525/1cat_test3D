#pragma once

#include "DxLib.h"

class Block
{
public:

    //左下奥
    VECTOR minPos;

    //右上手前
    VECTOR maxPos;

    //描画
    void Draw();

    bool CheckHit(VECTOR playerPos);

    bool CheckLanding
    (
        VECTOR playerPos,
        float oldY
    );
};