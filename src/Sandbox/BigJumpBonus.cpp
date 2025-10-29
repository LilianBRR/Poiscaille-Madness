#include "pch.h"
#include "BigJumpBonus.h"

void BigJumpBonus::Init()
{
	mBonusGeometry = new Capsule();
	mBonusGeometry->SetPosition({ mPosition.mX,  mPosition.mY,  mPosition.mZ });
	mBonusGeometry->SetScale(BONUS_SCALE);
	mBonusGeometry->SetRotation({ 0.f,0.f, BONUS_ROTATION_Z });
	mBonusGeometry->SetColor(BIG_JUMP_BONUS_COLOR );
	SetTag(BIG_JUMP_TAG);
	AddGeometry(mBonusGeometry);

	mCollider.mPositionCollider = mBonusGeometry->GetPosition();
	mCollider.mRadius = COLLIDER_RADIUS;
}

void BigJumpBonus::Update(float _deltaTime)
{
	SetPosition(mPosition.mX, mPosition.mY, mPosition.mZ - mSpeedMove * _deltaTime);
	Move(mPosition.mX, mPosition.mY, mPosition.mZ);
	mCurrentRotationY += mSpeedRotation * _deltaTime;
	mBonusGeometry->SetRotation({ 0.f, mCurrentRotationY, BONUS_ROTATION_Z });
	mCollider.mPositionCollider = mBonusGeometry->GetPosition();
}

void BigJumpBonus::Move(float _posX, float _posY, float _posZ)
{
	mBonusGeometry->SetPosition({ _posX, _posY, _posZ });
} 

bool BigJumpBonus::IsCollideCharacter(float _characterX, float _characterY ,float _characterZ)
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
