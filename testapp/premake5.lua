project "TestApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	links {
		"SpiritEngine"
	}

	files {
		"include/**.hpp",
		"src/**.cpp",
	}

	includedirs {
		"include",
		"%{wks.location}/include",
		"%{wks.location}",
		"%{wks.location}/vendor/include"
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
