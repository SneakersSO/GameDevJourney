#pragma once
#include "Component.h"
#include <unordered_map>
#include <string.h>


class AIComponent : public Component
{
public:

	AIComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

};