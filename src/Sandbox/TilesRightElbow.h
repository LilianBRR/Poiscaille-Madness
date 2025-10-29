#pragma once
#include "Tiles.h"
class TilesRightElbow : public Tiles
{
	Cube* squareRightSide;
	Cube* squareFrontSide;
public :
	TilesRightElbow() = default;
	~TilesRightElbow() = default;
	void Init() override;
	void Update(float _deltaTime) override;
	void Move(float _x, float _y, float _z) override;

	bool IsCharacterAbove(float _characterX, float _characterZ) override;

	void UpdateColliders() override;
};

