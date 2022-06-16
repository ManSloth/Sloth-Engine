workspace "Sloth"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Sloth/vendor/GLFW/include"
IncludeDir["Glad"] = "Sloth/vendor/Glad/include"
IncludeDir["ImGui"] = "Sloth/vendor/imgui"
IncludeDir["glm"] = "Sloth/vendor/glm"
IncludeDir["stb_image"] = "Sloth/vendor/stb_image"

include "Sloth/vendor/GLFW"
include "Sloth/vendor/Glad"
include "Sloth/vendor/imgui"

group ""

project "Sloth"
	location "Sloth"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "slthpch.h"
	pchsource "Sloth/src/slthpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SLTH_PLATFORM_WINDOWS",
			"SLTH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	
		filter "configurations:Debug"
			defines "SLTH_DEBUG"
			buildoptions "/MDd"
			symbols "on"

		filter "configurations:Release"
			defines "SLTH_Release"
			buildoptions "/MD"
			optimize "on"

		filter "configurations:Dist"
			defines "SLTH_DIST"
			buildoptions "/MD"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Sloth/vendor/spdlog/include", 
		"Sloth/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Sloth"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SLTH_PLATFORM_WINDOWS"
		}
	
		filter "configurations:Debug"
			defines "SLTH_DEBUG"
			buildoptions "/MDd"
			symbols "on"

		filter "configurations:Release"
			defines "SLTH_Release"
			buildoptions "/MD"
			optimize "on"

		filter "configurations:Dist"
			defines "SLTH_DIST"
			buildoptions "/MD"
			optimize "on"