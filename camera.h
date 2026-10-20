#pragma once
#include "DxLib.h"

class Camera
{
public:

    //カメラの回転角度
    float angleY = 0.0f;

    //前フレームのマウスX座標
    int oldMouseX = 0;

    void Update(VECTOR targetPos);
};