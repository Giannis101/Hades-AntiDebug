# Hades - An andvanced and complete anti-debug library for your Windows x64 C++ project

## Usage
- Easy to use.
- Detect most of the debugging types (usermode only).
- Detect all usermode debugger-hide tools and any attempt to hide the presence of debugger.
- Get access to undocumented kernel functions and bypass usermode hooks (limited).
- Call Windows API functions safely: Bypass IAT (import address table) manipulation and other usermode hooks on Windows API functions (limited).















## Warning: This is for educational purposes only!
The security is based on Windows kernel. Hades makes calls to kernel with the lowest possible way that usermode allows. Any future Windows update may cause failure or even generate false detections from this library. However it tested and working on both Windows 10 and 11 versions. Not tested on older windows versions
