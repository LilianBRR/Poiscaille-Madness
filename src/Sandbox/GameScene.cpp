#include "pch.h"
#include "GameScene.h"
#include "TilesSquare.h"
#include "TilesRightElbow.h"
#include "TilesLeftElbow.h"
#include "TilesHoledSquare.h"
#include "Character.h"
#include "BigJumpBonus.h"
#include "SpeedSlowingBonus.h"
#include "ScoreMultiplierBonus.h"
#include "Controller.h"
#include <iostream>

void GameScene::Init()
{
	std::cout << "GameScene launch" << std::endl;
	mGameCamera = new GameCamera();
	mGroundTexture = new Texture("res/Textures/wood.png");

	mGameOver = false;

	float spawnPositionZ = TILE_DEPTH_SIZE;

	TilesSquare* firstSquare = new TilesSquare;
	firstSquare->Init();
	firstSquare->SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, 0.f);
	AddTile(firstSquare);

	TilesSquare* secondSquare = new TilesSquare;
	secondSquare->Init();
	secondSquare->SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, spawnPositionZ);
	AddTile(secondSquare);

	for (int i = 0; i < MAX_FIRST_SPAWN_TILES; i++)
	{
		int randomTile = rand() % 4;

		spawnPositionZ += TILE_DEPTH_SIZE;

		if (randomTile == SQUARE_TILE_CHOOSE)
		{
			TilesSquare* square = new TilesSquare;
			square->SetGroundTexture(mGroundTexture);
			square->Init();
			square->SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, spawnPositionZ);
			AddTile(square);
		}
		else if (randomTile == RIGHT_ELBOW_TILE_CHOOSE)
		{
			TilesRightElbow* square = new TilesRightElbow;
			square->SetGroundTexture(mGroundTexture);
			square->Init();
			square->SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, spawnPositionZ);
			AddTile(square);
		}
		else if (randomTile == LEFT_ELBOW_TILE_CHOOSE)
		{
			TilesLeftElbow* square = new TilesLeftElbow;
			square->SetGroundTexture(mGroundTexture);
			square->Init();
			square->SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, spawnPositionZ);
			AddTile(square);
		}
		else if (randomTile == HOLED_SQUARE_TILE_CHOOSE)
		{
			TilesHoledSquare* square = new TilesHoledSquare;
			square->SetGroundTexture(mGroundTexture);
			square->Init();
			square->SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, spawnPositionZ);
			AddTile(square);
		}


	}

	mController = new Controller();
	mController->Init();

	mCharacter = new Character();
	mCharacter->Init();

	mController->SetCharacter(mCharacter);


	mFont = new gce::Font();
	mFont->Load(L"Comic sans MS");

	mTimer = 0;

	mTimerText = new Text();
	mTimerText->SetFont(mFont);
	mTimerText->SetColor(gce::Color::Black);
	mTimerText->SetPosition(TEXT_TIME_POSITION);
	mTimerText->SetText(L"Time : 0");
	AddText(mTimerText);

	mScore = 0;

	mScoreText = new Text();
	mScoreText->SetFont(mFont);
	mScoreText->SetColor(gce::Color::Black);
	mScoreText->SetPosition(TEXT_SCORE_POSITION);
	mScoreText->SetText(L"Score : 0");
	AddText(mScoreText);

}

