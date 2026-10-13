#include "DxLib.h"
#include "FpsControll.h"

//前フレームの時間
static int oldTime;

//初期化
void FpsControll_Initialize()
{
    oldTime = GetNowCount();
}

//60FPS待機
void FpsControll_Wait()
{
    while (GetNowCount() - oldTime < 16)
    {
    }

    oldTime = GetNowCount();
}