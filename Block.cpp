#include "Block.h"

void Block::Draw()
{
    DrawCube3D(
        minPos,
        maxPos,
        GetColor(0, 255, 0),
        GetColor(255, 255, 255),
        FALSE
    );
}