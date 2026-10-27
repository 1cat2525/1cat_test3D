#include "DxLib.h"
#include "camera.h"
#include "Physics.h"
#include "FpsControll.h"
#include "Block.h"
#include <cmath>

//Windowsアプリの開始地点
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //ウィンドウモードで起動
    //TRUE = フルスクリーンではなくウィンドウ表示
    //FALSE = フルスクリーン表示
    ChangeWindowMode(TRUE);

    // DXライブラリの初期化
    // 失敗したら終了
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetMouseDispFlag(FALSE);

    SetMousePoint(640, 360);

    FpsControll_Initialize();

    //キューブの中心座標
    VECTOR cubePos = VGet(0, 0, 0);

    //ジャンプの勢い
    float jumpPower = 0.0f;

    //ジャンプ中か判定する
    bool isJump = false;

    //ブロックに乗っているか判定
    bool onBlock = false;

    //Cameraクラスからカメラという実体を作っている
    Camera camera;

    //プレイヤーの向き
    float playerAngle = 0.0f;

    float targetAngle = 0.0f;
    
    //==========================================
    //配列の用意とか！
    //==========================================
    const int BLOCK_NUM = 4;

    Block blocks[BLOCK_NUM];

    //1個目
    blocks[0].minPos = VGet(100, -50, -50);
    blocks[0].maxPos = VGet(200, 50, 50);

    //2個目
    blocks[1].minPos = VGet(-200, 50, -50);
    blocks[1].maxPos = VGet(-100, 150, 50);

    //3個目
    blocks[2].minPos = VGet(-200, 150, 200);
    blocks[2].maxPos = VGet(-100, 250, 300);

    //4個目
    blocks[3].minPos = VGet(100, 250, 200);
    blocks[3].maxPos = VGet(200, 350, 300);

    //ライト計算を無効にする
    SetUseLighting(FALSE);

    //==========================================
    //メインループ
    //×ボタンが押されるまで繰り返す
    //==========================================
    while (ProcessMessage() == 0)
    {
        onBlock = false;

        //移動前の位置を保存
        VECTOR oldPos = cubePos;

        //前のフレームの描画を消す
        ClearDrawScreen();

        // --------------------------------------
        // 2D文字を表示
        // 3Dが映らなくてもDXLibが動いているか確認できる
        // --------------------------------------
        //DrawString(
        //    100,                      // X座標
        //    100,                      // Y座標
        //    "HELLO",                  // 表示する文字
        //    GetColor(255, 255, 255)   // 白色
        //);

        //--------------------------------------
        //カメラの設定
        //--------------------------------------
        camera.Update(cubePos);
       
        //--------------------------------------
        //3Dキューブを描画
        //--------------------------------------

        //DrawCube3D(

        //    // キューブの左下奥の座標
        //    VGet(-50, -50, -50),

        //    // キューブの右上手前の座標
        //    VGet(50, 50, 50),

        //    // 面の色
        //    GetColor(0, 255, 0),

        //    // 枠線の色
        //    GetColor(255, 255, 255),

        //    // FALSE = ワイヤーフレーム
        //    // TRUE  = 塗りつぶし
        //    TRUE
        //);

        //プレイヤー
        DrawCube3D(
            VGet(
                cubePos.x - 50,
                cubePos.y - 50,
                cubePos.z - 50
            ),

            VGet(
                cubePos.x + 50,
                cubePos.y + 50,
                cubePos.z + 50
            ),

            GetColor(0, 255, 0),
            GetColor(255, 255, 255),
            TRUE
        );
        
        //用意した配列のブロックの自動描写
        for (int i = 0; i < BLOCK_NUM; i++)
        {
            blocks[i].Draw();
        }


        //--------------------------------------
        //キー入力と移動
        //--------------------------------------
        //Wキーで前
        if (CheckHitKey(KEY_INPUT_W))
        {
            //X、Zの移動量
            float moveX =
                -sinf(camera.angleY) * 5.0f;

            float moveZ =
                cosf(camera.angleY) * 5.0f;

            playerAngle = camera.angleY;

            //移動先のx座標を保存
            float oldX = cubePos.x;

            cubePos.x += moveX;

            bool hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                cubePos.x = oldX;
            }

            //移動先のz座標を保存
            float oldZ = cubePos.z;

            cubePos.z += moveZ;

            hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                cubePos.z = oldZ;
            }
        }

        //Aキーで左
        if (CheckHitKey(KEY_INPUT_A))
        {
            //X、Zの移動量
            float moveX =
                -cosf(camera.angleY) * 5.0f;

            float moveZ =
                -sinf(camera.angleY) * 5.0f;

            playerAngle = camera.angleY - DX_PI_F / 2.0f;


            //移動先のx座標を保存
            float oldX = cubePos.x;

            cubePos.x += moveX;

            bool hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                cubePos.x = oldX;
            }

            //移動先のz座標を保存
            float oldZ = cubePos.z;

            cubePos.z += moveZ;

            hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                cubePos.z = oldZ;
            }
        } 

        //Sキーで後ろ
        if (CheckHitKey(KEY_INPUT_S))
        {
            //X、Zの移動量
            float moveX =
                sinf(camera.angleY) * 5.0f;

            float moveZ =
                -cosf(camera.angleY) * 5.0f;

            playerAngle = camera.angleY + DX_PI_F;

            //移動先のx座標を保存
            float oldX = cubePos.x;

            cubePos.x += moveX;

            bool hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                cubePos.x = oldX;
            }

            //移動先のz座標を保存
            float oldZ = cubePos.z;

            cubePos.z += moveZ;

            hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                cubePos.z = oldZ;
            }
        }

        //Dキーで右
        if (CheckHitKey(KEY_INPUT_D))
        {
            //X、Zの移動量
            float moveX =
                cosf(camera.angleY) * 5.0f;

            float moveZ =
                sinf(camera.angleY) * 5.0f;

            playerAngle = camera.angleY + DX_PI_F / 2.0f;

            //移動先のx座標を保存
            float oldX = cubePos.x;

            cubePos.x += moveX;

            bool hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                cubePos.x = oldX;
            }

            //移動先のz座標を保存
            float oldZ = cubePos.z;

            cubePos.z += moveZ;

            hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                cubePos.z = oldZ;
            }
        }

        //デバッグ
        DrawFormatString(
            10,
            130,
            GetColor(255, 255, 255),
            "onBlock=%d",
            onBlock
        );

        

        //ジャンプ中の処理　
        //y座標の保存
        float oldY = cubePos.y;
        //上向きの勢いで移動
        cubePos.y += jumpPower;

        //ブロックに乗っていない時だけ重力
        if (onBlock == false)
        {
            jumpPower -= 0.5f;
        }


        //地面に着地したら
        if (cubePos.y <= 0.0f)
        {
            cubePos.y = 0.0f;

            jumpPower = 0.0f;

            isJump = false;
        }

        //天井判定のこと
        for (int i = 0; i < BLOCK_NUM; i++)
        {
            if (blocks[i].CheckCeiling(
                cubePos,
                oldY
            ))
            {
                //ブロックの下面へ押し戻す
                cubePos.y = blocks[i].minPos.y - 50;

                //上昇停止
                jumpPower = 0.0f;
            }
        }

        //右キューブ当たり判定
        //右ブロックの上にいるか
        //if (
        //    cubePos.x + 50 > block.minPos.x &&
        //    cubePos.x - 50 < block.maxPos.x &&
        //    cubePos.z + 50 > block.minPos.z &&
        //    cubePos.z - 50 < block.maxPos.z
        //    )
        //{aaaaaaaa
        //    //上から落ちてきたか
        //    if (oldY - 50 > 50 &&
        //        cubePos.y - 50 <= 50)
        //    {
        //        cubePos.y = 100;

        //        jumpPower = 0.0f;

        //        isJump = false;

        //        onBlock = true;
        //    }
        //}

        //ブロックの上に立っている
        //iの上限かえればその分の当たり判定を管理できる
        for (int i = 0; i < BLOCK_NUM; i++)
        {
            if (blocks[i].CheckLanding(cubePos, oldY))
            {
                cubePos.y = blocks[i].maxPos.y + 50;

                jumpPower = 0.0f;

                onBlock = true;

                isJump = false;
            }
        }

        //ブロックの上に立っている判定。
        //ブロックの上に乗ってもすり抜けない
        for (int i = 0; i < BLOCK_NUM; i++)
        {
            if (
                cubePos.x + 50 > blocks[i].minPos.x &&
                cubePos.x - 50 < blocks[i].maxPos.x &&
                cubePos.z + 50 > blocks[i].minPos.z &&
                cubePos.z - 50 < blocks[i].maxPos.z &&
                cubePos.y <= blocks[i].maxPos.y + 50 &&
                cubePos.y >= blocks[i].maxPos.y + 45
                )
            {
                cubePos.y = blocks[i].maxPos.y + 50;

                jumpPower = 0.0f;

                onBlock = true;

                isJump = false;
            }
        }

        //ジャンプしていない時だけジャンプ開始
        if (CheckHitKey(KEY_INPUT_SPACE) && (cubePos.y == 0.0f || onBlock))
        {
            jumpPower = 13.5f;

            isJump = true;
        }

        //デバッグ、座標の表示とか
        DrawFormatString(
            10,
            30,
            GetColor(255, 255, 255),
            "X=%.1f Y=%.1f Z=%.1f",
            cubePos.x,
            cubePos.y,
            cubePos.z
        );

        /*
        DrawFormatString(
            10,
            50,
            GetColor(255, 255, 255),
            "oldY=%.1f",
            oldY
        );

        DrawFormatString(
            10,
            70,
            GetColor(255, 255, 255),
            "jump=%.1f",
            jumpPower
        );*/

        // --------------------------------------
        // 描画内容を画面に反映
        // --------------------------------------
        ScreenFlip();

        FpsControll_Wait();
    }

    //DXライブラリ終了
    DxLib_End();

    return 0;
}

