solution "TravisCITest"
	configurations { "Debug", "Release" }
	configuration "Debug"
		defines { "_DEBUG" }
		flags { "Symbols" }
	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
	configuration {}
	platforms { "x64" }
			
	language "C++"
	flags { "NoMinimalRebuild", "EnableSSE", "EnableSSE2" }
		
	configuration {"x64", "Debug"}
		targetsuffix "64D"
	configuration {"x64", "Release"}
		targetsuffix "64"
	configuration {}

	includedirs{ "./include" }
	
	configuration {}
	project "UnitTest"
		kind "ConsoleApp"
		location "../UnitTest"
		targetdir "./build"
		
		files { "./UnitTest/*.cpp", "./gtest-1.6.0/**" } 
			
		if os.is("linux") then
			links { "pthread" }
			links {"OpenCL"}
		end
		if _ACTION == "vs2012" then
			defines{ "GTEST_HAS_TR1_TUPLE=0" }
		end
		
		if os.is("macosx") then
		   linkoptions{ "-framework OpenCL" }
			buildoptions{"-DGTEST_USE_OWN_TR1_TUPLE=1"}
		end

		configuration {}
				


