#pragma once
#include "Character.h"

class Controller
{
private:

	Character* mCharacter = nullptr;

	bool mUp;
	bool mDown;
	bool mLeft;
	bool mRight;

	bool mPause;
	bool mRestart;


public:
	Controller() = default;
	~Controller() = default;

	void Init();
	void Update(float _deltaTime);
	void HandleInput(float _deltaTime);

	void SetCharacter(Character* character) { mCharacter = character; }

	bool IsUp() const { return mUp; }
	bool IsDown() const { return mDown; }
	bool IsLeft() const { return mLeft; }
	bool IsRight() const { return mRight; }

	void SetUp(bool up) { mUp = up; }
	void SetDown(bool down) { mDown = down; }
	void SetLeft(bool left) { mLeft = left; }
	void SetRight(bool right) { mRight = right; }

	void SwapPause() { mPause = !mPause; }
	bool GetPause() const { return mPause; }

	void SetRestart(bool _restart) { mRestart = _restart; }
	bool GetRestart() const { return mRestart; }

};

