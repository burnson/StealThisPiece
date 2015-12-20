function setPiece () {
  setConcertStealThisPiece();
}

function setConcertStealThisPiece () {
  piece = {};
  piece.seed = 133;
  piece.loopContinueRate = 5;
  piece.codeLength = 10000;
  piece.tapeLength = 1024;
  piece.loopStep = 100;
  piece.loopSkipCreateRate = 3;
  piece.loopInnerStartLow = 100;
  piece.loopInnerStartHigh = 100;
  piece.loopInnerEndLow = 100;
  piece.loopInnerEndHigh = 100;
  piece.loopOuterEndLow = 50;
  piece.loopOuterEndHigh = 50;
  piece.longestNote = 4;
  piece.probabilityInversionSections = 10;
  piece.computationRateInversion = 0.9975;
  piece.range = 0;
  piece.tempo = 112;
  piece.rhythmSixteenth = false;
  piece.rhythmTripletEighth = true;
  piece.rhythmEighth = true;
  piece.rhythmTripletQuarter = true;
  piece.rhythmQuarter = false;
  piece.useHairpins = true;
  piece.wrapDynamics = true;
  piece.pitchClass = [
    true, true, true, true,
    true, true, true, true,
    true, true, true, true
  ];
  
  probabilities = {};
  probabilities.MoveBackward = 200000;
  probabilities.MoveForward = 200000;
  probabilities.DecrementData = 200000;
  probabilities.IncrementData = 200000;
  probabilities.DecrementDuration = 5000;
  probabilities.IncrementDuration = 5000;
  probabilities.EmitFlute = 400;
  probabilities.EmitOboe = 400;
  probabilities.EmitClarinet = 200;
  probabilities.EmitBassoon = 200;
  probabilities.EmitHorn = 100;
  probabilities.EmitTrumpet = 200;
  probabilities.EmitTrombone = 100;
  probabilities.EmitBaritoneSax = 500;
  probabilities.EmitVibraphone = 500;
  probabilities.EmitCrotales = 100;
  probabilities.EmitViolin = 500;
  probabilities.EmitViola = 500;
  probabilities.EmitCello = 300;
  probabilities.EmitDoubleBass = 100;
  probabilities.ToggleWinds = 1000;
  probabilities.ToggleBrass = 1000;
  probabilities.TogglePercussion = 1000;
  probabilities.ToggleStrings = 1000;
  probabilities.FluteSoft = 10;
  probabilities.FluteLoud = 10;
  probabilities.FluteSofter = 10;
  probabilities.FluteLouder = 10;
  probabilities.OboeSoft = 10;
  probabilities.OboeLoud = 10;
  probabilities.OboeSofter = 10;
  probabilities.OboeLouder = 10;
  probabilities.ClarinetSoft = 10;
  probabilities.ClarinetLoud = 10;
  probabilities.ClarinetSofter = 10;
  probabilities.ClarinetLouder = 10;
  probabilities.BassoonSoft = 10;
  probabilities.BassoonLoud = 10;
  probabilities.BassoonSofter = 10;
  probabilities.BassoonLouder = 10;
  probabilities.HornSoft = 10;
  probabilities.HornLoud = 10;
  probabilities.HornSofter = 10;
  probabilities.HornLouder = 10;
  probabilities.TrumpetSoft = 10;
  probabilities.TrumpetLoud = 10;
  probabilities.TrumpetSofter = 10;
  probabilities.TrumpetLouder = 10;
  probabilities.TromboneSoft = 10;
  probabilities.TromboneLoud = 10;
  probabilities.TromboneSofter = 10;
  probabilities.TromboneLouder = 10;
  probabilities.BaritoneSaxSoft = 10;
  probabilities.BaritoneSaxLoud = 10;
  probabilities.BaritoneSaxSofter = 10;
  probabilities.BaritoneSaxLouder = 10;
  probabilities.VibraphoneSoft = 10;
  probabilities.VibraphoneLoud = 10;
  probabilities.VibraphoneSofter = 10;
  probabilities.VibraphoneLouder = 10;
  probabilities.CrotalesSoft = 10;
  probabilities.CrotalesLoud = 10;
  probabilities.CrotalesSofter = 10;
  probabilities.CrotalesLouder = 10;
  probabilities.ViolinSoft = 10;
  probabilities.ViolinLoud = 10;
  probabilities.ViolinSofter = 10;
  probabilities.ViolinLouder = 10;
  probabilities.ViolaSoft = 10;
  probabilities.ViolaLoud = 10;
  probabilities.ViolaSofter = 10;
  probabilities.ViolaLouder = 10;
  probabilities.CelloSoft = 10;
  probabilities.CelloLoud = 10;
  probabilities.CelloSofter = 10;
  probabilities.CelloLouder = 10;
  probabilities.DoubleBassSoft = 10;
  probabilities.DoubleBassLoud = 10;
  probabilities.DoubleBassSofter = 10;
  probabilities.DoubleBassLouder = 10;
}

