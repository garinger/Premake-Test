-- Currently, the project struct has the following layout:
--  bin
--  build
--  lib
--  src
--  premake5.lua

src_path = "%{os.getcwd()}/src"
lib_path = "%{os.getcwd()}/lib"
include_path = "%{os.getcwd()}/include"

workspace "Premake Test"
   configurations { "Debug", "Release" }
   location "build"

project "Premake Test"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files {
      src_path.."/**.cpp",
      src_path.."/**.h",
      lib_path.."/glad/src/glad.c",
      lib_path.."/imgui/src/*.cpp",
   }

   includedirs {
    lib_path.."/**"
   }

   libdirs {
    lib_path.."/**"
   }

   links {
      "SDL2",
      "SDL2main"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      symbols "Off"

   -- Set the target architecture to x64 for Windows
   filter "system:windows"
      architecture "x86_64"

   postbuildcommands {
      '{COPYFILE} "%{lib_path}/SDL2/lib/SDL2.dll" "%{cfg.buildtarget.directory}"'
   }