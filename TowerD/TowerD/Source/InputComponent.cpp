#include "InputComponent.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
{

}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// Calculate forward speed for MoveComponent
	float forwardSpeed = 0.0f;

	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}

	if (keyState[mBackKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}

	SetForwardSpeed(forwardSpeed);

	//Calculate angular speed for MoveComponent
	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}

	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}

	SetAngularSpeed(angularSpeed);
}