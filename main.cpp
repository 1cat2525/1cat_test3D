#include "DxLib.h"
#include "camera.h"
#include "Physics.h"
#include "FpsControll.h"
#include "Block.h"
#include "Player.h"
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

    //キューブ、プレイヤーの中心座標
    Player player;

    //Playerの初期化
    player.Initialize();

    //Cameraクラスからカメラという実体を作っている
    Camera camera;

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

    //モデル
    player.LoadModel(
        "Assets/Player/T-Pose.mv1"
    );

    //==========================================
    //メインループ
    //×ボタンが押されるまで繰り返す
    //==========================================
    while (ProcessMessage() == 0)
    {
        player.onBlock = false;

        //移動前の位置を保存
        VECTOR oldPos = player.pos;

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
        camera.Update(player.pos);

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
        player.Draw();

        //モデル
        player.UpdateModelPosition();

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


            //移動先のx座標を保存
            float oldX = player.pos.x;

            player.pos.x += moveX;

            bool hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(player.pos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                player.pos.x = oldX;
            }

            //移動先のz座標を保存
            float oldZ = player.pos.z;

            player.pos.z += moveZ;

            hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(player.pos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                player.pos.z = oldZ;
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


            //移動先のx座標を保存
            float oldX = player.pos.x;

            player.pos.x += moveX;

            bool hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(player.pos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                player.pos.x = oldX;
            }

            //移動先のz座標を保存
            float oldZ = player.pos.z;

            player.pos.z += moveZ;

            hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(player.pos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                player.pos.z = oldZ;
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


            //移動先のx座標を保存
            float oldX = player.pos.x;

            player.pos.x += moveX;

            bool hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(player.pos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                player.pos.x = oldX;
            }

            //移動先のz座標を保存
            float oldZ = player.pos.z;

            player.pos.z += moveZ;

            hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(player.pos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                player.pos.z = oldZ;
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

            //移動先のx座標を保存
            float oldX = player.pos.x;

            player.pos.x += moveX;

            bool hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(player.pos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                player.pos.x = oldX;
            }

            //移動先のz座標を保存
            float oldZ = player.pos.z;

            player.pos.z += moveZ;

            hit = false;

            for (int i = 0; i < BLOCK_NUM; i++)
            {
                if (blocks[i].CheckHit(player.pos))
                {
                    hit = true;
                    break;
                }
            }

            if (hit)
            {
                player.pos.z = oldZ;
            }
        }

        //デバッグ
        DrawFormatString(
            10,
            130,
            GetColor(255, 255, 255),
            "player.onBlock=%d",
            player.onBlock
        );



        //11/10に追加
        float moveDirX =
            player.pos.x - oldPos.x;

        float moveDirZ =
            player.pos.z - oldPos.z;

        if (
            fabsf(moveDirX) > 0.01f ||
            fabsf(moveDirZ) > 0.01f
            )
        {
            player.targetAngle =
                atan2f(
                    moveDirX,
                    moveDirZ
                );
        }


        //ジャンプ中の処理　
        //y座標の保存
        float oldY = player.pos.y;

        //ジャンプの呼び出し
        player.UpdateJump();

        //天井判定のこと
        for (int i = 0; i < BLOCK_NUM; i++)
        {
            if (blocks[i].CheckCeiling(
                player.pos,
                oldY
            ))
            {
                //ブロックの下面へ押し戻す
                player.pos.y = blocks[i].minPos.y - 50;

                //上昇停止
                player.jumpPower = 0.0f;
            }
        }

        //右キューブ当たり判定
        //右ブロックの上にいるか
        //if (
        //    player.pos.x + 50 > block.minPos.x &&
        //    player.pos.x - 50 < block.maxPos.x &&
        //    player.pos.z + 50 > block.minPos.z &&
        //    player.pos.z - 50 < block.maxPos.z
        //    )
        //{aaaaaaaa
        //    //上から落ちてきたか
        //    if (oldY - 50 > 50 &&
        //        player.pos.y - 50 <= 50)
        //    {
        //        player.pos.y = 100;

        //        player.jumpPower = 0.0f;

        //        player.isJump = false;

        //        player.onBlock = true;
        //    }
        //}

        //ブロックの上に立っている
        //iの上限かえればその分の当たり判定を管理できる
        for (int i = 0; i < BLOCK_NUM; i++)
        {
            if (blocks[i].CheckLanding(player.pos, oldY))
            {
                player.pos.y = blocks[i].maxPos.y + 50;

                player.jumpPower = 0.0f;

                player.onBlock = true;

                player.isJump = false;
            }
        }

        //ブロックの上に立っている判定。
        //ブロックの上に乗ってもすり抜けない
        for (int i = 0; i < BLOCK_NUM; i++)
        {
            if (
                player.pos.x + 50 > blocks[i].minPos.x &&
                player.pos.x - 50 < blocks[i].maxPos.x &&
                player.pos.z + 50 > blocks[i].minPos.z &&
                player.pos.z - 50 < blocks[i].maxPos.z &&
                player.pos.y <= blocks[i].maxPos.y + 50 &&
                player.pos.y >= blocks[i].maxPos.y + 45
                )
            {
                player.pos.y = blocks[i].maxPos.y + 50;

                player.jumpPower = 0.0f;

                player.onBlock = true;

                player.isJump = false;
            }
        }

        //ジャンプしていない時だけジャンプ開始
        if (CheckHitKey(KEY_INPUT_SPACE) && (player.pos.y == 0.0f || player.onBlock))
        {
            player.jumpPower = 13.5f;

            player.isJump = true;
        }

        //体の向きかも
        player.UpdateRotation();




        //デバッグ、座標の表示とか
        DrawFormatString(
            10,
            30,
            GetColor(255, 255, 255),
            "X=%.1f Y=%.1f Z=%.1f",
            player.pos.x,
            player.pos.y,
            player.pos.z
        );

        DrawFormatString(
            10,
            190,
            GetColor(255, 255, 255),
            "player.playerAngle=%.2f",
            player.playerAngle
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
            player.jumpPower
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

