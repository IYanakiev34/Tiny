workspace "Tiny"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "TinySandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Tiny/vendor/GLFW"
include "Tiny/vendor/GLAD"
include "Tiny/vendor/ImGui"

project "Tiny"
	location "Tiny"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "TNpch.h"
	pchsource "Tiny/src/TNpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/GLAD/include",
		"%{prj.name}/vendor/ImGui",
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"GLAD",
		"ImGui",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines{
			"TN_WINDOWS_PLATFORM",
			"TINY_BUILD_DLL",
			"TN_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/TinySandbox")
		}

	filter "configurations:Debug"
		defines "TN_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "TN_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "TN_DIST"
		buildoptions "/MD"
		optimize "On"


project "TinySandbox"
	location "TinySandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{wks.location}/Tiny/vendor/spdlog/include",
		"Tiny/src"
	}

	links{
		"Tiny"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TN_WINDOWS_PLATFORM"
		}

	filter "configurations:Debug"
		defines "TN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "TN_DIST"
		optimize "On"
