#include "pch.h"
#include "Character.h"


void Character::Init()
{
	SetPosition(CHARACTER_POSITION_X, CHARACTER_POSITION_Y, CHARACTER_POSITION_Z);

	Sphere* characterGeo = new Sphere();
	characterGeo->SetColor(CHARACTER_COLOR);
	characterGeo->SetScale(CHARACTER_SIZE);
	characterGeo->SetPosition(CHARACTER_POSITION);
	AddGeometry(characterGeo);

	mIsDead = false;
}

void Character::Update(float _deltaTime)
{
	if (mPositionY <= DEATH_HEIGHT)
	{
		SetIsDead(true);
	}

	mVelocityY -= GRAVITY * _deltaTime;
	mPositionY += mVelocityY * _deltaTime;

	if (!IsDead())
	{
		if (IsAtFloor() && !IsFreeFalling())
		{
			mPositionY = 2.0f;
			mVelocityY = 0.0f;
			mIsFastFalling = false;
		}

		float distance = mTargetX - mPositionX;

		if (fabs(distance) > 0.001f)
		{
			float t = fabs(distance) / STEP;
			if (t > 1.0f) t = 1.0f;

			float smooth = t * t * (3 - 2 * t);
			float move = (mLateralSpeed * smooth) * _deltaTime;

			if (fabs(move) < MIN_MOVE_THRESHOLD)
				move = (move >= 0 ? 1 : -1) * MIN_MOVE_THRESHOLD;

			if (distance > 0)
				mPositionX += move;
			else
				mPositionX -= move;

			if ((distance > 0 && mPositionX > mTargetX) ||
				(distance < 0 && mPositionX < mTargetX))
			{
				mPositionX = mTargetX;
			}
		}

		if (IsSliding())
		{
			mSlideTimer += _deltaTime;
			float halfHeight = CHARACTER_HEIGHT * SLIDE_SCALE_Y;
			float stretchZ = CHARACTER_DEPTH * SLIDE_STRETCH_Z;

			if (mSlideTimer <= SLIDE_DURATION / 2.0f)
			{
				float t = mSlideTimer / (SLIDE_DURATION / 2.0f);
				mScaleY = CHARACTER_HEIGHT + t * (halfHeight - CHARACTER_HEIGHT);
				mScaleZ = CHARACTER_DEPTH + t * (stretchZ - CHARACTER_DEPTH);
			}
			else if (mSlideTimer <= SLIDE_DURATION)
			{
				float t = (mSlideTimer - SLIDE_DURATION / 2.0f) / (SLIDE_DURATION / 2.0f);
				mScaleY = halfHeight + t * (CHARACTER_HEIGHT - halfHeight);
				mScaleZ = stretchZ + t * (CHARACTER_DEPTH - stretchZ);
			}
			else
			{
				StopSliding();
			}

			if (!IsAtFloor() || fabs(mTargetX - mPositionX) > 0.001f)
				StopSliding();
		}
		else
		{
			mScaleY = CHARACTER_HEIGHT;
			mScaleZ = CHARACTER_DEPTH;
		}

	}

	if (mIsBigJumpBoostActive)
	{
		mCurrentTimeBoost += _deltaTime;
		if (mCurrentTimeBoost >= mBigJumpBoostDuration)
		{
			SetBigJumpBoostActive(false);
			mIsBigJumpBoostActiveScene = false;
			mCurrentTimeBoost = 0.f;
		}
	}


	SetScale(CHARACTER_WIDTH, mScaleY, mScaleZ);
	SetPosition(mPositionX, mPositionY, mPositionZ);
}

void Character::SetPosition(float _x, float _y, float _z)
{
	mPositionX = _x;
	mPositionY = _y;
	mPositionZ = _z;

	mPosition.mX = mPositionX;
	mPosition.mY = mPositionY;
	mPosition.mZ = mPositionZ;

	for (Geometry* geo : mGeometries)
	{
		geo->SetPosition({ mPositionX, mPositionY, mPositionZ });
	}
}

Vector3_Character_Position Character::GetPosition()
{
	mPosition.mX = mPositionX;
	mPosition.mY = mPositionY;
	mPosition.mZ = mPositionZ;

	return mPosition;
}

void Character::SetScale(float _x, float _y, float _z)
{
	mScaleX = _x;
	mScaleY = _y;
	mScaleZ = _z;

	mScale.mX = mScaleX;
	mScale.mY = mScaleY;
	mScale.mZ = mScaleZ;

	for (Geometry* geo : mGeometries)
	{
		geo->SetScale({ mScaleX, mScaleY, mScaleZ });
	}
}

