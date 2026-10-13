#include "camera.h"

void Camera::Update(VECTOR targetPos)
{
	SetCameraPositionAndTarget_UpVecY(
		VGet(
			targetPos.x,
			targetPos.y + 300.0f,
			targetPos.z - 500.0f
		),
		targetPos
	);
}