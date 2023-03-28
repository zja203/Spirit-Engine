workspace "Spirit"
	architecture "x86_64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

	flags {
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SpiritEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	pchheader "include/Spirit/sprtpch.hpp"
	pchsource "src/sprtpch.cpp"

	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.cpp",
		"include/**.hpp",
		"vendor/**"
	}

	includedirs {
		"include",
		"vendor/include"
	}

	filter "system:windows"
		systemversion "10.0.19041.0"

		defines {
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		systemversion "latest"

	filter { "system:windows", "configurations:Debug" }
		buildoptions "/MDd"

	filter { "system:linux", "configurations:Debug" }
		buildoptions "-ggdb"

	filter { "configurations:Debug" }
		runtime "Debug"
		symbols "on"
		optimize "off"
		defines {
			"SPRT_DEBUG",
			"SPRT_ENABLE_ASSERTS"
		}

	filter { "configurations:Release" }
		runtime "Release"
		optimize "on"
		symbols "on"
		defines {
			"SPRT_RELEASE",
			"SPRT_ENABLE_ASSERTS"
		}

	filter { "configurations:Distribution" }
		runtime "Release"
		optimize "on"
		symbols "off"
		defines "SPRT_DISTRIBUTION"

include "testapp"
