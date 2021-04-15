#pragma once
#include "MoveComponent.h"
#include "Math.h"

class NavComponent : public MoveComponent 
{

public:
	// Lower update order to update first
	NavComponent(class Actor* owner, int updateOrder = 10);
	void TurnTo(const Vector2& pos);
	void Update(float deltaTime) override;
	void StartPath(const class Tile* start);

private:
	class Tile* mNextNode;
};
