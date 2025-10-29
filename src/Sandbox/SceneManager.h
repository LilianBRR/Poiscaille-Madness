#pragma once
#include "Scene.h"
class SceneManager
{
	Scene* mScene;
public:

	SceneManager() = default;
	~SceneManager() = default;

	void LoadScene(int _sceneID);
	Camera* GetSceneCamera();
	void Update(float _deltaTime);
	std::vector<Geometry*> RenderGeometry();
	std::vector<Text*> RenderText();
};

