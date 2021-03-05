#include "SpriteComponent.h"
#include <vector>
#include <unordered_map>
#include <string>

struct Anim {
	bool bIsLooping;
	std::vector<SDL_Texture*> animTextures;
};


class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

	//Update animation every frame (overriden from component)
	void Update(float deltaTime) override;

	//Set the textures used for animation
	void SetAnimTextures(std::string animName, Anim animData);

	void SetActiveAnim(std::string animName);

	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }

	void SetAnimFPS(float fps) { mAnimFPS = fps; }

	void SetCurrentAnim(Anim anim) { mCurrentAnim = anim; }
	Anim GetCurrentAnim() { return mCurrentAnim; }

	void SetResetAnim(std::string resetAnim) { mResetAnim = resetAnim; }
	std::string GetResetAnim() { return mResetAnim; }


private:
	// All textures in the animation
	std::vector<SDL_Texture*> mAnimTextures;

	// All animations for the component
	std::unordered_map<std::string, Anim> mAnims;

	Anim mCurrentAnim;

	std::string mResetAnim;

	//Current frame displayed
	float mCurrFrame;

	//Animation frame rate
	float mAnimFPS;

};