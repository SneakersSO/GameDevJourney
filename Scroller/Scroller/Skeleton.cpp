
#include "Game.h"
#include "Skeleton.h"
#include "AnimSpriteComponent.h"

Skeleton::Skeleton(Game* game)
	:Actor(game)
	,mRightSpeed(0.0f)
	,mDownSpeed(0.0f)
	,mJumpHeight(0.0f)
{
	mAsc = new AnimSpriteComponent(this);

	Anim walking;
	walking.bIsLooping = true;
	walking.animTextures = {
		game->GetTexture("Assets/Character01.png"),
		game->GetTexture("Assets/Character02.png"),
		game->GetTexture("Assets/Character03.png"),
		game->GetTexture("Assets/Character04.png"),
		game->GetTexture("Assets/Character05.png"),
		game->GetTexture("Assets/Character06.png"),
	};
	mAsc->SetAnimTextures("walking", walking);
	mAsc->SetResetAnim("walking");

	Anim jumping;
	jumping.bIsLooping = false;
	jumping.animTextures = {
		game->GetTexture("Assets/Character07.png"),
		game->GetTexture("Assets/Character08.png"),
		game->GetTexture("Assets/Character09.png"),
		game->GetTexture("Assets/Character10.png"),
		game->GetTexture("Assets/Character11.png"),
		game->GetTexture("Assets/Character12.png"),
		game->GetTexture("Assets/Character13.png"),
		game->GetTexture("Assets/Character14.png"),
		game->GetTexture("Assets/Character15.png"),
	};
	mAsc->SetAnimTextures("jumping", jumping);

	Anim punching;
	punching.bIsLooping = false;
	punching.animTextures = {
		game->GetTexture("Assets/Character16.png"),
		game->GetTexture("Assets/Character17.png"),
		game->GetTexture("Assets/Character18.png"),
	};
	mAsc->SetAnimTextures("punching", punching);

	mAsc->SetActiveAnim("walking");
	mAnimState = EWalking;
}

void Skeleton::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	//Update position based on speeds and delta time
	Vector2 pos = GetPosition();

	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	//Restrict position to left half of screen

	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}

	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}

	SetPosition(pos);
}

void Skeleton::ProcessKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;

	// right/left
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}

	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}

	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}

	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		SetAnimState(EJumping);
		mAsc->SetActiveAnim("jumping");
	}

	if (state[SDL_SCANCODE_J])
	{
		SetAnimState(EPunching);
		mAsc->SetActiveAnim("punching");
	}
}
