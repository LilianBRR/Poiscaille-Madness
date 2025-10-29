#include "pch.h"
#include "SceneManager.h"
#include "GameScene.h"

void SceneManager::LoadScene(int _sceneID)
{
	if (mScene)
	{
		delete mScene;
		mScene = nullptr;
	}

	mScene = new GameScene();
	mScene->Init();
	
}

Camera* SceneManager::GetSceneCamera()
{
	if (!mScene)
		return nullptr;

	return mScene->GetCamera();
}

void SceneManager::Update(float _deltaTime)
{
	if (mScene)
		mScene->Update(_deltaTime);
}

std::vector<Geometry*> SceneManager::RenderGeometry()
{
	if (!mScene)
		return {};
	return mScene->GetGeometries();
}

std::vector<Text*> SceneManager::RenderText()
{
	if (!mScene)
		return {};
	return mScene->GetTexts();
}
