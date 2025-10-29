#include "pch.h"
#include "TilesRightElbow.h"



void TilesRightElbow::Init()
{
	SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, TILES_SPAWN_POSITION_Z);

	squareFrontSide = new Cube();
	//squareFrontSide->SetTexture(*mGroundTexture);
	squareFrontSide->SetColor(TILES_COLOR);
	squareFrontSide->SetScale({ TWO_THIRD_SQUARES_SIZE, TILES_SQUARES_HEIGHT, HALF_DEPTH_SIZE });
	squareFrontSide->SetPosition({ TILES_SPAWN_POSITION_X - ONE_SIXTH_SQUARES_SIZE, TILES_SPAWN_POSITION_Y,OFFSET_BOTTOM_SQUARE_POSITION_Z + TILES_SPAWN_POSITION_Z });
	AddGeometry(squareFrontSide);

    float halfWidthFront = TWO_THIRD_SQUARES_SIZE / 2.f;
    float halfDepthFront = HALF_DEPTH_SIZE / 2.f;
    Vector3_Tiles posFront = squareFrontSide->GetPosition();

    AddCollider({
        { posFront.mX - halfWidthFront, posFront.mY, posFront.mZ - halfDepthFront }, // bottomLeft
        { posFront.mX + halfWidthFront, posFront.mY, posFront.mZ - halfDepthFront }, // bottomRight
        { posFront.mX - halfWidthFront, posFront.mY, posFront.mZ + halfDepthFront }, // topLeft
        { posFront.mX + halfWidthFront, posFront.mY, posFront.mZ + halfDepthFront }  // topRight
        });

    // === Carr� droit ===
	squareRightSide = new Cube();
	//squareRightSide->SetTexture(*mGroundTexture);
	squareRightSide->SetColor(TILES_COLOR);
	squareRightSide->SetScale({ THIRD_SQUARES_SIZE, TILES_SQUARES_HEIGHT, TILE_DEPTH_SIZE });
	squareRightSide->SetPosition({ TILES_SPAWN_POSITION_X + THIRD_SQUARES_SIZE, TILES_SPAWN_POSITION_Y,  TILES_SPAWN_POSITION_Z});
	AddGeometry(squareRightSide);

    float halfWidthRight = THIRD_SQUARES_SIZE / 2.f;
    float halfDepthRight = TILE_DEPTH_SIZE / 2.f;
    Vector3_Tiles posRight = squareRightSide->GetPosition();

    AddCollider({
        { posRight.mX - halfWidthRight, posRight.mY, posRight.mZ - halfDepthRight },
        { posRight.mX + halfWidthRight, posRight.mY, posRight.mZ - halfDepthRight },
        { posRight.mX - halfWidthRight, posRight.mY, posRight.mZ + halfDepthRight },
        { posRight.mX + halfWidthRight, posRight.mY, posRight.mZ + halfDepthRight }
        });
}

void TilesRightElbow::Update(float _deltaTime)
{
	SetPosition(mPosition.mX, mPosition.mY, mPosition.mZ - mSpeed * _deltaTime);
	Move(mPosition.mX, mPosition.mY, mPosition.mZ);
	UpdateColliders();
}

void TilesRightElbow::Move(float _x, float _y, float _z)
{
	squareRightSide->SetPosition({ _x + THIRD_SQUARES_SIZE,_y,_z });
	squareFrontSide->SetPosition({ _x - ONE_SIXTH_SQUARES_SIZE,_y,_z + OFFSET_BOTTOM_SQUARE_POSITION_Z });
	
}

bool TilesRightElbow::IsCharacterAbove(float _characterX, float _characterZ)
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
            return true;
    }
    return false;
}

void TilesRightElbow::UpdateColliders()
{
    mColliders.clear();
    // collider front
    float halfWidthFront = TWO_THIRD_SQUARES_SIZE / 2.f;
    float halfDepthFront = HALF_DEPTH_SIZE / 2.f;
    auto posFront = squareFrontSide->GetPosition();
    AddCollider({
        { posFront.x - halfWidthFront, posFront.y, posFront.z - halfDepthFront },
        { posFront.x + halfWidthFront, posFront.y, posFront.z - halfDepthFront },
        { posFront.x - halfWidthFront, posFront.y, posFront.z + halfDepthFront },
        { posFront.x + halfWidthFront, posFront.y, posFront.z + halfDepthFront }
        });

    // collider right
    float halfWidthRight = THIRD_SQUARES_SIZE / 2.f;
    float halfDepthRight = TILE_DEPTH_SIZE / 2.f;
    auto posRight = squareRightSide->GetPosition();
    AddCollider({
        { posRight.x - halfWidthRight, posRight.y, posRight.z - halfDepthRight },
        { posRight.x + halfWidthRight, posRight.y, posRight.z - halfDepthRight },
        { posRight.x - halfWidthRight, posRight.y, posRight.z + halfDepthRight },
        { posRight.x + halfWidthRight, posRight.y, posRight.z + halfDepthRight }
        });
}
