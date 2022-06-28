#pragma once

#include "Sloth/Core/Input.h"

namespace Sloth {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

		
	};
}