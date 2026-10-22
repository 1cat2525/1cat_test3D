#pragma once
#include "DxLib.h"

class Camera
{
public:

    //カメラの回転角度(横？)
    float angleY = 0.0f;

    //上下回転
    float angleX = 0.0f;

    //前フレームのマウスX座標
    int oldMouseX = 0;

    //前フレームのマウスY座標
    int oldMouseY = 0;

    void Update(VECTOR targetPos);
};