#include "pch.h"
#include "Controller.h"


void Controller::Init()
{
	mUp = mDown = mLeft = mRight = false;
	mPause = mRestart = false;
}

void Controller::Update(float _deltaTime)
{
	if (!mCharacter) return;
	HandleInput(_deltaTime);
}

void Controller::HandleInput(float _deltaTime)
{
	if (!mCharacter) return;

	if (GetKeyDown(Keyboard::ESCAPE) || GetKeyDown(Keyboard::P))
		SwapPause();

	if (!mPause)
	{
		if (GetKeyDown(Keyboard::LEFT_ARROW) || GetKeyDown(Keyboard::Q))
			mCharacter->MoveLeft(_deltaTime);

		if (GetKeyDown(Keyboard::RIGHT_ARROW) || GetKeyDown(Keyboard::D))
			mCharacter->MoveRight(_deltaTime);

		if (GetKeyDown(Keyboard::UP_ARROW) || GetKeyDown(Keyboard::Z))
			mCharacter->MoveUp(_deltaTime);

		if (GetKeyDown(Keyboard::DOWN_ARROW) || GetKeyDown(Keyboard::S))
			mCharacter->MoveDown(_deltaTime);
	}

	if (GetPause() || mCharacter->IsDead())
	{
		if (GetKeyDown(Keyboard::SPACEBAR) || GetKeyDown(Keyboard::R))
		{
			SetRestart(true);
		}
	}
	
}
