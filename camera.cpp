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
    angleY -= moveX * 0.01f;

    //今回のX位置を保存
    oldMouseX = mouseX;

    //マウス移動量(上下のほう)
    int moveY = mouseY - oldMouseY;

    //上下回転
    angleX += moveY * 0.01f;

    //今回のY位置を保存
    oldMouseY = mouseY;

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
