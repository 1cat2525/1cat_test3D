#include "camera.h"
#include <cmath>

void Camera::Update(VECTOR targetPos)
{
    int mouseX;
    int mouseY;

    GetMousePoint(&mouseX, &mouseY);

    int moveX = mouseX - 640;
    int moveY = mouseY - 360;

    angleY -= moveX * 0.01f;
    angleX += moveY * 0.01f;

    //毎フレーム中央へ戻す
    SetMousePoint(640, 360);

    float distance = 500.0f;

    VECTOR cameraPos;

    cameraPos.x =
        targetPos.x +
        sinf(angleY) * cosf(angleX) * distance;

    cameraPos.y =
        targetPos.y +
        sinf(angleX) * distance;

    cameraPos.z =
        targetPos.z -
        cosf(angleY) * cosf(angleX) * distance;

    SetCameraPositionAndTarget_UpVecY(
        cameraPos,
        VGet(
            targetPos.x,
            targetPos.y + 100.0f,
            targetPos.z
        )
    );

    //上下カメラがイキスギない設定（下を見るとき）
    if (angleX > 1.5f)
    {
        angleX = 1.5f;
    }
    //上下カメラがイキスギない設定（上を見るとき）
    if (angleX < -1.5f)
    {
        angleX = -1.5f;
    }
}
