#include "Player.h"

void Player::Initialize()
{
    pos = VGet(0, 0, 0);
}

void Player::Draw()
{
    DrawCube3D(
        VGet(
            pos.x - 50,
            pos.y - 50,
            pos.z - 50
        ),
        VGet(
            pos.x + 50,
            pos.y + 50,
            pos.z + 50
        ),
        GetColor(255, 255, 255),
        GetColor(255, 255, 255),
        FALSE
    );
}
