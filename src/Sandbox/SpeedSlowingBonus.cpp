#include "pch.h"
#include "SpeedSlowingBonus.h"

void SpeedSlowingBonus::Init()
{
	SetPosition(BONUS_POSITION_X, BONUS_POSITION_Y, BONUS_POSITION_Z);
	mBonusGeometry = new Capsule();
	mBonusGeometry->SetPosition({ BONUS_POSITION_X, BONUS_POSITION_Y, BONUS_POSITION_Z });
	mBonusGeometry->SetScale(BONUS_SCALE);
	mBonusGeometry->SetRotation({ 0.f,0.f, BONUS_ROTATION_Z });
	mBonusGeometry->SetColor(SPEED_SLOWING_BONUS_COLOR);
	SetTag(SPEED_SLOWING_TAG);
	AddGeometry(mBonusGeometry);

	mCollider.mPositionCollider = mBonusGeometry->GetPosition();
	mCollider.mRadius = COLLIDER_RADIUS;
}

void SpeedSlowingBonus::Update(float _deltaTime)
{
	SetPosition(BONUS_POSITION_X, BONUS_POSITION_Y, mPosition.mZ - mSpeedMove * _deltaTime);
	Move(mPosition.mX, mPosition.mY, mPosition.mZ);
	mCurrentRotationY += mSpeedRotation * _deltaTime;
	mBonusGeometry->SetRotation({ 0.f, mCurrentRotationY, BONUS_ROTATION_Z });
	mCollider.mPositionCollider = mBonusGeometry->GetPosition();
}

void SpeedSlowingBonus::Move(float _posX, float _posY, float _posZ)
{
	mBonusGeometry->SetPosition({ _posX, _posY, _posZ });
}

bool SpeedSlowingBonus::IsCollideCharacter(float _characterX, float _characterY, float _characterZ)
{
	float distX = _characterX - mCollider.mPositionCollider.mX;
	float distY = _characterY - mCollider.mPositionCollider.mY;
	float distZ = _characterZ - mCollider.mPositionCollider.mZ;

	float distance = std::sqrt(distX * distX + distY * distY + distZ * distZ);

	if (distance < (1.f + mCollider.mRadius))
	{
		return true;
	}

	return false;
}


