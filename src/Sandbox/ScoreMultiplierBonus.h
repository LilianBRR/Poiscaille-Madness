#pragma once
#include "Bonus.h"
class ScoreMultiplierBonus : public Bonus
{

public : 

	void Init() override;
	void Update(float _deltaTime) override;
	void Move(float _posX, float _posY, float _posZ) override;
	bool IsCollideCharacter(float _characterX, float _characterY, float _characterZ) override;
	//void UpdateColliders() override;
};