////////////////////////////////////////////////////////////////////////////////

var piece = {}, probabilities = {}, random;

function distributeProbabilities (amount)
{
  // Apply probability inversion if being used.
  probabilities["MoveBackward"] -=
    piece.computationRateInversion * probabilities["MoveBackward"] * amount;
  probabilities["MoveForward"] -=
    piece.computationRateInversion * probabilities["MoveForward"] * amount;
  probabilities["DecrementData"] -=
    piece.computationRateInversion * probabilities["DecrementData"] * amount;
  probabilities["IncrementData"] -=
    piece.computationRateInversion * probabilities["IncrementData"] * amount;
    
  // Turn the probabilities into a distribution.
  var sum = 0, instruction;
  for(instruction in probabilities) {
    sum += probabilities[instruction];
    probabilities[instruction] = sum;
  }
  
  // Normalize the distribution.
  for(instruction in probabilities) {
    probabilities[instruction] /= sum;
  }
}

// Instruction set
var nameOf = [
  "NullOp",
  "WhileBegin",
  "WhileEnd",
  "MoveBackward",
  "MoveForward",
  "DecrementData",
  "IncrementData",
  "DecrementDuration",
  "IncrementDuration",
  "EmitFlute",
  "EmitOboe",
  "EmitClarinet",
  "EmitBassoon",
  "EmitHorn",
  "EmitTrumpet",
  "EmitTrombone",
  "EmitBaritoneSax",
  "EmitVibraphone",
  "EmitCrotales",
  "EmitViolin",
  "EmitViola",
  "EmitCello",
  "EmitDoubleBass",
  "ToggleWinds",
  "ToggleBrass",
  "TogglePercussion",
  "ToggleStrings",
  "FluteSoft",
  "FluteLoud",
  "FluteSofter",
  "FluteLouder",
  "OboeSoft",
  "OboeLoud",
  "OboeSofter",
  "OboeLouder",
  "ClarinetSoft",
  "ClarinetLoud",
  "ClarinetSofter",
  "ClarinetLouder",
  "BassoonSoft",
  "BassoonLoud",
  "BassoonSofter",
  "BassoonLouder",
  "HornSoft",
  "HornLoud",
  "HornSofter",
  "HornLouder",
  "TrumpetSoft",
  "TrumpetLoud",
  "TrumpetSofter",
  "TrumpetLouder",
  "TromboneSoft",
  "TromboneLoud",
  "TromboneSofter",
  "TromboneLouder",
  "BaritoneSaxSoft",
  "BaritoneSaxLoud",
  "BaritoneSaxSofter",
  "BaritoneSaxLouder",
  "VibraphoneSoft",
  "VibraphoneLoud",
  "VibraphoneSofter",
  "VibraphoneLouder",
  "CrotalesSoft",
  "CrotalesLoud",
  "CrotalesSofter",
  "CrotalesLouder",
  "ViolinSoft",
  "ViolinLoud",
  "ViolinSofter",
  "ViolinLouder",
  "ViolaSoft",
  "ViolaLoud",
  "ViolaSofter",
  "ViolaLouder",
  "CelloSoft",
  "CelloLoud",
  "CelloSofter",
  "CelloLouder",
  "DoubleBassSoft",
  "DoubleBassLoud",
  "DoubleBassSofter",
  "DoubleBassLouder",
  "InstructionCount"
];

