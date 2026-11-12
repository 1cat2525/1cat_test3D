#include "Player.h"

void Player::Initialize()
{
    pos = VGet(0, 0, 0);
}

//キューブの位置
void Player::Draw()
{
    DrawCube3D(
        //下
        VGet(
            pos.x - 50,
            pos.y - 50,
            pos.z - 50
        ),
        //上
        VGet(
            pos.x + 50,
            pos.y + 50,
            pos.z + 50
        ),
        GetColor(255, 255, 255),
        GetColor(255, 255, 255),
        FALSE
    );

    //ここから下モデル
    MV1SetPosition(
        modelHandle,
        modelPos
    );

    MV1SetRotationXYZ(
        modelHandle,
        VGet(
            0,
            playerAngle + DX_PI_F,//DX_PI_Fは180°回すという意味
            0
        )
    );

    MV1DrawModel(
        modelHandle
    );
}

//モデル（プレイヤーの位置）
void Player::UpdateModelPosition()
{
    modelPos =
        VGet(
            pos.x,
            pos.y - 50,
            pos.z
        );
}

//モデル
void Player::LoadModel(const char* path)
{
    modelHandle = MV1LoadModel(path);
}

//向きの調整のやつ
void Player::UpdateRotation()
{
    float diff =
        targetAngle -
        playerAngle;

    while (diff > DX_PI_F)
    {
        diff -= DX_TWO_PI_F;
    }

    while (diff < -DX_PI_F)
    {
        diff += DX_TWO_PI_F;
    }

    playerAngle += diff * 0.2f;
}

//ジャンプ周り
void Player::UpdateJump()
{
    //上向きの勢いで移動
    pos.y += jumpPower;

    //重力
    if (onBlock == false)
    {
        jumpPower -= 0.5f;
    }

    //地面
    if (pos.y <= 0.0f)
    {
        pos.y = 0.0f;

        jumpPower = 0.0f;

        isJump = false;
    }
}