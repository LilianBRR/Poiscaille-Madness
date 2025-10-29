#include "pch.h"
#include "TilesSquare.h"

void TilesSquare::Init()
{
	SetPosition(TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, TILES_SPAWN_POSITION_Z);

    // === Carré principal ===
	square = new Cube();
	//square->SetTexture(*mGroundTexture);
	square->SetColor(TILES_COLOR);
	square->SetScale({ TILES_SQUARES_SIZE, TILES_SQUARES_HEIGHT, TILE_DEPTH_SIZE });
	square->SetPosition({ TILES_SPAWN_POSITION_X, TILES_SPAWN_POSITION_Y, TILES_SPAWN_POSITION_Z });
	AddGeometry(square);

	float halfWidth = TILES_SQUARES_SIZE / 2.f;
	float halfDepth = TILE_DEPTH_SIZE / 2.f;
	Vector3_Tiles pos = square->GetPosition();

	AddCollider({
		{ pos.mX - halfWidth, pos.mY, pos.mZ - halfDepth },
		{ pos.mX + halfWidth, pos.mY, pos.mZ - halfDepth },
		{ pos.mX - halfWidth, pos.mY, pos.mZ + halfDepth },
		{ pos.mX + halfWidth, pos.mY, pos.mZ + halfDepth }
		});
}

void TilesSquare::Update(float _deltaTime)
{
	SetPosition(mPosition.mX, mPosition.mY, mPosition.mZ - mSpeed * _deltaTime);
	Move(mPosition.mX, mPosition.mY, mPosition.mZ);
	UpdateColliders();
}

void TilesSquare::Move(float _x, float _y, float _z)
{
	square->SetPosition({ _x,_y,_z });
}

bool TilesSquare::IsCharacterAbove(float _characterX, float _characterZ)
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

void TilesSquare::UpdateColliders()
{
    mColliders.clear();
    float halfWidth = TILES_SQUARES_SIZE / 2.f;
    float halfDepth = TILE_DEPTH_SIZE / 2.f;
    Vector3_Tiles pos = square->GetPosition();

    AddCollider({
        { pos.mX - halfWidth, pos.mY, pos.mZ - halfDepth },
        { pos.mX + halfWidth, pos.mY, pos.mZ - halfDepth },
        { pos.mX - halfWidth, pos.mY, pos.mZ + halfDepth },
        { pos.mX + halfWidth, pos.mY, pos.mZ + halfDepth }
        });
}