var indexOf = function () {
  var x = {}, i;
  for (i = 0; i < nameOf.length; i++) {
    x[nameOf[i]] = i
  }
  return x;
}();

// Rhythm
var durationIndex = 0;
var durations = [];
var durationLCM = 48;
function createDurations () {
  if (piece.rhythmSixteenth) durations.push(durationLCM * 1 / 16);
  if (piece.rhythmTripletEighth) durations.push(durationLCM * 1 / 12);
  if (piece.rhythmEighth) durations.push(durationLCM * 1 / 8);
  if (piece.rhythmTripletQuarter) durations.push(durationLCM * 1 / 6);
  if (piece.rhythmQuarter) durations.push(durationLCM * 1 / 4);
}

// Instruments

var instruments = [];
var toggles = [true, true, true, true];

function makeInstrument (index, group, name, low, high) {
  return {
    "index": index,
    "group": group,
    "name": name,
    "low": low,
    "high": high,
    "notes": [],
    "offset": 0,
    "dynamicMark": 3
  };
}

function createInstruments () {
  var i = [];
  i.push(makeInstrument(0,  0, "Flute",       67, 98 + piece.range)); //G4-D6
  i.push(makeInstrument(1,  0, "Oboe",        60, 84 + piece.range)); //C4-C6
  i.push(makeInstrument(2,  0, "Clarinet",    50, 79 + piece.range)); //D3-G5
  i.push(makeInstrument(3,  0, "Bassoon",     36, 67 + piece.range)); //C2-G4
  i.push(makeInstrument(4,  1, "Horn",        48, 72 + piece.range)); //C3-C5
  i.push(makeInstrument(5,  1, "Trumpet",     55, 79 + piece.range)); //G3-G5
  i.push(makeInstrument(6,  1, "Trombone",    43, 67 + piece.range)); //G2-G4
  i.push(makeInstrument(7,  1, "BaritoneSax", 43, 60 + piece.range)); //G2-C4
  i.push(makeInstrument(8,  2, "Vibraphone",  53, 89              )); //F3-F6
  i.push(makeInstrument(9,  2, "Crotales",    60, 84              )); //C2-C4
  i.push(makeInstrument(10, 3, "Violin",      55, 84 + piece.range)); //G3-C6
  i.push(makeInstrument(11, 3, "Viola",       48, 79 + piece.range)); //C3-G5
  i.push(makeInstrument(12, 3, "Cello",       36, 67 + piece.range)); //C2-G5
  i.push(makeInstrument(13, 3, "DoubleBass",  28, 48 + piece.range)); //E2-C4
  instruments = i;
  
  /*Note: Violin is reassigned to group 2 below to express the behavior of a bug
  in the original where the Violin was considered part of the percussion group
  for toggling purposes. If backwards compatibility is not a concern then this
  line can be removed.*/
  instruments[10].group = 2;
}

var instructions = [], data = [];
var instructionPointer = 0;
var dataPointer = 0;

function planLoops () {
  var a = piece.loopInnerStartLow;
  var b = a + piece.loopInnerStartHigh;
  var c = b + piece.loopInnerEndLow;
  var d = c + piece.loopInnerEndHigh;
  var e = d + piece.loopOuterEndLow;
  var f = e + piece.loopOuterEndHigh;
  var g = f + piece.loopStep;
  var i;
  var whileBegin = indexOf["WhileBegin"];
  var whileEnd = indexOf["WhileEnd"];
  for(i = 0; i < instructions.length - g; i++)
  {
    if(random.nextIntBetween(0, piece.loopSkipCreateRate))
      continue;
    instructions[i] = whileBegin;
    instructions[i + random.nextIntBetween(e, f)] = whileEnd;
    instructions[i + random.nextIntBetween(a, b)] = whileBegin;
    instructions[i + random.nextIntBetween(c, d)] = whileEnd;
    i += g;
  }
}

function getProbableInstruction (normalizedNumber) {
  var k, bestKey = 'NullOp', lowestValue = 2; //i.e. a number > 1
  for (k in probabilities) {
    if (normalizedNumber < probabilities[k] && probabilities[k] < lowestValue) {
      lowestValue = probabilities[k];
      bestKey = k;
    }
  }
  return indexOf[bestKey];
}

