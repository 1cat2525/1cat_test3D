#include "Player.h"
#include <cmath>

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
            pos.y + 130,
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

//Wキー前移動
void Player::MoveForward(
    float angleY,
    Block blocks[],
    int blockNum
)
{
    float moveX =
        -sinf(angleY) * 5.0f;

    float moveZ =
        cosf(angleY) * 5.0f;

    float oldX = pos.x;

    pos.x += moveX;

    bool hit = false;

    for (int i = 0; i < blockNum; i++)
    {
        if (blocks[i].CheckHit(pos))
        {
            hit = true;
            break;
        }
    }

    if (hit)
    {
        pos.x = oldX;
    }

    float oldZ = pos.z;

    pos.z += moveZ;

    hit = false;

    for (int i = 0; i < blockNum; i++)
    {
        if (blocks[i].CheckHit(pos))
        {
            hit = true;
            break;
        }
    }

    if (hit)
    {
        pos.z = oldZ;
    }
}

//Sキー後ろ移動
void Player::MoveBack(
    float angleY,
    Block blocks[],
    int blockNum
)
{
    //X、Zの移動量
    float moveX =
        sinf(angleY) * 5.0f;

    float moveZ =
        -cosf(angleY) * 5.0f;

    //移動先のx座標を保存
    float oldX = pos.x;

    pos.x += moveX;

    bool hit = false;

    for (int i = 0; i < blockNum; i++)
    {
        if (blocks[i].CheckHit(pos))
        {
            hit = true;
            break;
        }
    }

    if (hit)
    {
        pos.x = oldX;
    }

    //移動先のz座標を保存
    float oldZ = pos.z;

    pos.z += moveZ;

    hit = false;

    for (int i = 0; i < blockNum; i++)
    {
        if (blocks[i].CheckHit(pos))
        {
            hit = true;
            break;
        }
    }

    if (hit)
    {
        pos.z = oldZ;
    }
}

//Aキー左移動
void Player::MoveLeft(
    float angleY,
    Block blocks[],
    int blockNum
)
{
    float moveX =
        -cosf(angleY) * 5.0f;

    float moveZ =
        -sinf(angleY) * 5.0f;

    //移動先のx座標を保存
    float oldX = pos.x;

    pos.x += moveX;

    bool hit = false;

    for (int i = 0; i < blockNum; i++)
    {
        if (blocks[i].CheckHit(pos))
        {
            hit = true;
            break;
        }
    }

    if (hit)
    {
        pos.x = oldX;
    }

    //移動先のz座標を保存
    float oldZ = pos.z;

    pos.z += moveZ;

    hit = false;

    for (int i = 0; i < blockNum; i++)
    {
        if (blocks[i].CheckHit(pos))
        {
            hit = true;
            break;
        }
    }

    if (hit)
    {
        pos.z = oldZ;
    }
}

//Dキー右移動
void Player::MoveRight(
    float angleY,
    Block blocks[],
    int blockNum
)
{
    float moveX =
        cosf(angleY) * 5.0f;

    float moveZ =
        sinf(angleY) * 5.0f;

    //移動先のx座標を保存
    float oldX = pos.x;

    pos.x += moveX;

    bool hit = false;

    for (int i = 0; i < blockNum; i++)
    {
        if (blocks[i].CheckHit(pos))
        {
            hit = true;
            break;
        }
    }

    if (hit)
    {
        pos.x = oldX;
    }

    //移動先のz座標を保存
    float oldZ = pos.z;

    pos.z += moveZ;

    hit = false;

    for (int i = 0; i < blockNum; i++)
    {
        if (blocks[i].CheckHit(pos))
        {
            hit = true;
            break;
        }
    }

    if (hit)
    {
        pos.z = oldZ;
    }
}

//ジャンプ
void Player::Jump()
{
    if (pos.y == 0.0f || onBlock)
    {
        jumpPower = 13.5f;

        isJump = true;
    }
}

//天井判定
void Player::CheckCeiling(
    Block blocks[],
    int blockNum,
    float oldY
)
{
    for (int i = 0; i < blockNum; i++)
    {
        if (
            blocks[i].CheckCeiling(
                pos,
                oldY
            )
            )
        {
            //ブロックの下面へ押し戻す
            pos.y =
                blocks[i].minPos.y - 50;

            //上昇停止
            jumpPower = 0.0f;
        }
    }
}

//ブロックの上に立ってる判定
void Player::CheckLanding(
    Block blocks[],
    int blockNum,
    float oldY
)
{
    for (int i = 0; i < blockNum; i++)
    {
        if (
            blocks[i].CheckLanding(
                pos,
                oldY
            )
            )
        {
            pos.y =
                blocks[i].maxPos.y + 50;

            jumpPower = 0.0f;

            onBlock = true;

            isJump = false;
        }
    }
}