#pragma once
#include "TIles.h"
class TilesHoledSquare : public Tiles
{
	Cube* squareFrontSide;
	Cube* squareBottomSide;
	Cube* squareLeftSide;
	Cube* squareRightSide;
public : 

	TilesHoledSquare() = default;
	~TilesHoledSquare() = default;
	void Init() override;
	void Update(float _deltaTime) override;
	void Move(float _x, float _y, float _z) override;

	bool IsCharacterAbove(float _characterX, float _characterZ) override;

	void UpdateColliders() override;
};

