#include "Actor.h"

class Skeleton : public Actor 
{
public:

	//Used to track animation state of the skeleton
	enum AnimState
	{
		EWalking,
		EJumping,
		EPunching
	};

	Skeleton(class Game* game);

	void UpdateActor(float deltaTime) override;

	void ProcessKeyboard(const uint8_t* state);

	float GetRightSpeed() const { return mRightSpeed; }

	float GetDownSpeed() const { return mDownSpeed; }

	AnimState GetAnimState() const { return mAnimState; }
	void SetAnimState(AnimState state) { mAnimState = state; }



private:
	float mRightSpeed;
	float mDownSpeed;
	float mJumpHeight;
	AnimState mAnimState;
	std::string mResetAnim;
	class AnimSpriteComponent* mAsc;
};