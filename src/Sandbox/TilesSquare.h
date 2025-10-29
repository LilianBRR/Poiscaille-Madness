#pragma once
#include "Tiles.h"
class TilesSquare : public Tiles
{
	Cube* square;
public :

	TilesSquare() = default;
	~TilesSquare() = default;
	void Init() override;
	void Update(float _deltaTime) override;
	void Move(float _x, float _y, float _z) override;

	bool IsCharacterAbove(float _characterX, float _characterZ) override;

	void UpdateColliders() override;
};