Vector3_Character_Scale Character::GetScale()
{
	mScale.mX = mScaleX;
	mScale.mY = mScaleY;
	mScale.mZ = mScaleZ;

	return mScale;
}

void Character::SetIsDead(bool _isDead)
{
	mIsDead = _isDead;
	if (_isDead)
		std::cout << "Character died!" << std::endl;
}

void Character::MoveUp(float _deltaTime)
{
	if (IsAtFloor() && !IsFreeFalling())
	{
		Jump(_deltaTime);
		std::cout << "Jumping!" << std::endl;
	}
}

void Character::MoveDown(float _deltaTime)
{
	if (IsAirborne())
	{
		FastFall(_deltaTime);
	}
	else
	{
		Slide(_deltaTime);
		std::cout << "Sliding!" << std::endl;
	}
}

void Character::MoveLeft(float _deltaTime)
{
	if (!IsLeftLane())
	{
		StepLeft(_deltaTime);
		std::cout << "Moving Left!" << std::endl;
	}
}

void Character::MoveRight(float _deltaTime)
{
	if (!IsRightLane())
	{
		StepRight(_deltaTime);
		std::cout << "Moving Right!" << std::endl;
	}
}

void Character::StepLeft(float _deltaTime)
{
	if (mTargetX > -STEP)
		mTargetX -= STEP;
}

void Character::StepRight(float _deltaTime)
{
	if (mTargetX < STEP)
		mTargetX += STEP;
}

void Character::Jump(float _deltaTime)
{
	if (IsAtFloor())
	{
		if (mIsBigJumpBoostActive)
		{
			mVelocityY = JUMP_VELOCITY_BOOST;
		}
		else
		{
			mVelocityY = JUMP_VELOCITY;
		}
		mIsFastFalling = false;
		std::cout << "Jumping!" << std::endl;
	}
}

void Character::Slide(float _deltaTime)
{
	if (!mIsSliding)
	{
		mIsSliding = true;
		mSlideTimer = 0.0f;
		std::cout << "Sliding!" << std::endl;
	}
}

void Character::FastFall(float _deltaTime)
{
	if (IsAirborne())
	{
		if (!mIsFastFalling)
		{
			if (mVelocityY > 0.0f)
				mVelocityY = 0.0f;

			mVelocityY -= FAST_FALL;

			mIsFastFalling = true;
			std::cout << "Fast Falling!" << std::endl;
		}
	}
}

void Character::StopSliding()
{
	mIsSliding = false;
	mSlideTimer = 0.0f;
}

float Character::GetSlideHeight() const
{
	float halfHeight = CHARACTER_HEIGHT * SLIDE_SCALE_Y;

	if (mSlideTimer <= SLIDE_DURATION / 2.0f)
	{
		float t = mSlideTimer / (SLIDE_DURATION / 2.0f);
		return CHARACTER_HEIGHT + t * (halfHeight - CHARACTER_HEIGHT);
	}
	else if (mSlideTimer <= SLIDE_DURATION)
	{
		float t = (mSlideTimer - SLIDE_DURATION / 2.0f) / (SLIDE_DURATION / 2.0f);
		return halfHeight + t * (CHARACTER_HEIGHT - halfHeight);
	}

	return CHARACTER_HEIGHT;
}

void Character::StartFreeFall()
{
	mIsFreeFalling = true;
	// ne jamais toucher à mVelocityY ici, pour conserver la vélocité de chute
}

void Character::AddGeometry(Geometry* _geometry)
{
	mGeometries.push_back(_geometry);
}

bool Character::IsCharacterAbove(std::vector<Tiles*>& _tiles)
{
	// Récupérer la position du personnage
	Vector3_Character_Position pos = GetPosition();

	// Vérifier si le perso est "au-dessus" d'une des tuiles
	for (Tiles* tile : _tiles)
	{
		if (tile && tile->IsCharacterAbove(pos.mX, pos.mZ))
		{
			return true; // le perso est sur une tuile
		}
	}

	return false; // sinon, il est dans le vide
}

bool Character::IsCollideBonus(Bonus* _bonus)
{
	Vector3_Character_Position pos = GetPosition();
	if (_bonus->IsCollideCharacter(pos.mX, pos.mY, pos.mZ))
	{
		std::cout << "Collision between entity Player and Bonus " << std::endl;
		return true;
	}
	return false;
}

void Character::SetBigJumpBoostActive(bool _boostIsActive)
{
	mIsBigJumpBoostActive = _boostIsActive;
}

void Character::SetBigJumpBoostActiveScene(bool _isActive)
{
	mIsBigJumpBoostActiveScene = _isActive;
}
