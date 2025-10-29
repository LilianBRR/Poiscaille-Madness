#include "pch.h"
#include "GameManager.h"
#include <chrono>
#include <thread>

GameManager* GameManager::mGameManagerInstance = nullptr;
SceneManager* GameManager::mSceneManagerInstance = nullptr;


GameManager* GameManager::GetInstance()
{

    if (mGameManagerInstance == nullptr)
    {
        mGameManagerInstance = new GameManager();
    }

    return mGameManagerInstance;
}

SceneManager* GameManager::GetSceneManager()
{
    if (mSceneManagerInstance == nullptr)
    {
        mSceneManagerInstance = new SceneManager();
    }

    return mSceneManagerInstance;
}

void GameManager::Run()
{
    mGameWindow = new Window(L"Runner3D", 1920, 1080);

    mSceneManagerInstance->LoadScene(0);

    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::time_point<Clock> TimePoint;

	const float TARGET_FPS = 120.0f;
    TimePoint lastTime = Clock::now();

    while (mGameWindow->IsOpen())
    {
		TimePoint currentTime = Clock::now();
		std::chrono::duration<float> deltaTime = currentTime - lastTime;
		float dt = deltaTime.count();
		lastTime = currentTime;


        Camera* cam = nullptr;
        if (mSceneManagerInstance)
            cam = mSceneManagerInstance->GetSceneCamera();

        if (cam)
        {
            mGameWindow->Begin(*cam);
            Update(dt);
            Draw();
            mGameWindow->End();
            mGameWindow->Display();
        }

		TimePoint endTime = Clock::now();
		std::chrono::duration<float> frameDuration = endTime - currentTime;

		float frameTime = frameDuration.count();

		if (frameTime < (1.0f / TARGET_FPS))
		{
			float sleepTime = (1.0f / TARGET_FPS) - frameTime;
            std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
		}
    }
}

void GameManager::Update(float _deltaTime)
{
    mSceneManagerInstance->Update(_deltaTime);
}

void GameManager::Draw()
{

    if (!mSceneManagerInstance)
        return;

    std::vector<Geometry*> geometries = mSceneManagerInstance->RenderGeometry();
    for (Geometry* geo : geometries)
    {
        if (geo)
            mGameWindow->Draw(*geo);
    }

    std::vector<Text*> texts = mSceneManagerInstance->RenderText();
    for (Text* text : texts)
    {
        if (text)
            mGameWindow->DrawText(*text);
    }
}

