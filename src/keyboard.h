#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Returns 0 on success, negative on failure.
int keyboard_key_down(const char* key);
int keyboard_key_up(const char* key);

#ifdef __cplusplus
}
#endif