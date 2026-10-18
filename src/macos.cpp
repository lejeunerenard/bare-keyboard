#include "keyboard.h"

#if defined(__APPLE__)

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>

#include <cstring>
#include <string>

namespace {

struct KeyMapping {
  const char* name;
  CGKeyCode code;
};

// macOS virtual key codes (physical key positions).
// These are independent of the character produced by the keyboard layout.
constexpr KeyMapping KEY_MAP[] = {
  {"A", 0x00},
  {"S", 0x01},
  {"D", 0x02},
  {"F", 0x03},
  {"H", 0x04},
  {"G", 0x05},
  {"Z", 0x06},
  {"X", 0x07},
  {"C", 0x08},
  {"V", 0x09},
  {"B", 0x0B},
  {"Q", 0x0C},
  {"W", 0x0D},
  {"E", 0x0E},
  {"R", 0x0F},
  {"Y", 0x10},
  {"T", 0x11},

  {"1", 0x12},
  {"2", 0x13},
  {"3", 0x14},
  {"4", 0x15},
  {"6", 0x16},
  {"5", 0x17},
  {"EQUALS", 0x18},
  {"9", 0x19},
  {"7", 0x1A},
  {"MINUS", 0x1B},
  {"8", 0x1C},
  {"0", 0x1D},
  {"RIGHT_BRACKET", 0x1E},
  {"O", 0x1F},
  {"U", 0x20},
  {"LEFT_BRACKET", 0x21},
  {"I", 0x22},
  {"P", 0x23},
  {"L", 0x25},
  {"J", 0x26},
  {"'", 0x27},
  {"K", 0x28},
  {";", 0x29},
  {"\\", 0x2A},
  {",", 0x2B},
  {"/", 0x2C},
  {"N", 0x2D},
  {"M", 0x2E},
  {".", 0x2F},
  {"GRAVE", 0x32},

  {"ENTER", 0x24},
  {"RETURN", 0x24},
  {"TAB", 0x30},
  {"SPACE", 0x31},
  {"BACKSPACE", 0x33},
  {"ESC", 0x35},

  {"META", 0x37},
  {"SHIFT", 0x38},
  {"CAPS_LOCK", 0x39},
  {"ALT", 0x3A},
  {"CTRL", 0x3B},

  {"ARROW_LEFT", 0x7B},
  {"ARROW_RIGHT", 0x7C},
  {"ARROW_DOWN", 0x7D},
  {"ARROW_UP", 0x7E},

  {"DELETE", 0x75},
  {"HOME", 0x73},
  {"END", 0x77},
  {"PAGE_UP", 0x74},
  {"PAGE_DOWN", 0x79},

  {"F1", 0x7A},
  {"F2", 0x78},
  {"F3", 0x63},
  {"F4", 0x76},
  {"F5", 0x60},
  {"F6", 0x61},
  {"F7", 0x62},
  {"F8", 0x64},
  {"F9", 0x65},
  {"F10", 0x6D},
  {"F11", 0x67},
  {"F12", 0x6F}
  // KeypadDecimal        = 0x41,
  // KeypadMultiply       = 0x43,
  // KeypadPlus           = 0x45,
  // KeypadClear          = 0x47,
  // KeypadDivide         = 0x4B,
  // KeypadEnter          = 0x4C,
  // KeypadMinus          = 0x4E,
  // KeypadEquals         = 0x51,
  // Keypad0              = 0x52,
  // Keypad1              = 0x53,
  // Keypad2              = 0x54,
  // Keypad3              = 0x55,
  // Keypad4              = 0x56,
  // Keypad5              = 0x57,
  // Keypad6              = 0x58,
  // Keypad7              = 0x59,
  // Keypad8              = 0x5B,
  // Keypad9              = 0x5C
};

bool lookup_key(const char* name, CGKeyCode* result) {
  if (name == nullptr || result == nullptr) {
    return false;
  }

  for (const auto& entry : KEY_MAP) {
    if (std::strcmp(name, entry.name) == 0) {
      *result = entry.code;
      return true;
    }
  }

  return false;
}

int send_key(const char* name, bool down) {
  CGKeyCode code;

  if (!lookup_key(name, &code)) {
    return -1;
  }

  CGEventRef event = CGEventCreateKeyboardEvent(
    nullptr,
    code,
    down
  );

  if (event == nullptr) {
    return -2;
  }

  CGEventPost(kCGHIDEventTap, event);
  CFRelease(event);

  return 0;
}

} // namespace

extern "C" int keyboard_key_down(const char* key) {
  return send_key(key, true);
}

extern "C" int keyboard_key_up(const char* key) {
  return send_key(key, false);
}

#endif // __APPLE__
