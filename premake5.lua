workspace "Sloth"
	architecture "x64"

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

include "Sloth/vendor/GLFW"
include "Sloth/vendor/Glad"
include "Sloth/vendor/imgui"

project "Sloth"
	location "Sloth"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "slthpch.h"
	pchsource "Sloth/src/slthpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SLTH_PLATFORM_WINDOWS",
			"SLTH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
		filter "configurations:Debug"
			defines "SLTH_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "SLTH_Release"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "SLTH_DIST"
			buildoptions "/MD"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Sloth/src"
	}

	links
	{
		"Sloth"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SLTH_PLATFORM_WINDOWS"
		}
	
		filter "configurations:Debug"
			defines "SLTH_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "SLTH_Release"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "SLTH_DIST"
			buildoptions "/MD"
			optimize "On"