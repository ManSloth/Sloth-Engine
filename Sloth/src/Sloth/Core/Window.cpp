#include "slthpch.h"
#include "Sloth/Core/Window.h"

#ifdef SLTH_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Sloth
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef SLTH_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		SLTH_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}