function scheduleNoOp () {
  
}

function scheduleFluteNote (note, start, duration, gain) {
  gain /= dBToGain(-28);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time:0.3, dB:-32},{time:0.9, dB:-32},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time:0.1, dB:-38},{time:0.9, dB:-38},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.3, dB:-42},{time:0.9, dB:-42},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 36, start, duration, gain,
    [{time:0.3, dB:-48},{time:0.9, dB:-48},{time:1.0, dB:-100}]);
  return;
  scheduleOscillator('sine', note + 48, start, duration, gain,
    [{time:0.2, dB:-41},{time:0.9, dB:-41},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 60, start, duration, gain,
    [{time:0.2, dB:-39},{time:0.9, dB:-39},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 72, start, duration, gain,
    [{time:0.2, dB:-44},{time:0.9, dB:-44},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 84, start, duration, gain,
    [{time:0.3, dB:-44},{time:0.9, dB:-44},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 96, start, duration, gain,
    [{time:0.3, dB:-56},{time:0.9, dB:-56},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 108, start, duration, gain,
    [{time:0.3, dB:-59},{time:0.9, dB:-59},{time:1.0, dB:-100}]);
}

function scheduleOboeNote (note, start, duration, gain) {
  gain /= dBToGain(-50);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time:0.1, dB:-50},{time:0.9, dB:-50},{time:1.0, dB:-100}]);
  scheduleOscillator('triangle', note + 12, start, duration, gain,
    [{time:0.1, dB:-55},{time:0.9, dB:-55},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.3, dB:-60},{time:0.9, dB:-60},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 36, start, duration, gain,
    [{time:0.3, dB:-65},{time:0.9, dB:-65},{time:1.0, dB:-100}]);
  return;
  scheduleOscillator('sine', note + 60, start, duration, gain,
    [{time:0.2, dB:-63},{time:0.9, dB:-63},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 72, start, duration, gain,
    [{time:0.2, dB:-58},{time:0.9, dB:-58},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 84, start, duration, gain,
    [{time:0.3, dB:-65},{time:0.9, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 96, start, duration, gain,
    [{time:0.3, dB:-70},{time:0.9, dB:-70},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 120, start, duration, gain,
    [{time:0.3, dB:-70},{time:0.9, dB:-70},{time:1.0, dB:-100}]);
}


function scheduleClarinetNote (note, start, duration, gain) {
  gain /= dBToGain(-50);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time:0.1, dB:-79},{time:0.9, dB:-79},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time:0.1, dB:-65},{time:0.9, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.3, dB:-50},{time:0.9, dB:-50},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 36, start, duration, gain,
    [{time:0.3, dB:-55},{time:0.9, dB:-55},{time:1.0, dB:-100}]);
}

function scheduleBassoonNote (note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time:0.05, dB:-65},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time:0.05, dB:-68},{time:0.95, dB:-68},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.05, dB:-58},{time:0.95, dB:-58},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 48, start, duration, gain,
    [{time:0.05, dB:-75},{time:0.95, dB:-75},{time:1.0, dB:-100}]);
}

function scheduleHornNote (note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time:0.05, dB:-65},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('triangle', note + 12, start, duration, gain,
    [{time:0.05, dB:-68},{time:0.95, dB:-68},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.2, dB:-58},{time:0.95, dB:-58},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 48, start, duration, gain,
    [{time:0.2, dB:-75},{time:0.95, dB:-75},{time:1.0, dB:-100}]);
}

function scheduleTromboneNote (note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time:0.05, dB:-65},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time:0.05, dB:-55},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.2, dB:-58},{time:0.95, dB:-58},{time:1.0, dB:-100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time:0.2, dB:-75},{time:0.95, dB:-75},{time:1.0, dB:-100}]);
}

function scheduleTrumpetNote (note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time:0.05, dB:-65},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time:0.05, dB:-55},{time:0.95, dB:-60},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.2, dB:-58},{time:0.95, dB:-58},{time:1.0, dB:-100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time:0.2, dB:-75},{time:0.95, dB:-75},{time:1.0, dB:-100}]);
}

function scheduleBaritoneSaxNote (note, start, duration, gain) {
  gain /= dBToGain(-50);
  scheduleOscillator('square', note, start, duration, gain,
    [{time:0.05, dB:-62},{time:0.15, dB:-65},{time:0.95, dB:-65},
    {time:1.0, dB:-100}]);
  scheduleOscillator('triangle', note + 12, start, duration, gain,
    [{time:0.05, dB:-52},{time:0.15, dB:-55},{time:0.95, dB:-55},
    {time:1.0, dB:-100}]);
  scheduleOscillator('triangle', note + 24, start, duration, gain,
    [{time:0.05, dB:-58},{time:0.15, dB:-58},{time:0.95, dB:-58},
    {time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 48, start, duration, gain,
    [{time:0.05, dB:-75},{time:0.15, dB:-75},{time:0.95, dB:-75},
    {time:1.0, dB:-100}]);
}

function scheduleVibraphoneNote (note, start, duration, gain) {
  gain /= dBToGain(-6);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time:0.05, dB:-3},{time:0.15, dB:-12},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time:0.05, dB:-6},{time:0.15, dB:-6},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.05, dB:-12},{time:0.15, dB:-42},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 48, start, duration, gain,
    [{time:0.05, dB:-24},{time:0.15, dB:-54},{time:1.0, dB:-100}]);
}

function scheduleCrotalesNote (note, start, duration, gain) {
  gain /= dBToGain(-12);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time:0.01, dB:-3},{time:0.05, dB:-30},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time:0.05, dB:-6},{time:0.15, dB:-12},{time:1.0, dB:-100}]);
  scheduleOscillator('triangle', note + 24, start, duration, gain,
    [{time:0.01, dB:-12},{time:0.05, dB:-30},{time:1.0, dB:-100}]);
  scheduleOscillator('triangle', note + 48, start, duration, gain,
    [{time:0.01, dB:-24},{time:0.05, dB:-30},{time:1.0, dB:-100}]);
}

function scheduleViolinNote (note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time:0.05, dB:-85},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time:0.05, dB:-85},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.2, dB:-58},{time:0.95, dB:-58},{time:1.0, dB:-100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time:0.2, dB:-75},{time:0.95, dB:-75},{time:1.0, dB:-100}]);
}

function scheduleViolaNote (note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time:0.05, dB:-85},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time:0.05, dB:-85},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.2, dB:-58},{time:0.95, dB:-58},{time:1.0, dB:-100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time:0.2, dB:-75},{time:0.95, dB:-75},{time:1.0, dB:-100}]);
}

function scheduleCelloNote (note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time:0.05, dB:-85},{time:0.95, dB:-60},{time:1.0, dB:-100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time:0.05, dB:-85},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.2, dB:-58},{time:0.95, dB:-58},{time:1.0, dB:-100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time:0.2, dB:-75},{time:0.95, dB:-75},{time:1.0, dB:-100}]);
}

function scheduleDoubleBassNote (note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time:0.05, dB:-85},{time:0.95, dB:-60},{time:1.0, dB:-100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time:0.05, dB:-85},{time:0.95, dB:-65},{time:1.0, dB:-100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time:0.2, dB:-58},{time:0.95, dB:-58},{time:1.0, dB:-100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time:0.2, dB:-75},{time:0.95, dB:-75},{time:1.0, dB:-100}]);
}
