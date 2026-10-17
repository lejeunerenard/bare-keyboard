const test = require('brittle')
const addon = require('.')

test('press', (t) => {
  t.execution(() => addon.press('h'))
})
