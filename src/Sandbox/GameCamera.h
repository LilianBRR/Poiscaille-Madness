#pragma once
#include "Camera.h"

class GameCamera
{
	Camera* mCamera = nullptr;;
public : 

	GameCamera();
	~GameCamera();
	void Init();
	void Update();
	void SetPosition(float _x, float _y, float _z);
	void SetRotation(float _x, float _y, float _z);
	Camera* GetCamera();
};

