--[[
	INSTRUCTIONS TO BUILD & LINK ON LINUX (DEBIAN SPECIFICALLY)
	1) dpkg --add-architecture i386
	2) apt-get update
	3) apt-get install build-essential gcc-multilib rpm libstdc++6:i386 libgcc1:i386 zlib1g:i386 libncurses5:i386 libmariadbclient-dev libmariadbclient-dev:i386
	3.extra) If needed: apt install libmariadb libmariadb:i386
	4) Generate gmake files with premake: premake gmake
	5) make config=[release/release32]
--]]

workspace "VCMPPython"
	architecture "x86_64"
	startproject "PythonPlugin"

	targetname "%{prj.name}"
	targetprefix "" -- Disable prefix
	targetsuffix "_x64" -- Default architecture

	pic "On" -- position independent code enabled for every project
	
	configurations
	{
		-- Debug configurations are not used
		-- "Debug32",
		-- "Debug",
		"Release32",
		"Release"
	}

	filter "configurations:*32"
		architecture "x86"
		targetsuffix "_x86"
		defines {"_x32"}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release*"
		runtime "Release"
		optimize "on"

	flags { "MultiProcessorCompile"	}
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

filter {}

-- Vendors
include "../vendor/pybind11"
include "vendor/simpleini"