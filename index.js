const native = require('./binding')

function check(ok, key, action) {
  if (!ok) {
    throw new Error(`Failed to ${action} key: ${key}`)
  }
}

const keyboard = {
  keyDown(key) {
    check(native.keyDown(normalize(key)), key, 'press')
  },

  keyUp(key) {
    check(native.keyUp(normalize(key)), key, 'release')
  },

  press(key) {
    try {
      this.keyDown(key)
      // This is a synchronous native event pair.
    } finally {
      this.keyUp(key)
    }
  },

  hotkey(...keys) {
    if (keys.length === 0) {
      throw new TypeError('At least one key is required')
    }

    const modifiers = keys.slice(0, -1)
    const target = keys[keys.length - 1]
    const pressed = []

    try {
      for (const key of modifiers) {
        this.keyDown(key)
        pressed.push(key)
      }

      this.press(target)
    } finally {
      for (const key of pressed.reverse()) {
        this.keyUp(key)
      }
    }
  }
}

function normalize(key) {
  if (typeof key !== 'string' || key.length === 0) {
    throw new TypeError('Key must be a non-empty string')
  }

  const aliases = {
    RETURN: 'ENTER',
    ESC: 'ESCAPE',
    CONTROL: 'CTRL',
    CMD: 'META',
    COMMAND: 'META'
  }

  const upper = key.toUpperCase()
  return aliases[upper] || upper
}

module.exports = { keyboard }
