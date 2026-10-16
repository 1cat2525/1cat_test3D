#include "DxLib.h"
#include "camera.h"
#include "Physics.h"
#include "FpsControll.h"
#include "Block.h"

// Windowsアプリの開始地点
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ウィンドウモードで起動
    // TRUE = フルスクリーンではなくウィンドウ表示
    ChangeWindowMode(TRUE);

    // DXライブラリの初期化
    // 失敗したら終了
    if (DxLib_Init() == -1)
    {
        return -1;
    }

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

    //==========================================
    //配列の用意とか！
    //==========================================
    Block blocks[2];

    //１個目
    blocks[0].minPos = VGet(100, -50, -50);
    blocks[0].maxPos = VGet(200, 50, 50);

    //２個目
    blocks[1].minPos = VGet(-200, 50, -50);
    blocks[1].maxPos = VGet(-100, 150, 50);



    // ライト計算を無効にする
    SetUseLighting(FALSE);

    // ==========================================
    // メインループ
    // ×ボタンが押されるまで繰り返す
    // ==========================================
    while (ProcessMessage() == 0)
    {
        onBlock = false;

        //移動前の位置を保存
        VECTOR oldPos = cubePos;

        // 前のフレームの描画を消す
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

        // --------------------------------------
        // カメラの設定
        // --------------------------------------
        camera.Update(cubePos);
       
        // --------------------------------------
        // 3Dキューブを描画
        // --------------------------------------

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
        for (int i = 0; i < 2; i++)
        {
            blocks[i].Draw();
        }


        // --------------------------------------
        // キー入力と移動
        // --------------------------------------
        // Aキーで左
        if (CheckHitKey(KEY_INPUT_A))
        {
            //移動先のx座標を保存
            float oldX = cubePos.x;

            //右へ移動
            cubePos.x -= 5.0f;

            //ブロックに当たったら
            bool hit = false;

            for (int i = 0; i < 2; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                }
            }

            if (hit)
            {
                cubePos.x = oldX;
            }
        }

        // Dキーで右
        if (CheckHitKey(KEY_INPUT_D))
        {
            //移動先のx座標を保存
            float oldX = cubePos.x;

            //右へ移動
            cubePos.x += 5.0f;

            //ブロックに当たったら
            bool hit = false;

            for (int i = 0; i < 2; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                }
            }

            if (hit)
            {
                cubePos.x = oldX;
            }
        }

        // Wキーで前
        if (CheckHitKey(KEY_INPUT_W))
        {
            //移動先のx座標を保存
            float oldZ = cubePos.z;

            //前に移動
            cubePos.z += 5.0f;

            //ブロックに当たったら
            bool hit = false;

            for (int i = 0; i < 2; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                }
            }

            if (hit)
            {
                cubePos.z = oldZ;
            }
        }

        // Sキーで後ろ
        if (CheckHitKey(KEY_INPUT_S))
        {
            //移動先のx座標を保存
            float oldZ = cubePos.z;

            //手前に移動
            cubePos.z -= 5.0f;

            //ブロックに当たったら
            bool hit = false;

            for (int i = 0; i < 2; i++)
            {
                if (blocks[i].CheckHit(cubePos))
                {
                    hit = true;
                }
            }

            if (hit)
            {
                cubePos.z = oldZ;
            }
        }

        //ジャンプしていない時だけジャンプ開始
        if (CheckHitKey(KEY_INPUT_SPACE) && isJump == false)
        {
            jumpPower = 15.0f;

            isJump = true;
        }

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

        //右キューブ当たり判定
        //右ブロックの上にいるか
        //if (
        //    cubePos.x + 50 > block.minPos.x &&
        //    cubePos.x - 50 < block.maxPos.x &&
        //    cubePos.z + 50 > block.minPos.z &&
        //    cubePos.z - 50 < block.maxPos.z
        //    )
        //{
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
        for (int i = 0; i < 2; i++)
        {
            if (blocks[i].CheckLanding(cubePos))
            {
                cubePos.y = blocks[i].maxPos.y + 50;

                jumpPower = 0.0f;
                onBlock = true;
                isJump = false;
            }
        }

        //デバッグ、座標の表示とか
        /*DrawFormatString(
            10,
            30,
            GetColor(255, 255, 255),
            "X=%.1f Y=%.1f Z=%.1f",
            cubePos.x,
            cubePos.y,
            cubePos.z
        );
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

    // DXライブラリ終了
    DxLib_End();

    return 0;
}