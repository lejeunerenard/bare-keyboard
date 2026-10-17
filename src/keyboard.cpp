#include "keyboard.h"

#if defined(_WIN32)
  #include <windows.h>
#elif defined(__APPLE__)
  #include <ApplicationServices/ApplicationServices.h>
#elif defined(__linux__)
  #include <X11/Xlib.h>
  #include <X11/extensions/XTest.h>
#endif

// Implement the matching backend in macos.cpp or linux.cpp.
// Do not silently claim success on unsupported platforms.
extern "C" int keyboard_key_down(const char *key);
extern "C" int keyboard_key_up(const char *key);
