#include <bare.h>
#include <js.h>
#include <utf.h>

#include <stdlib.h>

#include "src/keyboard.h"

static js_value_t *
keyboard_event(js_env_t *env, js_callback_info_t *info, int down) {
  size_t argc = 1;
  js_value_t *argv[1];

  if (js_get_callback_info(env, info, &argc, argv, NULL, NULL) < 0) {
    return NULL;
  }

  if (argc != 1) {
    js_value_t *result;

    if (js_get_boolean(env, false, &result) < 0) return NULL;

    return result;
  }

  size_t len = 0;

  if (js_get_value_string_utf8(env, argv[0], NULL, 0, &len) < 0) {
    return NULL;
  }

  char *key = (char *) malloc(len + 1);
  if (key == NULL) return NULL;

  if (js_get_value_string_utf8(
        env, argv[0], (utf8_t *) key, len + 1, NULL) < 0) {
    free(key);
    return NULL;
  }

  printf("key %s down %d\n", key, down);
  int status = down
    ? keyboard_key_down(key)
    : keyboard_key_up(key);

  free(key);

  js_value_t *result;

  if (js_get_boolean(env, status == 0, &result) < 0) {
    return NULL;
  }

  return result;
}

static js_value_t *
keyboard_key_down_binding(js_env_t *env, js_callback_info_t *info) {
  return keyboard_event(env, info, 1);
}

static js_value_t *
keyboard_key_up_binding(js_env_t *env, js_callback_info_t *info) {
  return keyboard_event(env, info, 0);
}

static js_value_t *
keyboard_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, NULL, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("keyDown", keyboard_key_down_binding)
  V("keyUp", keyboard_key_up_binding)
#undef V

  return exports;
}

BARE_MODULE(bare_keyboard, keyboard_exports)
