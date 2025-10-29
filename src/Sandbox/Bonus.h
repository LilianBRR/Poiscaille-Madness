#pragma once


struct Vector3_Bonus
{
	float mX, mY, mZ;

	Vector3_Bonus() : mX(0), mY(0), mZ(0) {}
	Vector3_Bonus(float x, float y, float z) : mX(x), mY(y), mZ(z) {}

	Vector3_Bonus(const gce::Vector3f32& v) : mX(v.x), mY(v.y), mZ(v.z) {}
};

struct Vector3_Bonus_Collider
{
	float mX, mY, mZ;

	Vector3_Bonus_Collider() : mX(0), mY(0), mZ(0) {}
	Vector3_Bonus_Collider(float x, float y, float z) : mX(x), mY(y), mZ(z) {}

	Vector3_Bonus_Collider(const gce::Vector3f32& v) : mX(v.x), mY(v.y), mZ(v.z) {}
};

struct ColliderBoxBonus
{

	Vector3_Bonus_Collider mPositionCollider;
	float mRadius;
	ColliderBoxBonus() = default;
	ColliderBoxBonus(Vector3_Bonus_Collider _position, float _radius)
	{
		mPositionCollider = _position;
		mRadius = _radius;
	}

};
class Bonus
{
	std::vector<Geometry*> mGeometries;
	

protected:
	Vector3_Bonus mPosition;
	ColliderBoxBonus mCollider;
	Capsule* mBonusGeometry;
	float mSpeedMove = 20.f;
	float mSpeedRotation = 250.f;
	float mCurrentRotationY = 0.f;
	bool mToDestroy = false;

	int mTag;
public :

	Bonus() = default;
	~Bonus() = default;

	virtual void Init() = 0;
	virtual void Update(float _deltaTime) = 0;
	virtual void Move(float _posX, float _posY, float _posZ) = 0;

	void SetPosition(float _x, float _y, float _z);
	Vector3_Bonus GetPosition() { return mPosition; }

	void AddGeometry(Geometry* _geometry);
	std::vector<Geometry*> GetGeometries() { return mGeometries; }

	ColliderBoxBonus GetColliders() const { return mCollider; }

	void SetTag(int _tag) { mTag = _tag; }
	int GetTag() { return mTag; }

	void SetSpeed(float _newSpeed) { mSpeedMove = _newSpeed; };

	void SetIsToDestroy() { mToDestroy = true; }
	bool GetIsToDestroy() { return mToDestroy; }
	virtual bool IsCollideCharacter(float _characterX, float _characterY, float _characterZ) = 0;
	//virtual void UpdateColliders() = 0;

};