function planInstructions () {
  var i, n = instructions.length;
  var inversionProbability;
  for(i = 0; i < n; i++)
  {
    setPiece();
    inversionProbability = (Math.floor(i / Math.floor(n /
      piece.probabilityInversionSections)) % 2);
    distributeProbabilities(inversionProbability);
    if(instructions[i] === 0)
      instructions[i] = getProbableInstruction(random.nextFloat());
  }
}

var cycleCount = 0;
var lowestDataAccess = 0;
var highestDataAccess = 0;

function halt() {
  return instructionPointer >= instructions.length || instructionPointer < 0;
}

function getInstruction () {
  return nameOf[instructions[instructionPointer]];
}

function updateDataAccess () {
  if (dataPointer < lowestDataAccess) {
    lowestDataAccess = dataPointer;
  }
  if (dataPointer > highestDataAccess) {
    highestDataAccess = dataPointer;
  }
}

function getCyclicDataPointer () {
  return (dataPointer + data.length * Math.abs(dataPointer)) % data.length;
}

function getData () {
  updateDataAccess();
  return data[getCyclicDataPointer()];
}

function addToData (amount) {
  updateDataAccess();
  var x = getCyclicDataPointer();
  data[x] = (data[x] + amount + 256) % 256;
}

function lookupPitch(instrument, p) {
  var x;
  var i, noteStart = instrument.low;
  x = p < 128 ? p : p - 256;
  
  if (instrument.low === instrument.high) {
    return instrument.low;
  }
  
  // Find the first C and make that 0.
  if (noteStart % 12 != 0) {
    noteStart += (12 - (instrument.low % 12));
  }
  
  if (x === 0) {
    return noteStart;
  }
  
  if (x > 0) {
    for (i = 0; i < x; i++) {
      while (!piece.pitchClass[(++noteStart) % 12]) {}
      
      //Octave down as far as possible if out of range.
      if (noteStart > instrument.high) {
        while (noteStart - 12 >= instrument.low) {
          noteStart -= 12;
        }
      }
    }
  } else {
    for (i = 0; i < -x; i++) {
      while (!piece.pitchClass[(--noteStart) % 12]) {}
      
      //Octave up as far as possible if out of range.
      if (noteStart < instrument.low) {
        while (noteStart + 12 <= instrument.high) {
          noteStart += 12;
        }
      }
    }
  }
  return noteStart;
}

var globalTime = 0;
var dynamics = 7;
var dynamic = [0, 1, 2, 3, 4, 5, 6];

function makeNote (offset, duration, pitch, dynamicMark) {
  var n = {
    "time": offset,
    "duration": duration,
    "pitch": pitch,
    "dynamicMark": dynamicMark
  };
  return n;
}

function addNote (instrument, data) {
  var instrumentIsOn = toggles[instrument.group];
  var actualPitch = lookupPitch(instrument, data);
  if (instrument.offset === globalTime) {
    var duration = durations[durationIndex];
    if (instrumentIsOn) {
      instrument.notes.push(makeNote(instrument.offset, duration,
        actualPitch, dynamic[instrument.dynamicMark]));
    }
    instrument.offset += duration;
    globalTime = instrument.offset;
  } else if (instrument.offset < globalTime) {
    var longestNote = piece.longestNote * durationLCM / 4;
    if (globalTime - instrument.offset > longestNote) {
      instrument.offset = globalTime - longestNote;
    }
    var duration = globalTime - instrument.offset;
    if (instrumentIsOn) {
      instrument.notes.push(makeNote(instrument.offset, duration,
        actualPitch, dynamic[instrument.dynamicMark]));
    }
    instrument.offset += duration;
  }
}

