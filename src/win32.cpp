#include "keyboard.h"

#if defined(_WIN32)

#include <windows.h>
#include <cstring>

static WORD
key_code(const char *key) {
  if (std::strcmp(key, "ENTER") == 0) return VK_RETURN;
  if (std::strcmp(key, "ESCAPE") == 0) return VK_ESCAPE;
  if (std::strcmp(key, "SPACE") == 0) return VK_SPACE;
  if (std::strcmp(key, "TAB") == 0) return VK_TAB;
  if (std::strcmp(key, "CTRL") == 0) return VK_CONTROL;
  if (std::strcmp(key, "SHIFT") == 0) return VK_SHIFT;
  if (std::strcmp(key, "ALT") == 0) return VK_MENU;

  if (std::strlen(key) == 1 &&
      key[0] >= 'A' && key[0] <= 'Z') {
    return static_cast<WORD>(key[0]);
  }

  return 0;
}

static int
send_key(const char *key, bool up) {
  WORD vk = key_code(key);
  if (vk == 0) return -1;

  INPUT input{};
  input.type = INPUT_KEYBOARD;
  input.ki.wVk = vk;
  input.ki.dwFlags = up ? KEYEVENTF_KEYUP : 0;

  return SendInput(1, &input, sizeof(input)) == 1 ? 0 : -1;
}

extern "C" int
keyboard_key_down(const char *key) {
  return send_key(key, false);
}

extern "C" int
keyboard_key_up(const char *key) {
  return send_key(key, true);
}

#endif // _WIN32
