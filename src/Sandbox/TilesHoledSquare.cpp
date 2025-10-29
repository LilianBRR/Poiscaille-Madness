#include "pch.h"
#include "TilesHoledSquare.h"



void TilesHoledSquare::Init()
{
	SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, TILES_SPAWN_POSITION_Z);


	// === Carré avant ===
	squareFrontSide = new Cube();
	//squareFrontSide->SetTexture(*mGroundTexture);
	squareFrontSide->SetColor(TILES_COLOR);
	squareFrontSide->SetScale({ THIRD_SQUARES_SIZE, TILES_SQUARES_HEIGHT, QUARTER_DEPTH_SIZE });
	squareFrontSide->SetPosition({ TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, TILES_SPAWN_POSITION_Z + OFFSET_FRONT_SQUARE_POSITION_Z });
	AddGeometry(squareFrontSide);

	float halfWidthFront = THIRD_SQUARES_SIZE / 2.f;
	float halfDepthFront = QUARTER_DEPTH_SIZE / 2.f;
	Vector3_Tiles posFront = squareFrontSide->GetPosition();

	AddCollider({
		{ posFront.mX - halfWidthFront, posFront.mY, posFront.mZ - halfDepthFront },
		{ posFront.mX + halfWidthFront, posFront.mY, posFront.mZ - halfDepthFront },
		{ posFront.mX - halfWidthFront, posFront.mY, posFront.mZ + halfDepthFront },
		{ posFront.mX + halfWidthFront, posFront.mY, posFront.mZ + halfDepthFront }
		});


	// === Carré bas ===
	squareBottomSide = new Cube();
	//squareBottomSide->SetTexture(*mGroundTexture);
	squareBottomSide->SetColor(TILES_COLOR);
	squareBottomSide->SetScale({ THIRD_SQUARES_SIZE, TILES_SQUARES_HEIGHT, HALF_DEPTH_SIZE });
	squareBottomSide->SetPosition({ TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, TILES_SPAWN_POSITION_Z - OFFSET_BOTTOM_SQUARE_POSITION_Z });
	AddGeometry(squareBottomSide);

	float halfWidthBottom = THIRD_SQUARES_SIZE / 2.f;
	float halfDepthBottom = HALF_DEPTH_SIZE / 2.f;
	Vector3_Tiles posBottom = squareBottomSide->GetPosition();

	AddCollider({
		{ posBottom.mX - halfWidthBottom, posBottom.mY, posBottom.mZ - halfDepthBottom },
		{ posBottom.mX + halfWidthBottom, posBottom.mY, posBottom.mZ - halfDepthBottom },
		{ posBottom.mX - halfWidthBottom, posBottom.mY, posBottom.mZ + halfDepthBottom },
		{ posBottom.mX + halfWidthBottom, posBottom.mY, posBottom.mZ + halfDepthBottom }
		});


	// === Carré gauche ===
	squareLeftSide = new Cube();
	//squareLeftSide->SetTexture(*mGroundTexture);
	squareLeftSide->SetColor(TILES_COLOR);
	squareLeftSide->SetScale({ THIRD_SQUARES_SIZE, TILES_SQUARES_HEIGHT, THREE_QUARTER_DEPTH_SIZE });
	squareLeftSide->SetPosition({ TILES_SPAWN_POSITION_X - THIRD_SQUARES_SIZE , TILES_SPAWN_POSITION_Y, TILES_SPAWN_POSITION_Z + OFFSET_SIDE_SQUARES_POSITION_Z });
	AddGeometry(squareLeftSide);

	float halfWidthLeft = THIRD_SQUARES_SIZE / 2.f;
	float halfDepthLeft = THREE_QUARTER_DEPTH_SIZE / 2.f;
	Vector3_Tiles posLeft = squareLeftSide->GetPosition();

	AddCollider({
		{ posLeft.mX - halfWidthLeft, posLeft.mY, posLeft.mZ - halfDepthLeft },
		{ posLeft.mX + halfWidthLeft, posLeft.mY, posLeft.mZ - halfDepthLeft },
		{ posLeft.mX - halfWidthLeft, posLeft.mY, posLeft.mZ + halfDepthLeft },
		{ posLeft.mX + halfWidthLeft, posLeft.mY, posLeft.mZ + halfDepthLeft }
		});


	// === Carré droit ===
	squareRightSide = new Cube();
	//squareRightSide->SetTexture(*mGroundTexture);
	squareRightSide->SetColor(TILES_COLOR);
	squareRightSide->SetScale({ THIRD_SQUARES_SIZE, TILES_SQUARES_HEIGHT, THREE_QUARTER_DEPTH_SIZE });
	squareRightSide->SetPosition({ TILES_SPAWN_POSITION_X + THIRD_SQUARES_SIZE, TILES_SPAWN_POSITION_Y, TILES_SPAWN_POSITION_Z + OFFSET_SIDE_SQUARES_POSITION_Z });
	AddGeometry(squareRightSide);

	float halfWidthRight = THIRD_SQUARES_SIZE / 2.f;
	float halfDepthRight = THREE_QUARTER_DEPTH_SIZE / 2.f;
	Vector3_Tiles posRight = squareRightSide->GetPosition();

	AddCollider({
		{ posRight.mX - halfWidthRight, posRight.mY, posRight.mZ - halfDepthRight },
		{ posRight.mX + halfWidthRight, posRight.mY, posRight.mZ - halfDepthRight },
		{ posRight.mX - halfWidthRight, posRight.mY, posRight.mZ + halfDepthRight },
		{ posRight.mX + halfWidthRight, posRight.mY, posRight.mZ + halfDepthRight }
		});
}

