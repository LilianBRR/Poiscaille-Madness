#include "pch.h"
#include "Bonus.h"

void Bonus::SetPosition(float _x, float _y, float _z)
{
	mPosition = { _x, _y, _z };
};

void Bonus::AddGeometry(Geometry* _geometry)
{
	mGeometries.push_back(_geometry);
}
