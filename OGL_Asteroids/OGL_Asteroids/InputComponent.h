#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:

	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxAngularSpeed() { return mMaxAngularSpeed; }
	float GetMaxForwardSpeed() { return mMaxForwardSpeed; }
	int GetForwardKey() { return mForwardKey; }
	int GetBackKey() { return mBackKey; }
	int GetClockwiseKey() { return mClockwiseKey; }
	int GetCounterClockwiseKey() { return mCounterClockwiseKey; }

	void SetMaxForwardSpeed(float maxForwardSpeed) { mMaxForwardSpeed = maxForwardSpeed; }
	void SetMaxAngularSpeed(float MaxAngularSpeed) { mMaxAngularSpeed = MaxAngularSpeed; }
	void SetForwardKey(int forwardKey) { mForwardKey = forwardKey; }
	void SetBackKey(int backKey) { mBackKey = backKey; }
	void SetClockwiseKey(int clockwiseKey) { mClockwiseKey = clockwiseKey; }
	void SetCounterClockwiseKey(int counterClockwiseKey) { mCounterClockwiseKey = counterClockwiseKey; }

private:

	// The maximum forward/angular speeds
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	//Keys for forward/back movement
	int mForwardKey;
	int mBackKey;

	//Keys for angular movement
	int mClockwiseKey;
	int mCounterClockwiseKey;

};