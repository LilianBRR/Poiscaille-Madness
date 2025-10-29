#pragma once
#include "Scene.h"
#include "GameCamera.h"


class GameScene : public Scene
{
	GameCamera* mGameCamera = nullptr;

	bool mGameOver;
	gce::Font* mFont;

	float mTileSpawnCurrentTime;
	float mTimeBeforeTileSpawn = TIME_BEFORE_TILE_SPAWN;

	float mIncreaseSpeedCurrentTime;
	float mTimeBeforeSpeedIncrease = TIME_BEFORE_SPEED_INCREASE;
	float mTimeBeforeSpeedDecrease = TIME_BEFORE_SPEED_DECREASE;
	float mIncreaseSpeedCurrentTimeBonus;

	Text* mScoreText;
	int mScore = 0;
	int mScoreIncreaser = 1;
	int mScoreIncreaserBoost = 5;

	float mScoreCurrentTime;
	float mTimeBeforeScoreIncrease = TIME_BEFORE_SCORE_INCREASE;

	Text* mTimerText;
	int mTimer = 0;

	Text* mTimerBonusText;

	float mTimerCurrentTime;
	float mTimeBeforeTimerIncrease = TIME_BEFORE_TIMER_INCREASE;

	float mNewSpeed = NEW_SPEED;
	float mMaxSpeed = MAX_SPEED;

	bool mIsSpeedSlowingBonusActive = false;
	bool mIsScoreMultiplierBonusActive = false;

	//Temps entre chaque Spawn de bonus
	float mCurrentTimeBonusSpawning;
	float mTimeBeforeBonusSpawning = TIME_BEFORE_BONUS_SPAWNING;

	//Temps Total Bonus
	float mCurrentTimeBonus;

	//Timer affiche pendant le bonus
	float mCurrentTimerDuringBonus;
	float mTimerBonus = TIMER_BONUS;

	bool mRestartRequested = false;

	bool mIsRestarting = false;
	float mMaxDurationBonus = 10.f;

	float mBonusBarInitialeScaleX = CUBE_BAR_SCALE_X;

	/*float mCurrentTimeSpeedSlowingBonus = 0.f;
	float mMaxDurationSpeedBonus = 3.f;*/

	Texture* mGroundTexture;

	Text* mTextBonusBar;


public :

	GameScene() = default;

	void Init() override;
	void Update(float _deltaTime) override;
	bool ShouldRestart() const { return mRestartRequested; }

	void ClearScene();
	bool IsRestarting() const { return mIsRestarting; }

	void Reset();

	void LoadTiles(int _randomChoose);
	void LoadBonus(int _randomChoose);

	Camera* GetCamera() override;

	
};

