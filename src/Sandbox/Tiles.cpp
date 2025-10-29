#include "pch.h"
#include "Tiles.h"

void Tiles::AddGeometry(Geometry* _geometry)
{
	mGeometries.push_back(_geometry);
}

void Tiles::SetSpeed(float _speed)
{
	mSpeed = _speed;
}

void Tiles::SetGroundTexture(Texture* _texture)
{
	mGroundTexture = _texture;
}

void Tiles::SetPosition(float _x, float _y, float _z)
{
	mPosition = { _x, _y, _z };
}


Vector3_Tiles Tiles::GetPosition()
{
	return mPosition;
}

