#pragma once

#include "DxLib.h"
#include "Block.h"

class Player
{
public:

    //位置
    VECTOR pos;

    //モデル描画位置
    VECTOR modelPos = VGet(0, 0, 0);

    //もでる位置？
    void UpdateModelPosition();

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

    //モデル
    int modelHandle = -1;

    //モデルロード
    void LoadModel(const char* path);

    void Initialize();

    //向き関数
    void UpdateRotation();

    //ジャンプ周り
    void UpdateJump();

    void Draw();

    //Wキー前移動
    void MoveForward(
        float angleY,
        Block blocks[],
        int blockNum
    );

    //Sキー後ろ移動
    void MoveBack(
        float angleY,
        Block blocks[],
        int blockNum
    );

    //Aキー左移動
    void MoveLeft(
        float angleY,
        Block blocks[],
        int blockNum
    );

    //Dキー右移動
    void MoveRight(
        float angleY,
        Block blocks[],
        int blockNum
    );

    void CheckLanding(
        Block blocks[],
        int blockNum,
        float oldY
    );

    void CheckCeiling(
        Block blocks[],
        int blockNum,
        float oldY
    );
};