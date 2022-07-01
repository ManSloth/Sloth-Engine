#pragma once

#include "Sloth/Core/Base.h"
#include "Sloth/Core/KeyCodes.h"
#include "Sloth/Core/MouseCodes.h"

namespace Sloth {
	
	class SLOTH_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}