function emit (i) {
  var index = indexOf[i];
  if (i === 'DecrementDuration') {
    durationIndex = Math.max(0, durationIndex - 1);
  } else if (i === 'IncrementDuration') {
    durationIndex = Math.min(durations.length - 1, durationIndex + 1);
  } else if (index >= indexOf.EmitFlute &&
             index <= indexOf.EmitDoubleBass) {
    var instrumentId = index - indexOf['EmitFlute'];
    var d = getData();
    addNote(instruments[instrumentId], getData());
  } else if (index >= indexOf.ToggleWinds &&
             index <= indexOf.ToggleStrings) {
    var indexToToggle = index - indexOf.ToggleWinds;
    toggles[indexToToggle] = !toggles[indexToToggle];
    if (!toggles[0] && !toggles[1] && !toggles[2] && !toggles[3]) {
      toggles = [true, true, true, true];
    }
  } else if (index >= indexOf.FluteSoft && index <= indexOf.DoubleBassLouder) {
    var dynamicId = index - indexOf.FluteSoft;
    var dynamicType = dynamicId % 4;
    var dynamicInstrument = (dynamicId - dynamicType) / 4;
    var dynamicMark = instruments[dynamicInstrument].dynamicMark;
    if (dynamicType === 0) {
      dynamicMark = 2;
    } else if (dynamicType === 1) {
      dynamicMark = 4;
    } else if (dynamicType === 2) {
      if (piece.wrapDynamics) {
        dynamicMark = (dynamics + dynamicMark - 1) % dynamics;
      } else {
        dynamicMark = Math.max(dynamicMark - 1, 0);
      }
    } else {
      if (piece.wrapDynamics) {
        dynamicMark = (dynamics + dynamicMark + 1) % dynamics;
      } else {
        dynamicMark = Math.min(dynamicMark + 1, dynamics - 1);
      }
    }
    instruments[dynamicInstrument].dynamicMark = dynamicMark;
  }
}

function performInstruction () {
  cycleCount++;
  if (halt()) return false;
  var i = getInstruction();
  if (i === "MoveForward") dataPointer++;
  else if (i === "MoveBackward") dataPointer--;
  else if (i === "IncrementData") addToData(1);
  else if (i === "DecrementData") addToData(-1);
  else if ((i === "WhileBegin" && !getData()) || (i === "WhileEnd" && getData())) {
    if (i !== "WhileEnd" || random.nextIntBetween(0, piece.loopContinueRate)) {
      //Perform jump operation to emulate while loops.
      var braceCount = 1;
      do {
        instructionPointer += (i == "WhileBegin" ? 1 : -1);
        if (halt()) {
          return false;
        }
        if (getInstruction() === (i === "WhileBegin" ? "WhileEnd" : "WhileBegin"))
          braceCount--;
        else if (getInstruction() === (i === "WhileEnd" ? "WhileEnd" : "WhileBegin"))
          braceCount++;
      } while (braceCount > 0);
    }
  } else {
    emit(i);
  }
  instructionPointer++;
  return true;
}

function createPiece () {
  setPiece();
  
  // Initialize random number generator;
  random = createMultiplyWithCarryPRNG(piece.seed);
  
  // Initialize constants and distributions.
  createDurations();
  createInstruments();
  distributeProbabilities(0.0);
  
  // Initialize state and maps.
  var i;
  for (i = 0; i < piece.codeLength; i++) { instructions[i] = 0; }
  for (i = 0; i < piece.tapeLength; i++) { data[i] = 0; }
  
  planLoops();
  planInstructions();
  while (performInstruction()) {}
}

function pieceAsCSV () {
  var i, j;
  var pieceString = 'Instrument,Channel,Start,Duration,Key,Dynamic\n';
  for (i = 0; i < instruments.length; i++) {
    var instrument = instruments[i];
    for (j = 0; j < instrument.notes.length; j++) {
      var note = instrument.notes[j];
      var s = instrument.name;
      s += ',' + instrument.index;
      s += ',' + note.time;
      s += ',' + note.duration;
      s += ',' + note.pitch;
      s += ',' + note.dynamicMark;
      s += "\n";
      pieceString += s;
    }
  }
  return pieceString.trim();
}

function noteTimeToSeconds (noteTime) {
  return noteTime * 4 * 60 / piece.tempo / durationLCM;
}

function dynamicMarkToVelocity (dynamicMark) {
  return Math.round(dynamicMark / 7 * 87) + 20;
}

