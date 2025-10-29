#pragma once
#include <iostream>
#include "Tiles.h"
#include "Bonus.h"

struct Vector3_Character_Position
{
	float mX, mY, mZ;

	Vector3_Character_Position() : mX(0), mY(0), mZ(0) {}
	Vector3_Character_Position(float x, float y, float z) : mX(x), mY(y), mZ(z) {}
};

struct Vector3_Character_Scale
{
	float mX, mY, mZ;

	Vector3_Character_Scale() : mX(0), mY(0), mZ(0) {}
	Vector3_Character_Scale(float x, float y, float z) : mX(x), mY(y), mZ(z) {}
};

class Character
{
private:

	bool mIsDead;

	float mSpeed = SPEED;
	float mStep = STEP;
	float mPositionX = CHARACTER_POSITION_X;
	float mPositionY = CHARACTER_POSITION_Y;
	float mPositionZ = CHARACTER_POSITION_Z;

	float mScaleX = CHARACTER_WIDTH;
	float mScaleY = CHARACTER_HEIGHT;
	float mScaleZ = CHARACTER_DEPTH;

	float mTargetX = CHARACTER_POSITION_X;
	float mLateralSpeed = LANE_SWAPPING_SPEED;

	bool mIsAtFloor = true;

	float mVelocityY = 0.0f;
	bool mIsFastFalling = false;

	bool mIsSliding = false;
	float mSlideTimer = 0.0f;
	float mOriginalHeight = CHARACTER_HEIGHT;

	bool mIsFreeFalling = false;

	bool mIsBigJumpBoostActive = false;
	bool mIsBigJumpBoostActiveScene = true;
	float mCurrentTimeBoost = 0.f;
	float mBigJumpBoostDuration = 10.f;

	

	std::vector<Geometry*> mGeometries;
	Vector3_Character_Position mPosition;
	Vector3_Character_Scale mScale;

public : 

	Character() = default;
	~Character() = default;
	void Init();
	void Update(float _deltaTime);

	void SetPosition(float _x, float _y, float _z);
	Vector3_Character_Position GetPosition();

	void SetScale(float _x, float _y, float _z);
	Vector3_Character_Scale GetScale();

	void SetIsDead(bool _isDead);
	bool IsDead() const { return mIsDead; }

	void MoveUp(float _deltaTime);
	void MoveDown(float _deltaTime);
	void MoveLeft(float _deltaTime);
	void MoveRight(float _deltaTime);

	void StepLeft(float _deltaTime);
	void StepRight(float _deltaTime);

	void ResetTargetX() { mTargetX = CHARACTER_POSITION_X; }

	void Jump(float _deltaTime);
	void Slide(float _deltaTime);
	void FastFall(float _deltaTime);

	bool IsSliding() const { return mIsSliding; }
	void StopSliding();

	float GetSlideHeight() const;

	bool IsFreeFalling() const { return mIsFreeFalling; }
	void SetFreeFalling(bool freeFall) { mIsFreeFalling = freeFall; }

	void StartFreeFall();

	const float mMinFallY = MIN_FALL_Y;

	bool IsAirborne() const { return mPositionY > 2.0f; }
	bool IsAtFloor() const { return mPositionY <= 2.0f; }

	bool IsLeftLane() const { return mPositionX <= -STEP; }
	bool IsMiddleLane() const { return mPositionX == 0.0f; }
	bool IsRightLane() const { return mPositionX >= STEP; }

	void AddGeometry(Geometry* geometry);
	std::vector<Geometry*> GetGeometries() { return mGeometries; }

	bool IsCharacterAbove(std::vector<Tiles*>& _tiles);
	bool IsCollideBonus(Bonus* _bonus);

	void SetBigJumpBoostActive(bool _boostIsActive);

	bool GetIsBigJumpBoostActive() { return mIsBigJumpBoostActive; }
	bool GetIsBigJumpBoostActiveScene() { return mIsBigJumpBoostActiveScene; }

	void SetBigJumpBoostActiveScene(bool _isActive);
	float GetCurrentBigJumpBonusTime() { return mCurrentTimeBoost; }


};

