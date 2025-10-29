#include "pch.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
   
}

GameCamera::~GameCamera()
{
}

void GameCamera::Init()
{
    if (!mCamera)
    {
        mCamera = new Camera(CameraType::PERSPECTIVE);
        mCamera->SetPosition({ 0.0f, CAMERA_POSITION_Y, CAMERA_POSITION_Z });
        mCamera->SetRotation({ CAMERA_ROTATION_X, 0.0f, 0.0f });
        mCamera->SetFOV(gce::PI / 4.0f);
        mCamera->SetFarPlane(500.0f);
        mCamera->SetNearPlane(0.001f);
    }
}
void GameCamera::SetPosition(float _x, float _y, float _z)
{
    mCamera->SetPosition({ _x, _y, _z });
}

void GameCamera::SetRotation(float _x, float _y, float _z)
{
    mCamera->SetRotation({ _x, _y, _z });
}

Camera* GameCamera::GetCamera()
{
    if (!mCamera)
    {
        Init();
        std::cout << "Camera launch" << std::endl;
    }
    return mCamera;
}


