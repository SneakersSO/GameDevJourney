#include "Ship.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Math.h"
#include "InputComponent.h"
#include "CircleComponent.h"
#include "Laser.h"
#include "Asteroid.h"

Ship::Ship(Game* game)
	:Actor(game)
	,mLaserCooldown(0.5f)
{
	sc = new SpriteComponent(this, 150);

	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	InputComponent* ip = new InputComponent(this);

	ip->SetMaxForwardSpeed(300.0f);
	ip->SetMaxAngularSpeed(Math::TwoPi);

	ip->SetForwardKey(SDL_SCANCODE_W);
	ip->SetBackKey(SDL_SCANCODE_S);
	ip->SetClockwiseKey(SDL_SCANCODE_D);
	ip->SetCounterClockwiseKey(SDL_SCANCODE_A);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(42.0f);

	ip->SetMass(250.f);

}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;

	//Does the ship collide with a asteroid?
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			SetState(EDead);
		}
	}
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		//Create a laser and set its position/rotation to mine
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRot(GetRot());

		// Reset laser cooldown (half second)
		mLaserCooldown = 0.5f;
	}
}
