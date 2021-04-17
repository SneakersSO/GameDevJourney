#pragma once
#include "Component.h"
#include "Math.h"
#include <vector>

class MoveComponent : public Component
{
public:
	//Lower update order to update first
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }

	float GetForwardSpeed() const { return mForwardSpeed; }

	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }

	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

	float GetMass() { return mMass; }
	void SetMass(float mass) { mMass = mass; }

private:
	// Controls rotations (radians/second)

	float mAngularSpeed;

	// Controls forward movement (units/second)

	float mForwardSpeed;

	float mMass;
	Vector2 mVelocity;

};


