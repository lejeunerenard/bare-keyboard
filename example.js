const { keyboard } = require('./')

const waitS = 5

async function run() {
  console.log(`${waitS}s done`)
  const msg = "abcdefghijklmnopqrstuvwxyz1234567890.;'\\,/".split('')
  // issues: -"
  console.log('msg', msg)
  for (const char of msg) {
    console.log('pressing char: ', char)
    keyboard.press(char)

    await sleep(100)
  }
  keyboard.press('ENTER')
  keyboard.hotkey('COMMAND', 'S')
}

console.log(`wait ${waitS}s`)
setTimeout(run, waitS * 1000)

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms))
}
