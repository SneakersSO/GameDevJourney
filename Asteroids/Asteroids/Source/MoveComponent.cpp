#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mAngularSpeed(0.0f)
	,mForwardSpeed(0.0f)
	,mVelocity(Vector2::Zero)
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRot();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRot(rot);

	}

	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 force = mOwner->GetForward();
		Vector2 acc;
		acc.x = force.x / mMass;
		acc.y = force.y / mMass;
		acc.x = mVelocity.x / deltaTime;
		acc.y = mVelocity.y / deltaTime;
		mVelocity += acc * deltaTime;

		Vector2 pos = mOwner->GetPosition();

		pos += mVelocity * deltaTime;
		mOwner->SetPosition(pos);
	}
}