#include "slthpch.h"
#include "Sloth/Core/Input.h"

#ifdef SLTH_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Sloth {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef SLTH_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		SLTH_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}