void GameScene::Update(float _deltaTime)
{
	if (mIsRestarting)
		return;

	mController->Update(_deltaTime);

	if (!mController->GetPause() && !mCharacter->IsDead())
	{
		for (Tiles* tile : mTiles)
		{
			tile->Update(_deltaTime);
			if (tile->GetPosition().mZ <= -30.f)
			{
				EraseTile(tile);
			}
		}

		//Speed Up
		mIncreaseSpeedCurrentTime += _deltaTime;
		if (mIncreaseSpeedCurrentTime >= mTimeBeforeSpeedIncrease && mNewSpeed <= mMaxSpeed)
		{
			mTimeBeforeTileSpawn *= 0.99f;
			for (Tiles* tile : mTiles)
			{
				mNewSpeed = tile->GetSpeed() * 1.01f;
				tile->SetSpeed(mNewSpeed);
			}
			mIncreaseSpeedCurrentTime = 0.f;
		}

		//Spawn Tile
		mTileSpawnCurrentTime += _deltaTime;
		if (mTileSpawnCurrentTime >= mTimeBeforeTileSpawn)
		{
			int randomTile = rand() % 4;
			LoadTiles(randomTile);
			mTileSpawnCurrentTime = 0.f;
		}

		//Bonus Spawn
		mCurrentTimeBonusSpawning += _deltaTime;
		if (mCurrentTimeBonusSpawning >= mTimeBeforeBonusSpawning)
		{
			int randomBonus = rand() % 2;
			LoadBonus(randomBonus);
			mCurrentTimeBonusSpawning = 0.f;
		}

		for (Bonus* bonus : mBonus)
		{
			bonus->Update(_deltaTime);
			bonus->SetSpeed(mNewSpeed);
			if (mCharacter->IsCollideBonus(bonus))
			{
				if (bonus->GetTag() == BIG_JUMP_TAG)
				{
					mCharacter->SetBigJumpBoostActive(true);
					mTextBonusBar = new Text();
					mTextBonusBar->SetFont(mFont);
					mTextBonusBar->SetColor(gce::Color::Black);
					mTextBonusBar->SetPosition(TEXT_JUMP_BONUS_BAR_POSITION);
					mTextBonusBar->SetText(L"Jump Boost");
					AddText(mTextBonusBar);

					mCurrentTimeBonus = 0.f;
				}
				/*if (bonus->GetTag() == SPEED_SLOWING_TAG)
				{
					mIsSpeedSlowingBonusActive = true;
				}*/
				if (bonus->GetTag() == SCORE_MULTIPLIER_TAG)
				{

					mIsScoreMultiplierBonusActive = true;

					mTextBonusBar = new Text();
					mTextBonusBar->SetFont(mFont);
					mTextBonusBar->SetColor(gce::Color::Black);
					mTextBonusBar->SetPosition(TEXT_SCORE_BONUS_BAR_POSITION);
					mTextBonusBar->SetText(L"Score x5");
					AddText(mTextBonusBar);

					mCurrentTimeBonus = 0.f;
				}
				EraseBonus(bonus);
			}
			else if (bonus->GetPosition().mZ <= -30.f)
			{
				EraseBonus(bonus);
			}
		}

		bool onTile = false;
		Vector3_Character_Position charPos = mCharacter->GetPosition();

		// mTiles est le vecteur des tiles de la scene (tu l'utilises deja dans ce fichier)
		if (charPos.mY >= mCharacter->mMinFallY)
		{
			for (Tiles* tile : mTiles)
			{
				for (Tiles* tile : mTiles)
				{
					if (tile && tile->IsCharacterAbove(charPos.mX, charPos.mZ))
					{
						onTile = true;
						break;
					}
				}
			}
		}
		if (!onTile)
		{
			// Si le perso n'�tait pas d�j� en freefall, on le met en freefall
			if (!mCharacter->IsFreeFalling())
			{
				mCharacter->StartFreeFall(); // ne touche pas � la v�locit�
			}
		}
		else
		{
			// Si on est sur une tile, on s'assure que le perso n'est pas en "freefall"
			mCharacter->SetFreeFalling(false);
		}

		// Mise � jour de l'�tat du Character
		mCharacter->Update(_deltaTime);
		if (mCharacter->GetIsBigJumpBoostActive())
		{
			mCurrentTimerDuringBonus += _deltaTime;
			if (mCurrentTimerDuringBonus >= TIME_BEFORE_DECREASE_TIMER_BONUS)
			{
				mTimerBonus -= TIME_BEFORE_DECREASE_TIMER_BONUS;
				int whole = static_cast<int>(mTimerBonus);
				int decimal = static_cast<int>((mTimerBonus - whole) * 10);

				mTextBonusBar->SetText(L"Jump Boost ( " + std::to_wstring(whole) + L"." + std::to_wstring(decimal) + L"s)");

				mCurrentTimerDuringBonus = 0.f;
			}
		}
		if (!mCharacter->GetIsBigJumpBoostActiveScene())
		{
			EraseText(mTextBonusBar);
			mCharacter->SetBigJumpBoostActiveScene(true);
			mTimerBonus = TIMER_BONUS;
		}

		mScoreCurrentTime += _deltaTime;
		if (mScoreCurrentTime >= mTimeBeforeScoreIncrease)
		{
			if (mIsScoreMultiplierBonusActive)
			{
				mScore += mScoreIncreaserBoost;
				mCurrentTimeBonus += _deltaTime;
				mCurrentTimerDuringBonus += _deltaTime;
				if (mCurrentTimerDuringBonus >= TIME_BEFORE_DECREASE_TIMER_BONUS)
				{
					mTimerBonus -= TIME_BEFORE_DECREASE_TIMER_BONUS;

					int whole = static_cast<int>(mTimerBonus);
					int decimal = static_cast<int>((mTimerBonus - whole) * 10);

					mTextBonusBar->SetText(L"Score x5 ( " + std::to_wstring(whole) + L"." + std::to_wstring(decimal) + L"s)");

					mCurrentTimerDuringBonus = 0.f;
				}
				if (mCurrentTimeBonus >= mMaxDurationBonus)
				{
					mCurrentTimeBonusSpawning = 0.f;
					mIsScoreMultiplierBonusActive = false;
					std::cout << "Bonus Score finish" << std::endl;
					EraseText(mTextBonusBar);
					mTimerBonus = TIMER_BONUS;
				}
			}
			else
			{
				mScore += mScoreIncreaser;
			}
			mScore++;
			std::wstring score = std::to_wstring(mScore);
			mScoreText->SetText(L"Score : " + score);
			mScoreCurrentTime = 0.f;
		}
		mTimerCurrentTime += _deltaTime;
		if (mTimerCurrentTime >= mTimeBeforeTimerIncrease)
		{
			mTimer++;
			std::wstring timer = std::to_wstring(mTimer);
			mTimerText->SetText(L"Time : " + timer);
			mTimerCurrentTime = 0.f;
		}
	}

	if (mController->GetPause())
	{
		if (mController->GetRestart())
		{
			Reset();
			mController->SwapPause();
			return;
		}
	}

	if (mCharacter->IsDead())
	{

		for (Tiles* tile : mTiles)
		{
			tile->Update(_deltaTime);
			if (tile->GetPosition().mZ <= -30.f)
			{
				EraseTile(tile);
			}
		}
		

		mIncreaseSpeedCurrentTime += _deltaTime;
		if (mIncreaseSpeedCurrentTime >= mTimeBeforeSpeedDecrease)
		{
			mTimeBeforeTileSpawn *= 1.5f;
			for (Tiles* tile : mTiles)
			{
				mNewSpeed = tile->GetSpeed() * (2.f / 3.f);
				tile->SetSpeed(mNewSpeed);
			}
			mIncreaseSpeedCurrentTime = 0.f;
		}
		for (Bonus* bonus : mBonus)
		{
			bonus->Update(_deltaTime);
			bonus->SetSpeed(mNewSpeed);
		}

		mTileSpawnCurrentTime += _deltaTime;
		if (mTileSpawnCurrentTime >= mTimeBeforeTileSpawn)
		{
			int randomTile = rand() % 4;
			LoadTiles(randomTile);
			mTileSpawnCurrentTime = 0.f;
		}

		// Mise à jour de l'état du Character
		mCharacter->Update(_deltaTime);

		if (mController->GetRestart())
		{
			Reset();
			return;
		}

	}
}

