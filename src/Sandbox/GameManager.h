#pragma once
#include "SceneManager.h"

class GameManager
{
	static GameManager* mGameManagerInstance;
	static SceneManager* mSceneManagerInstance;
	Window* mGameWindow;

public : 

	GameManager() = default;
	~GameManager() = default;

	static GameManager* GetInstance();
	SceneManager* GetSceneManager();

	void Run();
	void Update(float _deltaTime);
	void Draw();

};

