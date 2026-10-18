export type Key =
  | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L'
  | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X'
  | 'Y' | 'Z' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
  | 'ENTER' | 'RETURN' | 'ESCAPE' | 'ESC'
  | 'SPACE' | 'TAB' | 'BACKSPACE' | 'DELETE'
  | 'SHIFT' | 'CTRL' | 'CONTROL' | 'ALT'
  | 'META' | 'CMD' | 'COMMAND' | 'WIN'
  | 'CAPS_LOCK'
  | 'ARROW_LEFT' | 'ARROW_RIGHT' | 'ARROW_UP' | 'ARROW_DOWN'
  | 'HOME' | 'END' | 'PAGE_UP' | 'PAGE_DOWN'
  | 'MINUS' | '-'
  | 'EQUALS' | '='
  | '.' | 'PERIOD'
  | 'GRAVE' | '/' | '\\' | ';' | ',' | '\''
  | 'LEFT_BRACKET' | '[' | 'RIGHT_BRACKET' | ']'
  | 'F1' | 'F2' | 'F3' | 'F4'
  | 'F5' | 'F6' | 'F7' | 'F8'
  | 'F9' | 'F10' | 'F11' | 'F12'

export interface Keyboard {
  /** Press and hold a key. */
  keyDown(key: Key): void

  /** Release a previously pressed key. */
  keyUp(key: Key): void

  /** Press and release a key. */
  press(key: Key): void

  /**
   * Press a key combination.
   * All keys except the last are treated as modifiers.
   *
   * @example keyboard.hotkey('CTRL', 'S')
   * @example keyboard.hotkey('META', 'SHIFT', 'S')
   */
  hotkey(...keys: [Key, ...Key[]]): void
}

const keyboard: Keyboard
export = keyboard