void GameScene::ClearScene()
{
	for (Tiles* tile : mTiles)
		delete tile;
	mTiles.clear();

	delete mCharacter;
	mCharacter = nullptr;

	delete mController;
	mController = nullptr;
}

void GameScene::Reset()
{
	std::cout << "GameScene reset" << std::endl;

	//1 Supprimer toutes les tiles actuelles
	for (Tiles* tile : mTiles)
		delete tile;
	mTiles.clear();

	//2 R�initialiser les variables de jeu
	mScore = 0;
	mTimer = 0;
	mScoreCurrentTime = 0.f;
	mTimerCurrentTime = 0.f;
	mTileSpawnCurrentTime = 0.f;
	mIncreaseSpeedCurrentTime = 0.f;
	mCurrentTimeBonusSpawning = 0.f;
	mCurrentTimeBonus = 0.f;
	mCurrentTimerDuringBonus = 0.f;
	mTimeBeforeTileSpawn = TIME_BEFORE_TILE_SPAWN;
	mNewSpeed = NEW_SPEED;
	mGameOver = false;
	mCharacter->SetIsDead(false);

	//3 Recr�er les premi�res tuiles comme dans Init()
	float spawnPositionZ = TILE_DEPTH_SIZE;

	TilesSquare* firstSquare = new TilesSquare;
	firstSquare->Init();
	firstSquare->SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, 0.f);
	AddTile(firstSquare);

	TilesSquare* secondSquare = new TilesSquare;
	secondSquare->Init();
	secondSquare->SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, spawnPositionZ);
	AddTile(secondSquare);

	for (int i = 0; i < MAX_FIRST_SPAWN_TILES; i++)
	{
		int randomTile = rand() % 4;
		spawnPositionZ += TILE_DEPTH_SIZE;

		Tiles* tile = nullptr;
		switch (randomTile)
		{
		case SQUARE_TILE_CHOOSE:
			tile = new TilesSquare;
			break;
		case RIGHT_ELBOW_TILE_CHOOSE:
			tile = new TilesRightElbow;
			break;
		case LEFT_ELBOW_TILE_CHOOSE:
			tile = new TilesLeftElbow;
			break;
		case HOLED_SQUARE_TILE_CHOOSE:
			tile = new TilesHoledSquare;
			break;
		default:
			break;
		}

		if (tile)
		{
			tile->SetGroundTexture(mGroundTexture);
			tile->Init();
			tile->SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, spawnPositionZ);
			AddTile(tile);
		}
	}

	//4 R�initialiser le joueur
	mCharacter->ResetTargetX();
	mCharacter->SetPosition(CHARACTER_POSITION_X, CHARACTER_POSITION_Y, CHARACTER_POSITION_Z);
	mCharacter->SetIsDead(false);
	mCharacter->SetFreeFalling(false);

	//5 R�initialiser le texte du score et du timer
	mScoreText->SetText(L"Score : 0");
	mTimerText->SetText(L"Time : 0");

	//6 R�initialiser le contr�leur
	mController->SetRestart(false);
}

