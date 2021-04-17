#include "Laser.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Asteroid.h"
#include "Game.h"

Laser::Laser(Game* game)
	:Actor(game)
	, mDeathTimer(1.0f)
	, mLifeTime(.68f)
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	//Create a move component and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	// Create a circle component for collision
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{

	// Do you intersect with an asteroid?
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			//If this laser intersects with an asteroid,
			// set ourselves and the asteroid to dead
			SetState(EDead);
			ast->SetState(EDead);
			break;
		}
	}

	mLifeTime -= deltaTime;

	if (mLifeTime <= 0.0f)
	{
		SetState(EDead);
	}
}