# Hades - An andvanced and complete anti-debug library for your Windows x64 C++ project

## Usage
- Easy to use.
- Detect most of the debugging types (usermode only).
- Detect all usermode debugger-hide tools and any attempt to hide the presence of debugger.
- Get access to undocumented kernel functions and bypass usermode hooks (limited).
- Call Windows API functions safely: Bypass IAT (import address table) manipulation and other usermode hooks on Windows API functions (limited).

## Warning: This is for educational purposes only!
The security is based on Windows kernel. Hades makes calls to kernel with the lowest possible way that usermode allows. Any future Windows update may cause failure or even generate false detections from this library. However it tested and working on both Windows 10 and 11 versions. Not tested on older windows versions

## How to use
- Built the library
- Include library in your project
- Include the headers you want to use. You have these options:
  - AntiDebug.hpp contains ready-to-use anti-debug functions for self and remote process. If you not searching for anything more advanced than that, this is the only header you have to include.
  - Include Kernel.hpp only if you want to use Hades::Kernel in your project (Kernel functions). With this you can get access to undocumented kernel functions of Windows and bypass usermode hooks or breakpoints has been set on these functions.
  - Include WindowsAPI.hpp only if you want to use Hades::WindowsAPI in your project (Windows API functions with Hades). With this you can use safely Windows API and bypass IAT manipulation, usermode hooks and breakpoints has been set on these functions.

There are available examples in TestApp project.
