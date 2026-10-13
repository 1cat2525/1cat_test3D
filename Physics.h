#pragma once

#include "DxLib.h"

//ƒuƒƒbƒN‚Æ‚Ì“–‚½‚è”»’è
bool CheckBlockHit(
    VECTOR playerPos,
    VECTOR blockMin,
    VECTOR blockMax
);

//‘«ê”»’è
bool CheckLanding(
    VECTOR playerPos,
    VECTOR blockMin,
    VECTOR blockMax
);