function pieceAsMIDI () {
  var midiData = [], instrument, note;
  var i, j;
  for (i = 0; i < instruments.length; i++) {
    instrument = instruments[i];
    for (j = 0; j < instrument.notes.length; j++) {
      note = instrument.notes[j];
      midiData.push({
        "time": noteTimeToSeconds(note.time),
        "duration": noteTimeToSeconds(note.duration),
        "channel": instrument.index,
        "pitch": note.pitch,
        "velocity": dynamicMarkToVelocity(note.dynamicMark)
      });
    }
  }
  return midiData;
}

function isRunningUnderNodeJS() {
  return typeof global !== 'undefined' &&
    Object.prototype.toString.call(global.process) === '[object process]';
}

function parityChecksum(s) {
  var parity = 0, i;
  for (i = 0; i < s.length; i++) {
    parity = (parity + s.charCodeAt(i)) >>> 0;
  }
  return parity;
}

function generateInConsole () {
  createPiece();
  var finalPiece = pieceAsCSV();
  console.log('CSV of piece:')
  console.log(finalPiece);
  console.log('Parity of CSV: ' + parityChecksum(finalPiece));
  if(parityChecksum(finalPiece) !== 6820566) {
    console.log('WARNING: piece does not match reference');
  }
}

////////////////////////////////////////////////////////////////////////////////

function createMultiplyWithCarryPRNG (seed) {
  var state = [];
  
  function get32BitHigh (x) {
    return (x - get32BitLow(x)) / 0x100000000;
  }
  
  function get32BitLow (x) {
    return x >>> 0;
  }
  
  function is32Bit (x) {
    return x >= 0 && x < 0x100000000 && x === Math.floor(x);
  }
  
  function multiply32BitHigh (a, b) {
    return get32BitHigh(get32BitLow(a) * get32BitLow(b));
  }
  
  function multiply32BitLow (a, b) {
    var ah = (get32BitLow(a) >>> 16) & 0xffff, al = get32BitLow(a) & 0xffff;
    var bh = (get32BitLow(b) >>> 16) & 0xffff, bl = get32BitLow(b) & 0xffff;
    return ((al * bl) + ((ah * bl + al * bh) << 16) >>> 0);
  }
  
  var generator = {
    next : function () {
      var magicNumbers = [5115, 1776, 1492, 2111111111], low = 0, high = 0, i;
      for (i = 0; i < magicNumbers.length; i++) {
        low += multiply32BitLow(state[i], magicNumbers[i]);
        high += multiply32BitHigh(state[i], magicNumbers[i]);
      }
      high += get32BitHigh(low += state.pop()), low = get32BitLow(low);
      return state.unshift(low), state.pop(), state.push(high), state[0];
    },
    
    nextFloat : function () {
      var high = this.next() * 0x100000;
      var low = this.next() >>> 12;
      return (high + low) / Math.pow(2, 52);
    },
    
    nextIntBetween : function(a, b) {
      if (b < a) {
        b = [a, a = b][0];
        console.log("Warning: nextIntBetween got backwards range");
      }
      return Math.floor(a + this.nextFloat() * (b - a));
    },
    
    reseed : function (s) {
      var i;
      if (!is32Bit(s)) {
        console.log(s + " is not a valid seed. Forcing to 0."), s = 0;
      }
      for (i = 0; i < 5; i++) {
        state.push(s = get32BitLow(multiply32BitLow(29943829, s) + 0xffffffff));
      }
      for (i = 0; i < 100; i++) {
        this.next();
      }
    }
  };
  generator.reseed(seed);
  return generator;
}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

var context = new (window.AudioContext || window.webkitAudioContext)();
reverbjs.extend(context);
var midiQueue;
var playerStartTime;
var timeInAdvanceToSchedule = 0.5;
var predestination = context.destination;
var reverbGain;
var masterGain;
var reverb;

function configureReverb () {
  masterGain = context.createGain();
  masterGain.gain.value = 1.0;
  masterGain.connect(context.destination);

  reverbGain = context.createGain();
  reverbGain.gain.value = 1.0;
  reverbGain.connect(masterGain);
  
  predestination = reverbGain;

  reverb = context.createReverbFromUrl(
    'http://reverbjs.org/Library/UndergroundCarPark.wav',
    function() { console.log('Loaded reverb'); });
  reverbGain.connect(reverb);
  reverb.connect(masterGain);
}

