#pragma once
#include <vector>
#include <algorithm>

struct Vector3_Tiles
{
	float mX, mY, mZ;

	Vector3_Tiles() : mX(0), mY(0), mZ(0) {}
	Vector3_Tiles(float x, float y, float z) : mX(x), mY(y), mZ(z) {}

	// constructeur de conversion
	Vector3_Tiles(const gce::Vector3f32& v) : mX(v.x), mY(v.y), mZ(v.z) {}
};

struct Vector3_Tiles_Collider
{
	float mX, mY, mZ;

	Vector3_Tiles_Collider() : mX(0), mY(0), mZ(0) {}
	Vector3_Tiles_Collider(float x, float y, float z) : mX(x), mY(y), mZ(z) {}

};

struct ColliderBox
{
	Vector3_Tiles_Collider bottomLeft;
	Vector3_Tiles_Collider bottomRight;
	Vector3_Tiles_Collider topLeft;
	Vector3_Tiles_Collider topRight;

	ColliderBox() = default;
	ColliderBox(Vector3_Tiles_Collider bl, Vector3_Tiles_Collider br,
		Vector3_Tiles_Collider tl, Vector3_Tiles_Collider tr)
		: bottomLeft(bl), bottomRight(br), topLeft(tl), topRight(tr) {
	}
};

class Tiles
{
	
protected :
	float mSpeed = 20.f;
	std::vector<Geometry*> mGeometries;
	Vector3_Tiles mPosition;
	std::vector<ColliderBox> mColliders;
	
	Texture* mGroundTexture;

public :
	Tiles() = default;
	~Tiles() = default;

	virtual void Init() = 0;
	virtual void Update(float _deltaTime) = 0;
	virtual void Move(float _x, float _y, float _z) = 0;

	void SetPosition(float _x, float _y, float _z);
	Vector3_Tiles GetPosition();

	void AddGeometry(Geometry* _geometry);
	std::vector<Geometry*> GetGeometries() { return mGeometries; }

	void AddCollider(const ColliderBox& collider) { mColliders.push_back(collider); }
	const std::vector<ColliderBox>& GetColliders() const { return mColliders; }

	virtual void UpdateColliders() = 0;

	void SetSpeed(float _speed);
	float GetSpeed() { return mSpeed; }

	virtual bool IsCharacterAbove(float _characterX, float _characterZ) = 0;

	void SetGroundTexture(Texture* _texture);

};

