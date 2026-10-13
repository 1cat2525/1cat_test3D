#include "Physics.h"

//ƒuƒƒbƒN‚Æ‚Ì“–‚½‚è”»’è
bool CheckBlockHit(
    VECTOR playerPos,
    VECTOR blockMin,
    VECTOR blockMax
)
{
    if (
        playerPos.x + 50 > blockMin.x &&
        playerPos.x - 50 < blockMax.x &&
        playerPos.y + 50 > blockMin.y &&
        playerPos.y - 50 < blockMax.y &&
        playerPos.z + 50 > blockMin.z &&
        playerPos.z - 50 < blockMax.z
        )
    {
        return true;
    }

    return false;
}

//‘«ê”»’è
bool CheckLanding(
    VECTOR playerPos,
    VECTOR blockMin,
    VECTOR blockMax
)
{
    if (
        playerPos.x + 50 > blockMin.x &&
        playerPos.x - 50 < blockMax.x &&
        playerPos.z + 50 > blockMin.z &&
        playerPos.z - 50 < blockMax.z &&
        playerPos.y <= blockMax.y + 50 &&
        playerPos.y >= blockMax.y + 45
        )
    {
        return true;
    }

    return false;
}