function dBToGain(dB) {
  if (dB <= -100) {
    return 0;
  }
  return Math.pow(10, dB / 10);
}

function frequencyToMIDINoteNumber (frequency) {
  var n = 12 * Math.log(frequency * Math.pow(2, 11 / 4) / 55) / Math.log(2);
  var rounded = Math.round(n * 128) / 128;
  return rounded;
}

function getCurrentTime() {
  return context.currentTime;
}

function getPieceAsMIDI() {
  createPiece();
  exampleData = pieceAsMIDI();
  var csv = pieceAsCSV();
  if (parityChecksum(csv) !== 6820566) {
    alert('Warning: piece has changed!');
  }
  console.log('Parity of CSV: ' + parityChecksum(csv));
  var sortKey = "time";
  exampleData.sort(function(a, b) {
    if (a[sortKey] < b[sortKey]) {
      return -1;
    } else if (a[sortKey] > b[sortKey]) {
      return 1;
    }
    return 0;
  });
  return exampleData;
}

function initialize () {
  configureReverb();
  schedulePiece();
}

function midiNoteNumberToFrequency (midiNoteNumber) {
  return 55 * Math.pow(2, (midiNoteNumber - 33) / 12);
}

function processNextFrame () {
  if (midiQueue.length === 0) {
    return;
  }
  var playerCurrentTime = getCurrentTime() - playerStartTime;
  var playerScheduleTime = playerCurrentTime + timeInAdvanceToSchedule;
  while (midiQueue[0] !== undefined && midiQueue[0].time < playerScheduleTime) {
    var m = midiQueue.shift();
    scheduleInstrumentalNote(m.channel, m.pitch, m.time + playerStartTime,
      m.duration, m.velocity);
  }
  window.requestAnimationFrame(processNextFrame);
}

function scheduleInstrumentalNote (instrument, midiNoteNumber, startTime,
  duration, velocity) {
  if (velocity === undefined) {
    velocity = 0.5;
  } else {
    velocity = Math.min(Math.max(velocity / 127, 0.01), 1);
  }
  var gain = 0.1 * velocity;
  var instruments = [
    scheduleFluteNote,
    scheduleOboeNote,
    scheduleClarinetNote,
    scheduleBassoonNote,
    scheduleHornNote,
    scheduleTrumpetNote,
    scheduleTromboneNote,
    scheduleBaritoneSaxNote,
    scheduleVibraphoneNote,
    scheduleCrotalesNote,
    scheduleViolinNote,
    scheduleViolaNote,
    scheduleCelloNote,
    scheduleDoubleBassNote
  ];
  instruments[instrument](midiNoteNumber, startTime, duration, gain);
}

function schedulePiece () {
  scheduleInstrumentalNote(0, 60, 0, 0, 0); //just to get things going
  midiQueue = getPieceAsMIDI();
  playerStartTime = getCurrentTime() + 1.0;
  processNextFrame();
}

function scheduleOscillator(type, note, startTime, duration, gain, shape) {
  if (startTime < getCurrentTime()) {
    console.log('Warning: dropped note that started in past');
    return;
  }
  var gainShaper = context.createGain();
  gainShaper.gain.value = 0;
  gainShaper.gain.setValueAtTime(0, startTime);
  for (var i in shape) {
    var g = dBToGain(shape[i].dB) * gain;
    var t = startTime + shape[i].time * duration;
    gainShaper.gain.linearRampToValueAtTime(g, t);
  }
  gainShaper.connect(predestination);
  
  var oscillator = context.createOscillator();
  oscillator.type = type;
  oscillator.frequency.value = midiNoteNumberToFrequency(note);
  oscillator.start(startTime);
  oscillator.stop(startTime + duration);
  oscillator.connect(gainShaper);
}

function shutdownGracefully() {
  console.log('Shutting down audio...');
  var start = getCurrentTime(), length = 0.5, progress = 0;
  while (progress <= 1) {
    masterGain.gain.value = 1 - progress;
    progress = (getCurrentTime() - start) / length;
  }
}

////////////////////////////////////////////////////////////////////////////////

if (isRunningUnderNodeJS()) {
  generateInConsole();
}
