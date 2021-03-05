#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,mCurrFrame(0.0f)
	,mAnimFPS(24.0f)
{

}

void AnimSpriteComponent::SetAnimTextures(const std::string animName, const Anim animData)
{
	mAnims.emplace(animName, animData);
}


void AnimSpriteComponent::SetActiveAnim(std::string animName)
{
	auto iter = mAnims.find(animName);

	if (iter != mAnims.end())
	{
		mAnimTextures = iter->second.animTextures;

		if (mAnimTextures.size() > 0)
		{
			mCurrFrame = 0.0f;
			SetTexture(mAnimTextures[0]);
			SetCurrentAnim(iter->second);
		}
	}
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		if (GetCurrentAnim().bIsLooping)
		{
			// Wrap current frame if needed
			while (mCurrFrame >= mAnimTextures.size())
			{
				mCurrFrame -= mAnimTextures.size();
			}

			// Set the current texture
			SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);

		}

		else if (!GetCurrentAnim().bIsLooping && mCurrFrame >= mAnimTextures.size())
		{
			SetActiveAnim(mResetAnim);
		}

		else
		{
			SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
		}

	}
}
