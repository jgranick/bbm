BBM
===

Beginning the process of a native extension for BlackBerry, to support BBM with NME.

You might not be familiar with native extensions for NME. The basic idea is that you can take function C/C++ code, then create bindings so Haxe classes can access this functionality.

To help the compile process, HXCPP (the standard library that supports Haxe/C++ builds) includes a build tool. This will handle all calls to the compiler. Under the "project" directory there is a "Build.xml" file. This is given to HXCPP to compile the native code that is contained here. Open a terminal or command prompt, go to the project directory, then run "haxelib run hxcpp Build.xml -Dblackberry" in order to compile it for BlackBerry.

HXCPP will automatically use the BLACKBERRY_NDK_ROOT variable found in ".hxcpp_config.xml" from your user directory (C:\Users\your-name, /home/your-name, etc) when building for BlackBerry. This is the variable NME sets when you run "nme setup blackberry" and provide the path to your BlackBerry Native SDK directory. Since BBM is not available in older versions of the Native SDK, make certain that you are pointing to a current SDK when building.

Originally I began work on this project using a sample from http://developer.blackberry.com, using an older (beta) BlackBerry 10 SDK. Using the current gold SDK, there appear to be some compile errors under "project/BBM.cpp" ... and of course for this to be fully operational, work will need to be done to expose all required functionality, anyway.

The native code is structured so "project/ExternalInterface.cpp" handles the CFFI bindings that allow Haxe to access the native functions. This is by convention, but is not strictly required for an NME extension. You'll find there is one method exposed there, right now. the DEFINE_PRIM macro is what exposes a C++ method for Haxe. "DEFINE_PRIM (bbm_initialize, 1);" exposes the method so Haxe can use it. If you look at "blackberry/BBM.hx" you can see the Haxe code which makes this function available on the other side.

When a compile succeeds, it should write a shared library file under "ndll/BlackBerry/bbm.so"

The only requirement for an NME native extension is "include.nmml", which you'll find at the root of this project. NME picks up this file automatically when a project is being loaded from haxelib. In there you'll see that it tells NME there is a native library called "bbm" that we want the command-line tools to include in the project. That way, when you build and deploy to the device, and BBM.hx tries to access "bbm.so", it will be present.

Working locally, you can also use <include path="to/your/bbm/dev/directory" /> in order for NME to have the same behavior.

Ordinarily, all of this works fine using NME 3.4.4, but BBM and some other BlackBerry system APIs are a little bit special... instead of working in full isolation, they need to be hooked into the event loop of your project in order to receive the required system messages.

NME 3.4.4 does not make it possible to hook into the event loop, but NME 3.5.0 was just released, and exposes this functionality. Under "project/BBM.cpp" you may see the call, "nme_register_bps_event_handler". This method exists in the development builds of NME to allow BlackBerry-specific native extensions to register a handler to receive these events.

I believe NME may be currently hard-coded to only allow one handler. A little help to make that allow lists of handlers would be great.