void GameScene::LoadTiles(int _randomChoose)
{
	switch (_randomChoose)
	{
	case SQUARE_TILE_CHOOSE:
	{
		TilesSquare* square = new TilesSquare;
		square->SetGroundTexture(mGroundTexture);
		square->Init();
		square->SetSpeed(mNewSpeed);
		AddTile(square);
		break;
	}
	case RIGHT_ELBOW_TILE_CHOOSE:
	{
		TilesRightElbow* square = new TilesRightElbow;
		square->SetGroundTexture(mGroundTexture);
		square->Init();
		square->SetSpeed(mNewSpeed);
		AddTile(square);
		break;
	}
	case LEFT_ELBOW_TILE_CHOOSE:
	{
		TilesLeftElbow* square = new TilesLeftElbow;
		square->SetGroundTexture(mGroundTexture);
		square->Init();
		square->SetSpeed(mNewSpeed);
		AddTile(square);
		break;
	}
	case HOLED_SQUARE_TILE_CHOOSE:
	{
		TilesHoledSquare* square = new TilesHoledSquare;
		square->SetGroundTexture(mGroundTexture);
		square->Init();
		square->SetSpeed(mNewSpeed);
		AddTile(square);
		break;
	}
	default:
		std::cout << "Tile not choose... " << std::endl;
		break;
	}
}

void GameScene::LoadBonus(int _randomChoose)
{

	
	switch (_randomChoose)
	{
	case BIG_JUMP_BONUS_CHOOSE:
	{
		int randomX = rand() % 3;
		float posX = 0.f;
		switch (randomX)
		{
		case LEFT_BONUS_SPAWN:
		{
			posX = -BONUS_SPAWN_SIDE_X;
			break;
		}
		case CENTER_BONUS_SPAWN:
		{
			posX = BONUS_POSITION_X;
			break;
		}
		case RIGHT_BONUS_SPAWN:
		{
			posX = BONUS_SPAWN_SIDE_X;
			break;
		}
		default:
			std::cout << "Pos x not choose..." << std::endl;
			break;
		}
		BigJumpBonus* bonus = new BigJumpBonus();
		bonus->Init();
		bonus->SetPosition(posX, BONUS_POSITION_Y, BONUS_POSITION_Z);
		AddBonus(bonus);
		break;
	}
	case SCORE_MULTIPLIIER_BONUS_CHOOSE:
	{
		int randomX = rand() % 3;
		float posX = 0.f;
		switch (randomX)
		{
		case LEFT_BONUS_SPAWN:
		{
			posX = -BONUS_SPAWN_SIDE_X;
			break;
		}
		case CENTER_BONUS_SPAWN:
		{
			posX = BONUS_POSITION_X;
			break;
		}
		case RIGHT_BONUS_SPAWN:
		{
			posX = BONUS_SPAWN_SIDE_X;
			break;
		}
		default:
			std::cout << "Pos x not choose..." << std::endl;
			break;
		}
		ScoreMultiplierBonus* bonus = new ScoreMultiplierBonus();
		bonus->Init();
		bonus->SetPosition(posX, BONUS_POSITION_Y, BONUS_POSITION_Z);
		AddBonus(bonus);
		break;
	}
	default:
		std::cout << "Bonus not choose... " << std::endl;
		break;
	}
}

Camera* GameScene::GetCamera()
{
	return mGameCamera->GetCamera();
}
