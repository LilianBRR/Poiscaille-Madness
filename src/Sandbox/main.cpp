#include "pch.h"
#include "GameManager.h"
int main()
{
    srand(static_cast<unsigned int>(time(0)));

    GameManager* pInstance = GameManager::GetInstance();
    pInstance->GetSceneManager();
    pInstance->Run();

    return 0;
}

/* //Window creation
    Window window(L"Test", 1920, 1080);

    //Camera creation
    Camera camera(CameraType::PERSPECTIVE);
    camera.SetPosition({0.0f, 20.0f, -20.0f});
    camera.SetRotation({45.0f, 0.0f, 0.0f});
    camera.SetFOV(gce::PI/4.0f);
    camera.SetFarPlane(500.0f);
    camera.SetNearPlane(0.001f);

   

    //Mesh creation
    Cube floor;
    floor.SetTexture(texture);
    floor.SetPosition({0.0f, 0.0f, 0.0f});
    floor.SetScale({20.0f, 0.1f, 20.0f});

    Cube wall;
    wall.SetTexture(texture);
    wall.SetPosition({0.0f, 5.0f, 5.0f});
    wall.SetScale({20.0f, 0.1f, 20.0f});
    wall.SetRotation({90.0f, 0.0f, 0.0f});

	gce::Font font(L"Arial");

	Text text;
    text.SetFont(&font);
    text.SetText(L"Use WASD to move the camera");
    text.SetPosition({25.0f, 25.0f});
	text.SetColor(gce::Color::White);

    //Rendering Loop
    while (window.IsOpen())
    {
        window.Begin(camera);
            window.Draw(wall);
            window.Draw(floor);

			window.DrawText(text);

        window.End();
        
        window.Display();

        //Game logic

        gce::Vector3f32 dir = {};
        dir.x = GetKey(Keyboard::D) - GetKey(Keyboard::A);
        dir.z = GetKey(Keyboard::W) - GetKey(Keyboard::S);
        dir.SelfNormalize();
        dir *= 0.016f;
        
        camera.Translate(dir);
        
    }
    */