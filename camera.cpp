#include "camera.h"
#include <cmath>

void Camera::Update(VECTOR targetPos)
{
    int mouseX;
    int mouseY;

    GetMousePoint(&mouseX, &mouseY);

    //マウス移動量
    int moveX = mouseX - oldMouseX;

    //横回転
    angleY += moveX * 0.01f;

    //今回の位置を保存
    oldMouseX = mouseX;

    /*if (CheckHitKey(KEY_INPUT_Q))
    {
        angleY -= 0.05f;
    }

    if (CheckHitKey(KEY_INPUT_E))
    {
        angleY += 0.05f;
    }*/

    float distance = 500.0f;

    VECTOR cameraPos;

    cameraPos.x =
        targetPos.x + sinf(angleY) * distance;

    cameraPos.y =
        targetPos.y + 300.0f;

    cameraPos.z =
        targetPos.z - cosf(angleY) * distance;

    SetCameraPositionAndTarget_UpVecY(
        cameraPos,
        targetPos
    );
}