void TilesHoledSquare::Update(float _deltaTime)
{
	SetPosition(mPosition.mX, mPosition.mY, mPosition.mZ - mSpeed * _deltaTime);
	Move(mPosition.mX, mPosition.mY, mPosition.mZ);
	UpdateColliders();
}

void TilesHoledSquare::Move(float _x, float _y, float _z)
{
	squareFrontSide->SetPosition({ _x,_y,_z + OFFSET_FRONT_SQUARE_POSITION_Z });
	squareBottomSide->SetPosition({ _x,_y,_z - OFFSET_BOTTOM_SQUARE_POSITION_Z });
	squareLeftSide->SetPosition({ _x - THIRD_SQUARES_SIZE,_y,_z + OFFSET_SIDE_SQUARES_POSITION_Z });
	squareRightSide->SetPosition({ _x + THIRD_SQUARES_SIZE,_y,_z + OFFSET_SIDE_SQUARES_POSITION_Z });
}

bool TilesHoledSquare::IsCharacterAbove(float _characterX, float _characterZ)
{
	for (const auto& collider : mColliders)
	{
		float minX = collider.bottomLeft.mX;
		if (collider.bottomRight.mX < minX) minX = collider.bottomRight.mX;
		if (collider.topLeft.mX < minX) minX = collider.topLeft.mX;
		if (collider.topRight.mX < minX) minX = collider.topRight.mX;

		float maxX = collider.bottomLeft.mX;
		if (collider.bottomRight.mX > maxX) maxX = collider.bottomRight.mX;
		if (collider.topLeft.mX > maxX) maxX = collider.topLeft.mX;
		if (collider.topRight.mX > maxX) maxX = collider.topRight.mX;

		float minZ = collider.bottomLeft.mZ;
		if (collider.bottomRight.mZ < minZ) minZ = collider.bottomRight.mZ;
		if (collider.topLeft.mZ < minZ) minZ = collider.topLeft.mZ;
		if (collider.topRight.mZ < minZ) minZ = collider.topRight.mZ;

		float maxZ = collider.bottomLeft.mZ;
		if (collider.bottomRight.mZ > maxZ) maxZ = collider.bottomRight.mZ;
		if (collider.topLeft.mZ > maxZ) maxZ = collider.topLeft.mZ;
		if (collider.topRight.mZ > maxZ) maxZ = collider.topRight.mZ;

		if (_characterX >= minX && _characterX <= maxX &&
			_characterZ >= minZ && _characterZ <= maxZ)
		{
			return true;
		}
	}

	return false;
}

void TilesHoledSquare::UpdateColliders()
{
	mColliders.clear();

	auto addTileCollider = [&](Cube* cube, float halfWidth, float halfDepth)
		{
			auto pos = cube->GetPosition();
			AddCollider({
				{ pos.x - halfWidth, pos.y, pos.z - halfDepth },
				{ pos.x + halfWidth, pos.y, pos.z - halfDepth },
				{ pos.x - halfWidth, pos.y, pos.z + halfDepth },
				{ pos.x + halfWidth, pos.y, pos.z + halfDepth }
				});
		};

	addTileCollider(squareFrontSide, THIRD_SQUARES_SIZE / 2.f, QUARTER_DEPTH_SIZE / 2.f);
	addTileCollider(squareBottomSide, THIRD_SQUARES_SIZE / 2.f, HALF_DEPTH_SIZE / 2.f);
	addTileCollider(squareLeftSide, THIRD_SQUARES_SIZE / 2.f, THREE_QUARTER_DEPTH_SIZE / 2.f);
	addTileCollider(squareRightSide, THIRD_SQUARES_SIZE / 2.f, THREE_QUARTER_DEPTH_SIZE / 2.f);
}
