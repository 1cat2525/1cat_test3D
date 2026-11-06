#pragma once

#include "DxLib.h"

class Player
{
public:

    //位置
    VECTOR pos;

    //ジャンプ
    float jumpPower = 0.0f;

    //地面にいるか
    bool onBlock = false;

    //ジャンプ中
    bool isJump = false;

    //向き
    float playerAngle = 0.0f;

    //向きたい方向
    float targetAngle = 0.0f;

    void Initialize();

    void Draw();
};