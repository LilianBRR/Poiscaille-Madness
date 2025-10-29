#pragma once
#include "GameCamera.h"
#include "Tiles.h"
#include "Character.h"
#include "Bonus.h"
#include "Controller.h"

class Scene
{
protected :

	std::vector<Tiles*> mTiles;
	std::vector<Bonus*> mBonus;
	std::vector<Text*> mTexts;
	std::vector<Text*> mBonusBar;
	Character* mCharacter;
	Controller* mController;
	Camera* mSceneCamera;
	
public :

	Scene();
	~Scene();

	virtual void Init() = 0;
	virtual void Update(float _deltaTime) = 0;

	virtual Camera* GetCamera() = 0;

	void AddTile(Tiles* _tile);
	void EraseTile(Tiles* _tile);
	void AddBonus(Bonus* _bonus);
	void EraseBonus(Bonus* _bonus);

	std::vector<Geometry*> GetGeometries();

	void EraseText(Text* _text);
	void EraseBonusBar(Text* _text);


	void AddText(Text* _text);
	void AddTextBar(Text* _text);
	std::vector<Text*> GetTexts();	
};

