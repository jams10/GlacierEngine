workspace "Glacier" -- �ַ��
	architecture "x64" -- �츮�� �ٷ�� �ַ�� �÷���

	configurations -- �ַ�� ����
	{
		"Debug",   -- ���� �� ����ϴ� ����� ���.
		"Release", -- Release mode �Ӹ��ƴ϶� Debug�� ����ȭ�� ���� ���.
		"Dist"     -- Distribution(����) ����. �α��� ���� ���� ����.
	}
--     buildcfg : Debug/Release  system : Win/Mac��. architecture : x86/x64��.
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {} -- include ���͸����� ���� ����ü�� �������.

project "Glacier"      -- Glacier ������Ʈ
	location "Glacier" -- Glacier �ַ��(worksapce) �� Glacier ���� ���� Glacier ������Ʈ�� ��ġ��.
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")  -- ��� ���͸�
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}") -- intermediate ���͸�

	pchheader "pch.h"
	pchsource "Glacier/src/pch.cpp"

	files -- ������Ʈ�� �߰��� ���ϵ�.
	{	-- ** : �ش� ���� ���� ��������� ���� ������ Ž����.
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

	-- Ư�� �÷����� ���� Ư�� ������Ʈ ����(configurations)�� ���. ���ǹ��� ���. ������ �÷��������� �Ʒ� �������� ������.
	filter "system:windows"
		systemversion "latest" -- Windows SDK version

		defines -- ��ó���� ����
		{
			"GR_PLATFORM_WINDOWS",
			"GR_BUILD_DLL"
		}

	filter "configurations:Debug" -- Debug ������ ��.
		defines "GR_DEBUG"        -- Debug ����� �� ����� ��ó�� ���ǹ�.
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

project "Sandbox"      -- Sandbox ������Ʈ
	location "Sandbox"
	kind "ConsoleApp"  -- Project Configuration Type : Application(exe)
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	-- ��� ���͸�
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	-- intermediate ���͸�

	files
	{	-- ** : �ش� ���� ���� ��������� ���� ������ Ž����.
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

	links -- ������Ʈ ����
	{
		"Glacier"
	}

	-- Ư�� �÷����� ���� Ư�� ������Ʈ ����(configurations)�� ���. ���ǹ��� ���.
	filter "system:windows"
		cppdialect "C++17"     -- C++ version
		staticruntime "On"     -- runtime library�� ����
		systemversion "latest" -- Windows SDK version

		defines -- ��ó���� ����
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

-- ������Ʈ ��ο� ��ĭ�� ���ԵǾ� �ִ� �̸��� ������ ������ �߻� ����. 
-- https://stackoverflow.com/questions/19914339/error-msb3073-how-do-i-fix-this