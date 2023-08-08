workspace "Glacier" -- 솔루션
	architecture "x64" -- 우리가 다루는 솔루션 플랫폼

	configurations -- 솔루션 설정
	{
		"Debug",   -- 개발 시 사용하는 디버그 모드.
		"Release", -- Release mode 뿐만아니라 Debug에 최적화를 더한 모드.
		"Dist"     -- Distribution(배포) 빌드. 로깅을 전혀 하지 않음.
	}
--     buildcfg : Debug/Release  system : Win/Mac등. architecture : x86/x64등.
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {} -- include 디렉터리들을 담은 구조체를 만들어줌.

project "Glacier"      -- Glacier 프로젝트
	location "Glacier" -- Glacier 솔루션(worksapce) 내 Glacier 폴더 내에 Glacier 프로젝트가 위치함.
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")  -- 출력 디렉터리
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}") -- intermediate 디렉터리

	pchheader "pch.h"
	pchsource "Glacier/src/pch.cpp"

	files -- 프로젝트에 추가할 파일들.
	{	-- ** : 해당 폴더 부터 재귀적으로 하위 폴더를 탐색함.
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/resources/shaders/**.hlsl",
		"%{prj.name}/vendor/directxtk/**.h",
		"%{prj.name}/vendor/directxtk/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs -- Additional Include Directories
	{
	    "%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/directxtk"
	}
	
	libdirs 
	{ 
		"%{prj.name}/vendor/directxtk"
	}
	
	links
	{ 
		"d3d11.lib",
		"d3dcompiler.lib",
		"dxguid.lib",
		"DirectXTK.lib"
	}
	
	shadermodel ("5.0")
	shaderobjectfileoutput "resources/shaders/outputs/%%(Filename).cso"

	-- 특정 플랫폼에 대한 특정 프로젝트 설정(configurations)시 사용. 조건문과 비슷. 윈도우 플랫폼에서만 아래 설정들을 적용함.
	filter "system:windows"
		systemversion "latest" -- Windows SDK version

		defines -- 전처리기 정의
		{
			"GR_PLATFORM_WINDOWS",
			"GR_BUILD_DLL"
		}

	filter "configurations:Debug" -- Debug 설정일 때.
		defines "GR_DEBUG"        -- Debug 모드일 때 사용할 전처리 정의문.
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GR_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"      -- Sandbox 프로젝트
	location "Sandbox"
	kind "ConsoleApp"  -- Project Configuration Type : Application(exe)
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	-- 출력 디렉터리
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	-- intermediate 디렉터리

	files
	{	-- ** : 해당 폴더 부터 재귀적으로 하위 폴더를 탐색함.
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs -- Additional Include Directories
	{
		"Glacier/src",
		"Glacier/vendor/spdlog/include",
		"Glacier/vendor/imgui",
		"Glacier/vendor/directxtk"
	}

	links -- 프로젝트 참조
	{
		"Glacier"
	}

	-- 특정 플랫폼에 대한 특정 프로젝트 설정(configurations)시 사용. 조건문과 비슷.
	filter "system:windows"
		cppdialect "C++17"     -- C++ version
		staticruntime "On"     -- runtime library와 연결
		systemversion "latest" -- Windows SDK version

		defines -- 전처리기 정의
		{
			"GR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GR_DIST"
		runtime "Release"
		optimize "on"

-- 프로젝트 경로에 빈칸이 포함되어 있는 이름이 있으면 오류가 발생 했음. 
-- https://stackoverflow.com/questions/19914339/error-msb3073-how-do-i-fix-this