#pragma once
#include "Tiles.h"

class TilesLeftElbow : public Tiles
{
	Cube* squareLeftSide;
	Cube* squareFrontSide;

	Vector3_Tiles_Collider mLeftSideBaseBottomLeft;
	Vector3_Tiles_Collider mLeftSideBaseBottomRight;
	Vector3_Tiles_Collider mFrontSideBaseBottomLeft;
	Vector3_Tiles_Collider mFrontSideBaseBottomRight;


public:
	TilesLeftElbow() = default;
	~TilesLeftElbow() = default;
	void Init() override;
	void Update(float _deltaTime) override;
	void Move(float _x, float _y, float _z) override;

	bool IsCharacterAbove(float _characterX, float _characterZ) override;

	void UpdateColliders() override;
};

