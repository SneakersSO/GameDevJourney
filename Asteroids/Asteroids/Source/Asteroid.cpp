#include "Asteroid.h"
#include "Math.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"

Asteroid::Asteroid(class Game* game)
	:Actor(game)
{
	// Initialize to random position/orientation

	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));

	SetPosition(randPos);

	SetRot(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component, and set texture

	SpriteComponent* sc = new SpriteComponent(this);

	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	// Create a move component, and set a forward speed

	MoveComponent* mc = new MoveComponent(this);

	mc->SetForwardSpeed(150.0f);

	// Create a circle component & set radius
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}