var keypress = require('keypress');
var SerialPort = require('serialport');
var port = new SerialPort('COM5',{
baudRate: 9600,
parser: SerialPort.parsers.ReadLine
});
 
// make `process.stdin` begin emitting "keypress" events
keypress(process.stdin);
 
// listen for the "keypress" event
process.stdin.on('keypress', function (ch, key) {
  console.log('got "keypress"', key);
  write(key.name);
  if (key && key.ctrl && key.name == 'c') {
    process.stdin.pause();
  }
});
 
function write (key) {
    if (key == 'up'     ) key = 'w';
    if (key == 'down'   ) key = 's';
    if (key == 'left'   ) key = 'a';
    if (key == 'right'  ) key = 'd';
    port.write(key, function(err) {
        if (err) {
        return console.log('Error on write: ', err.message);
        }
        console.log('message written');
    });
}
 
process.stdin.setRawMode(true);
process.stdin.resume();