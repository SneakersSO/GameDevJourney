#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:

	//Used to track state of actor
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	//Constructor/desctructor
	Actor(class Game* game);

	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);

	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);

	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	State GetState() { return mState; };
	void SetState(State state) { mState = state; }

	const Vector2& GetPosition() { return mPosition; };
	void SetPosition(const Vector2& pos) { mPosition = pos; }

	float GetScale() { return mScale; };
	void SetScale(float scale) { mScale = scale; }

	float GetRot() { return mRotation; };
	void SetRot(float rotation) { mRotation = rotation; }
	Game* GetGame() { return mGame; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	std::vector<class Component*> GetComponents() { return mComponents; };


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	void ProcessInput(const uint8_t* keyState);

	virtual void ActorInput(const uint8_t* keyState);

private:

	// Actor's state
	State mState;

	// Transform
	Vector2 mPosition;	// Center position of actor

	float mScale;		// Uniforms scale of actor (1.0f for 100%)

	float mRotation;	// Rotation angle (in radians)

	// Components held by this actor

	std::vector<class Component*> mComponents;

	class Game* mGame;
};
