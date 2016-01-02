'use strict';

function pieceConfiguration() {
  var p = {};
  p.seed = 133;
  p.loopContinueRate = 5;
  p.codeLength = 10000;
  p.tapeLength = 1024;
  p.loopStep = 100;
  p.loopSkipCreateRate = 3;
  p.loopInnerStartLow = 100;
  p.loopInnerStartHigh = 100;
  p.loopInnerEndLow = 100;
  p.loopInnerEndHigh = 100;
  p.loopOuterEndLow = 50;
  p.loopOuterEndHigh = 50;
  p.longestNote = 4;
  p.probabilityInversionSections = 10;
  p.computationRateInversion = 0.9975;
  p.range = 0;
  p.tempo = 112;
  p.rhythmSixteenth = false;
  p.rhythmTripletEighth = true;
  p.rhythmEighth = true;
  p.rhythmTripletQuarter = true;
  p.rhythmQuarter = false;
  p.wrapDynamics = true;
  p.pitchClass = [
    true, true, true, true,
    true, true, true, true,
    true, true, true, true
  ];
  p.probabilityOf = {};
  p.probabilityOf.NullOp = 0;
  p.probabilityOf.WhileBegin = 0;
  p.probabilityOf.WhileEnd = 0;
  p.probabilityOf.MoveBackward = 20000;
  p.probabilityOf.MoveForward = 20000;
  p.probabilityOf.DecrementData = 20000;
  p.probabilityOf.IncrementData = 20000;
  p.probabilityOf.DecrementDuration = 500;
  p.probabilityOf.IncrementDuration = 500;
  p.probabilityOf.EmitFlute = 40;
  p.probabilityOf.EmitOboe = 40;
  p.probabilityOf.EmitClarinet = 20;
  p.probabilityOf.EmitBassoon = 20;
  p.probabilityOf.EmitHorn = 10;
  p.probabilityOf.EmitTrumpet = 20;
  p.probabilityOf.EmitTrombone = 10;
  p.probabilityOf.EmitBaritoneSax = 50;
  p.probabilityOf.EmitVibraphone = 50;
  p.probabilityOf.EmitCrotales = 10;
  p.probabilityOf.EmitViolin = 50;
  p.probabilityOf.EmitViola = 50;
  p.probabilityOf.EmitCello = 30;
  p.probabilityOf.EmitDoubleBass = 10;
  p.probabilityOf.ToggleWinds = 100;
  p.probabilityOf.ToggleBrass = 100;
  p.probabilityOf.TogglePercussion = 100;
  p.probabilityOf.ToggleStrings = 100;
  p.probabilityOf.FluteSoft = 1;
  p.probabilityOf.FluteLoud = 1;
  p.probabilityOf.FluteSofter = 1;
  p.probabilityOf.FluteLouder = 1;
  p.probabilityOf.OboeSoft = 1;
  p.probabilityOf.OboeLoud = 1;
  p.probabilityOf.OboeSofter = 1;
  p.probabilityOf.OboeLouder = 1;
  p.probabilityOf.ClarinetSoft = 1;
  p.probabilityOf.ClarinetLoud = 1;
  p.probabilityOf.ClarinetSofter = 1;
  p.probabilityOf.ClarinetLouder = 1;
  p.probabilityOf.BassoonSoft = 1;
  p.probabilityOf.BassoonLoud = 1;
  p.probabilityOf.BassoonSofter = 1;
  p.probabilityOf.BassoonLouder = 1;
  p.probabilityOf.HornSoft = 1;
  p.probabilityOf.HornLoud = 1;
  p.probabilityOf.HornSofter = 1;
  p.probabilityOf.HornLouder = 1;
  p.probabilityOf.TrumpetSoft = 1;
  p.probabilityOf.TrumpetLoud = 1;
  p.probabilityOf.TrumpetSofter = 1;
  p.probabilityOf.TrumpetLouder = 1;
  p.probabilityOf.TromboneSoft = 1;
  p.probabilityOf.TromboneLoud = 1;
  p.probabilityOf.TromboneSofter = 1;
  p.probabilityOf.TromboneLouder = 1;
  p.probabilityOf.BaritoneSaxSoft = 1;
  p.probabilityOf.BaritoneSaxLoud = 1;
  p.probabilityOf.BaritoneSaxSofter = 1;
  p.probabilityOf.BaritoneSaxLouder = 1;
  p.probabilityOf.VibraphoneSoft = 1;
  p.probabilityOf.VibraphoneLoud = 1;
  p.probabilityOf.VibraphoneSofter = 1;
  p.probabilityOf.VibraphoneLouder = 1;
  p.probabilityOf.CrotalesSoft = 1;
  p.probabilityOf.CrotalesLoud = 1;
  p.probabilityOf.CrotalesSofter = 1;
  p.probabilityOf.CrotalesLouder = 1;
  p.probabilityOf.ViolinSoft = 1;
  p.probabilityOf.ViolinLoud = 1;
  p.probabilityOf.ViolinSofter = 1;
  p.probabilityOf.ViolinLouder = 1;
  p.probabilityOf.ViolaSoft = 1;
  p.probabilityOf.ViolaLoud = 1;
  p.probabilityOf.ViolaSofter = 1;
  p.probabilityOf.ViolaLouder = 1;
  p.probabilityOf.CelloSoft = 1;
  p.probabilityOf.CelloLoud = 1;
  p.probabilityOf.CelloSofter = 1;
  p.probabilityOf.CelloLouder = 1;
  p.probabilityOf.DoubleBassSoft = 1;
  p.probabilityOf.DoubleBassLoud = 1;
  p.probabilityOf.DoubleBassSofter = 1;
  p.probabilityOf.DoubleBassLouder = 1;
  return p;
}

////////////////////////////////////////////////////////////////////////////////

var piece = {}, probabilities = {}, distribution = {}, random;
var durationIndex = 0;
var durations = [];
var durationLCM = 48;
var instruments = [];
var toggles = [true, true, true, true];
var instructions = [], data = [];
var instructionPointer = 0;
var dataPointer = 0;
var globalTime = 0;
var dynamics = 7;
var dynamic = [0, 1, 2, 3, 4, 5, 6];

var instructionSet = [
  "NullOp", "WhileBegin", "WhileEnd", "MoveBackward", "MoveForward",
  "DecrementData", "IncrementData", "DecrementDuration", "IncrementDuration",
  "EmitFlute", "EmitOboe", "EmitClarinet", "EmitBassoon", "EmitHorn",
  "EmitTrumpet", "EmitTrombone", "EmitBaritoneSax", "EmitVibraphone",
  "EmitCrotales", "EmitViolin", "EmitViola", "EmitCello", "EmitDoubleBass",
  "ToggleWinds", "ToggleBrass", "TogglePercussion", "ToggleStrings",
  "FluteSoft", "FluteLoud", "FluteSofter", "FluteLouder", "OboeSoft",
  "OboeLoud", "OboeSofter", "OboeLouder", "ClarinetSoft", "ClarinetLoud",
  "ClarinetSofter", "ClarinetLouder", "BassoonSoft", "BassoonLoud",
  "BassoonSofter", "BassoonLouder", "HornSoft", "HornLoud", "HornSofter",
  "HornLouder", "TrumpetSoft", "TrumpetLoud", "TrumpetSofter", "TrumpetLouder",
  "TromboneSoft", "TromboneLoud", "TromboneSofter", "TromboneLouder",
  "BaritoneSaxSoft", "BaritoneSaxLoud", "BaritoneSaxSofter",
  "BaritoneSaxLouder", "VibraphoneSoft", "VibraphoneLoud",
  "VibraphoneSofter", "VibraphoneLouder", "CrotalesSoft", "CrotalesLoud",
  "CrotalesSofter", "CrotalesLouder", "ViolinSoft", "ViolinLoud",
  "ViolinSofter", "ViolinLouder", "ViolaSoft", "ViolaLoud", "ViolaSofter",
  "ViolaLouder", "CelloSoft", "CelloLoud", "CelloSofter", "CelloLouder",
  "DoubleBassSoft", "DoubleBassLoud", "DoubleBassSofter", "DoubleBassLouder",
  "InstructionCount"
];

var indexOf = (function () {
  var x = {}, i;
  for (i = 0; i < instructionSet.length; i += 1) {
    x[instructionSet[i]] = i;
  }
  return x;
}());

function distributeProbabilities(inversionProbability) {
  var inversionAmount = piece.computationRateInversion * inversionProbability,
    sum = 0,
    instruction;
  distribution = {};
  for (instruction in probabilities) {
    if (probabilities.hasOwnProperty(instruction)) {
      distribution[instruction] = probabilities[instruction];
    }
  }

  // Apply probability inversion if being used.
  distribution.MoveBackward -= inversionAmount * distribution.MoveBackward;
  distribution.MoveForward -= inversionAmount * distribution.MoveForward;
  distribution.DecrementData -= inversionAmount * distribution.DecrementData;
  distribution.IncrementData -= inversionAmount * distribution.IncrementData;

  // Turn the probabilities into a distribution.
  for (instruction in distribution) {
    if (distribution.hasOwnProperty(instruction)) {
      sum += distribution[instruction];
      distribution[instruction] = sum;
    }
  }

  // Normalize the distribution.
  for (instruction in distribution) {
    if (distribution.hasOwnProperty(instruction)) {
      distribution[instruction] /= sum;
    }
  }
}

function createDurations() {
  if (piece.rhythmSixteenth) {
    durations.push(durationLCM / 16);
  }
  if (piece.rhythmTripletEighth) {
    durations.push(durationLCM / 12);
  }
  if (piece.rhythmEighth) {
    durations.push(durationLCM / 8);
  }
  if (piece.rhythmTripletQuarter) {
    durations.push(durationLCM / 6);
  }
  if (piece.rhythmQuarter) {
    durations.push(durationLCM / 4);
  }
}

function makeInstrument(index, group, name, low, high) {
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

function createInstruments() {
  var i = [];
  i.push(makeInstrument(0,  0, "Flute",       67, 98 + piece.range)); //G4-D6
  i.push(makeInstrument(1,  0, "Oboe",        60, 84 + piece.range)); //C4-C6
  i.push(makeInstrument(2,  0, "Clarinet",    50, 79 + piece.range)); //D3-G5
  i.push(makeInstrument(3,  0, "Bassoon",     36, 67 + piece.range)); //C2-G4
  i.push(makeInstrument(4,  1, "Horn",        48, 72 + piece.range)); //C3-C5
  i.push(makeInstrument(5,  1, "Trumpet",     55, 79 + piece.range)); //G3-G5
  i.push(makeInstrument(6,  1, "Trombone",    43, 67 + piece.range)); //G2-G4
  i.push(makeInstrument(7,  1, "BaritoneSax", 43, 60 + piece.range)); //G2-C4
  i.push(makeInstrument(8,  2, "Vibraphone",  53, 89));               //F3-F6
  i.push(makeInstrument(9,  2, "Crotales",    60, 84));               //C2-C4
  i.push(makeInstrument(10, 3, "Violin",      55, 84 + piece.range)); //G3-C6
  i.push(makeInstrument(11, 3, "Viola",       48, 79 + piece.range)); //C3-G5
  i.push(makeInstrument(12, 3, "Cello",       36, 67 + piece.range)); //C2-G5
  i.push(makeInstrument(13, 3, "DoubleBass",  28, 48 + piece.range)); //E2-C4
  instruments = i;

  /*Backwards compatibility to express original behavior where Violin was
  considered part of the percussion group for toggling. This could be removed.*/
  instruments[10].group = 2;
}

function planLoops() {
  var a = piece.loopInnerStartLow,
    b = a + piece.loopInnerStartHigh,
    c = b + piece.loopInnerEndLow,
    d = c + piece.loopInnerEndHigh,
    e = d + piece.loopOuterEndLow,
    f = e + piece.loopOuterEndHigh,
    g = f + piece.loopStep,
    i,
    whileBegin = indexOf.WhileBegin,
    whileEnd = indexOf.WhileEnd;
  for (i = 0; i < instructions.length - g; i += 1) {
    if (random.nextIntBetween(0, piece.loopSkipCreateRate) === 0) {
      instructions[i] = whileBegin;
      instructions[i + random.nextIntBetween(e, f)] = whileEnd;
      instructions[i + random.nextIntBetween(a, b)] = whileBegin;
      instructions[i + random.nextIntBetween(c, d)] = whileEnd;
      i += g;
    }
  }
}

function getProbableInstruction(normalizedNumber) {
  var k, bestKey = 'NullOp', lowestValue = 2; //i.e. a number > 1
  for (k in distribution) {
    if (distribution.hasOwnProperty(k)) {
      if (normalizedNumber < distribution[k] &&
          distribution[k] < lowestValue) {
        lowestValue = distribution[k];
        bestKey = k;
      }
    }
  }
  return indexOf[bestKey];
}

function planInstructions() {
  var i, n = instructions.length, inversionProbability;
  for (i = 0; i < n; i += 1) {
    inversionProbability = (Math.floor(i / Math.floor(n /
      piece.probabilityInversionSections)) % 2);
    distributeProbabilities(inversionProbability);
    if (instructions[i] === 0) {
      instructions[i] = getProbableInstruction(random.nextFloat());
    }
  }
}

function halt() {
  return instructionPointer >= instructions.length || instructionPointer < 0;
}

function getInstruction() {
  return instructionSet[instructions[instructionPointer]];
}

function getCyclicDataPointer() {
  return (dataPointer + data.length * Math.abs(dataPointer)) % data.length;
}

function getData() {
  return data[getCyclicDataPointer()];
}

function addToData(amount) {
  var x = getCyclicDataPointer();
  data[x] = (data[x] + amount + 256) % 256;
}

function lookupPitch(instrument, p) {
  var x, i, noteStart = instrument.low;
  x = p < 128 ? p : p - 256;

  if (instrument.low === instrument.high) {
    return instrument.low;
  }

  // Find the first C and make that 0.
  if (noteStart % 12 !== 0) {
    noteStart += (12 - (instrument.low % 12));
  }

  if (x === 0) {
    return noteStart;
  }

  if (x > 0) {
    for (i = 0; i < x; i += 1) {
      noteStart += 1;
      while (!piece.pitchClass[noteStart % 12]) { noteStart += 1; }

      //Octave down as far as possible if out of range.
      if (noteStart > instrument.high) {
        while (noteStart - 12 >= instrument.low) {
          noteStart -= 12;
        }
      }
    }
  } else {
    for (i = 0; i < -x; i += 1) {
      noteStart -= 1;
      while (!piece.pitchClass[noteStart % 12]) { noteStart -= 1; }

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

function makeNote(offset, duration, pitch, dynamicMark) {
  var n = {
    "time": offset,
    "duration": duration,
    "pitch": pitch,
    "dynamicMark": dynamicMark
  };
  return n;
}

function addNote(instrument, data) {
  var instrumentIsOn = toggles[instrument.group],
    actualPitch = lookupPitch(instrument, data),
    duration,
    longestNote;
  if (instrument.offset === globalTime) {
    duration = durations[durationIndex];
    if (instrumentIsOn) {
      instrument.notes.push(makeNote(instrument.offset, duration,
        actualPitch, dynamic[instrument.dynamicMark]));
    }
    instrument.offset += duration;
    globalTime = instrument.offset;
  } else if (instrument.offset < globalTime) {
    longestNote = piece.longestNote * durationLCM / 4;
    if (globalTime - instrument.offset > longestNote) {
      instrument.offset = globalTime - longestNote;
    }
    duration = globalTime - instrument.offset;
    if (instrumentIsOn) {
      instrument.notes.push(makeNote(instrument.offset, duration,
        actualPitch, dynamic[instrument.dynamicMark]));
    }
    instrument.offset += duration;
  }
}

function emit(i) {
  var index = indexOf[i], instrumentId, indexToToggle,
    dynamicId, dynamicType, dynamicInstrument, dynamicMark;
  if (i === 'DecrementDuration') {
    durationIndex = Math.max(0, durationIndex - 1);
  } else if (i === 'IncrementDuration') {
    durationIndex = Math.min(durations.length - 1, durationIndex + 1);
  } else if (index >= indexOf.EmitFlute &&
             index <= indexOf.EmitDoubleBass) {
    instrumentId = index - indexOf.EmitFlute;
    addNote(instruments[instrumentId], getData());
  } else if (index >= indexOf.ToggleWinds &&
             index <= indexOf.ToggleStrings) {
    indexToToggle = index - indexOf.ToggleWinds;
    toggles[indexToToggle] = !toggles[indexToToggle];
    if (!toggles[0] && !toggles[1] && !toggles[2] && !toggles[3]) {
      toggles = [true, true, true, true];
    }
  } else if (index >= indexOf.FluteSoft && index <= indexOf.DoubleBassLouder) {
    dynamicId = index - indexOf.FluteSoft;
    dynamicType = dynamicId % 4;
    dynamicInstrument = (dynamicId - dynamicType) / 4;
    dynamicMark = instruments[dynamicInstrument].dynamicMark;
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

function performInstruction() {
  if (halt()) {
    return false;
  }
  var i = getInstruction(), braceCount;
  if (i === "MoveForward") {
    dataPointer += 1;
  } else if (i === "MoveBackward") {
    dataPointer -= 1;
  } else if (i === "IncrementData") {
    addToData(1);
  } else if (i === "DecrementData") {
    addToData(-1);
  } else if ((i === "WhileBegin" && !getData()) || (i === "WhileEnd" && getData())) {
    if (i !== "WhileEnd" || random.nextIntBetween(0, piece.loopContinueRate)) {
      //Perform jump operation to emulate while loops.
      braceCount = 1;
      do {
        instructionPointer += (i === "WhileBegin" ? 1 : -1);
        if (halt()) {
          return false;
        }
        if (getInstruction() === (i === "WhileBegin" ? "WhileEnd" : "WhileBegin")) {
          braceCount -= 1;
        } else if (getInstruction() === (i === "WhileEnd" ? "WhileEnd" : "WhileBegin")) {
          braceCount += 1;
        }
      } while (braceCount > 0);
    }
  } else {
    emit(i);
  }
  instructionPointer += 1;
  return true;
}

function createMultiplyWithCarryPRNG(seed) {
  function get32BitLow(x) {
    return x >>> 0;
  }

  function get32BitHigh(x) {
    return (x - get32BitLow(x)) / 0x100000000;
  }

  function is32Bit(x) {
    return x >= 0 && x < 0x100000000 && x === Math.floor(x);
  }

  function multiply32BitHigh(a, b) {
    return get32BitHigh(get32BitLow(a) * get32BitLow(b));
  }

  function multiply32BitLow(a, b) {
    var ah = (get32BitLow(a) >>> 16) & 0xffff, al = get32BitLow(a) & 0xffff,
      bh = (get32BitLow(b) >>> 16) & 0xffff, bl = get32BitLow(b) & 0xffff;
    return ((al * bl) + ((ah * bl + al * bh) << 16) >>> 0);
  }

  var state = [], generator = {
    next : function () {
      var magicNumbers = [5115, 1776, 1492, 2111111111], low = 0, high = 0, i;
      for (i = 0; i < magicNumbers.length; i += 1) {
        low += multiply32BitLow(state[i], magicNumbers[i]);
        high += multiply32BitHigh(state[i], magicNumbers[i]);
      }
      low += state.pop();
      high += get32BitHigh(low);
      low = get32BitLow(low);
      state.unshift(low);
      state.pop();
      state.push(high);
      return state[0];
    },

    nextFloat : function () {
      var high = this.next() * 0x100000,
        low = this.next() >>> 12;
      return (high + low) / Math.pow(2, 52);
    },

    nextIntBetween : function (a, b) {
      return Math.floor(a + this.nextFloat() * (b - a));
    },

    reseed : function (s) {
      var i;
      if (!is32Bit(s)) {
        console.log(s + " is not a valid seed. Forcing to 0.");
        s = 0;
      }
      for (i = 0; i < 5; i += 1) {
        s = get32BitLow(multiply32BitLow(29943829, s) + 0xffffffff);
        state.push(s);
      }
      for (i = 0; i < 100; i += 1) {
        this.next();
      }
    }
  };
  generator.reseed(seed);
  return generator;
}

function createPiece(pieceToUse) {
  piece = pieceToUse;
  probabilities = pieceToUse.probabilityOf;

  // Initialize random number generator;
  random = createMultiplyWithCarryPRNG(piece.seed);

  // Initialize constants and distributions.
  createDurations();
  createInstruments();

  // Initialize state and maps.
  var i, shouldContinue = true;
  for (i = 0; i < piece.codeLength; i += 1) { instructions[i] = 0; }
  for (i = 0; i < piece.tapeLength; i += 1) { data[i] = 0; }

  planLoops();
  planInstructions();
  while (shouldContinue) {
    shouldContinue = performInstruction();
  }
}

function pieceAsCSV() {
  var i, j, pieceString = 'Instrument,Channel,Start,Duration,Key,Dynamic\n',
    instrument, note;
  for (i = 0; i < instruments.length; i += 1) {
    instrument = instruments[i];
    for (j = 0; j < instrument.notes.length; j += 1) {
      note = instrument.notes[j];
      pieceString += instrument.name + ',' + instrument.index + ',' +
        note.time + ',' + note.duration + ',' + note.pitch + ',' +
        note.dynamicMark + '\n';
    }
  }
  return pieceString.trim();
}

function noteTimeToSeconds(noteTime) {
  return noteTime * 4 * 60 / piece.tempo / durationLCM;
}

function dynamicMarkToVelocity(dynamicMark) {
  return Math.round(dynamicMark / 7 * 87) + 20;
}

function pieceAsMIDI() {
  var midiData = [], instrument, note, i, j;
  for (i = 0; i < instruments.length; i += 1) {
    instrument = instruments[i];
    for (j = 0; j < instrument.notes.length; j += 1) {
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

function parityChecksum(s) {
  var parity = 0, i;
  for (i = 0; i < s.length; i += 1) {
    parity = (parity + s.charCodeAt(i)) >>> 0;
  }
  return parity;
}

////////////////////////////////////////////////////////////////////////////////

function isRunningUnderNodeJS() {
  var isNodeJS = false, typeOfGlobal = typeof global;
  if (typeOfGlobal !== "undefined") {
    if (Object.prototype.toString.call(global.process) === '[object process]') {
      isNodeJS = true;
    }
  }
  return isNodeJS;
}

function generateInConsole() {
  createPiece(pieceConfiguration());
  var finalPiece = pieceAsCSV();
  console.log('CSV of piece:\n' + finalPiece);
  console.log('Parity of CSV: ' + parityChecksum(finalPiece));
  if (parityChecksum(finalPiece) !== 6820566) {
    console.log('WARNING: piece does not match reference');
  }
}

function dBToGain(dB) {
  if (dB <= -100) {
    return 0;
  }
  return Math.pow(10, dB / 10);
}

var context;
var midiQueue;
var playerStartTime;
var timeInAdvanceToSchedule = 0.5;
var predestination;
var reverbGain;
var masterGain;
var reverb;

function getCurrentTime() {
  return context.currentTime;
}

function midiNoteNumberToFrequency(midiNoteNumber) {
  return 55 * Math.pow(2, (midiNoteNumber - 33) / 12);
}

function scheduleOscillator(type, note, startTime, duration, gain, shape) {
  if (startTime < getCurrentTime()) {
    console.log('Warning: dropped note that started in past');
    return;
  }
  var gainShaper = context.createGain(), i, g, t, oscillator;
  gainShaper.gain.value = 0;
  gainShaper.gain.setValueAtTime(0, startTime);
  for (i in shape) {
    if (shape.hasOwnProperty(i)) {
      g = dBToGain(shape[i].dB) * gain;
      t = startTime + shape[i].time * duration;
      gainShaper.gain.linearRampToValueAtTime(g, t);
    }
  }
  gainShaper.connect(predestination);

  oscillator = context.createOscillator();
  oscillator.type = type;
  oscillator.frequency.value = midiNoteNumberToFrequency(note);
  oscillator.start(startTime);
  oscillator.stop(startTime + duration);
  oscillator.connect(gainShaper);
}

////////////////////////////////////////////////////////////////////////////////

function scheduleFluteNote(note, start, duration, gain) {
  gain /= dBToGain(-28);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time: 0.3, dB: -32}, {time: 0.9, dB: -32}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time: 0.1, dB: -38}, {time: 0.9, dB: -38}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.3, dB: -42}, {time: 0.9, dB: -42}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 36, start, duration, gain,
    [{time: 0.3, dB: -48}, {time: 0.9, dB: -48}, {time: 1.0, dB: -100}]);
}

function scheduleOboeNote(note, start, duration, gain) {
  gain /= dBToGain(-47);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time: 0.1, dB: -50}, {time: 0.9, dB: -50}, {time: 1.0, dB: -100}]);
  scheduleOscillator('triangle', note + 12, start, duration, gain,
    [{time: 0.1, dB: -55}, {time: 0.9, dB: -55}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.3, dB: -60}, {time: 0.9, dB: -60}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 36, start, duration, gain,
    [{time: 0.3, dB: -65}, {time: 0.9, dB: -65}, {time: 1.0, dB: -100}]);
}

function scheduleClarinetNote(note, start, duration, gain) {
  gain /= dBToGain(-50);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time: 0.1, dB: -79}, {time: 0.9, dB: -79}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time: 0.1, dB: -65}, {time: 0.9, dB: -65}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.3, dB: -50}, {time: 0.9, dB: -50}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 36, start, duration, gain,
    [{time: 0.3, dB: -55}, {time: 0.9, dB: -55}, {time: 1.0, dB: -100}]);
}

function scheduleBassoonNote(note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time: 0.05, dB: -65}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time: 0.05, dB: -68}, {time: 0.95, dB: -68}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.05, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 48, start, duration, gain,
    [{time: 0.05, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
}

function scheduleHornNote(note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time: 0.05, dB: -65}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
  scheduleOscillator('triangle', note + 12, start, duration, gain,
    [{time: 0.05, dB: -68}, {time: 0.95, dB: -68}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 48, start, duration, gain,
    [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
}

function scheduleTromboneNote(note, start, duration, gain) {
  gain /= dBToGain(-58);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time: 0.05, dB: -65}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time: 0.05, dB: -55}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
}

function scheduleTrumpetNote(note, start, duration, gain) {
  gain /= dBToGain(-50);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time: 0.05, dB: -65}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time: 0.05, dB: -55}, {time: 0.95, dB: -60}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
}

function scheduleBaritoneSaxNote(note, start, duration, gain) {
  gain /= dBToGain(-50);
  scheduleOscillator('square', note, start, duration, gain,
    [{time: 0.05, dB: -62}, {time: 0.15, dB: -65}, {time: 0.95, dB: -65},
      {time: 1.0, dB: -100}]);
  scheduleOscillator('triangle', note + 12, start, duration, gain,
    [{time: 0.05, dB: -52}, {time: 0.15, dB: -55}, {time: 0.95, dB: -55},
      {time: 1.0, dB: -100}]);
  scheduleOscillator('triangle', note + 24, start, duration, gain,
    [{time: 0.05, dB: -58}, {time: 0.15, dB: -58}, {time: 0.95, dB: -58},
      {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 48, start, duration, gain,
    [{time: 0.05, dB: -75}, {time: 0.15, dB: -75}, {time: 0.95, dB: -75},
      {time: 1.0, dB: -100}]);
}

function scheduleVibraphoneNote(note, start, duration, gain) {
  gain /= dBToGain(-6);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time: 0.05, dB: -3}, {time: 0.15, dB: -12}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time: 0.05, dB: -6}, {time: 0.15, dB: -6}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.05, dB: -12}, {time: 0.15, dB: -42}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 48, start, duration, gain,
    [{time: 0.05, dB: -24}, {time: 0.15, dB: -54}, {time: 1.0, dB: -100}]);
}

function scheduleCrotalesNote(note, start, duration, gain) {
  gain /= dBToGain(-12);
  scheduleOscillator('sine', note, start, duration, gain,
    [{time: 0.01, dB: -3}, {time: 0.05, dB: -30}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 12, start, duration, gain,
    [{time: 0.05, dB: -6}, {time: 0.15, dB: -12}, {time: 1.0, dB: -100}]);
  scheduleOscillator('triangle', note + 24, start, duration, gain,
    [{time: 0.01, dB: -12}, {time: 0.05, dB: -30}, {time: 1.0, dB: -100}]);
  scheduleOscillator('triangle', note + 48, start, duration, gain,
    [{time: 0.01, dB: -24}, {time: 0.05, dB: -30}, {time: 1.0, dB: -100}]);
}

function scheduleViolinNote(note, start, duration, gain) {
  gain /= dBToGain(-55);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time: 0.05, dB: -85}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time: 0.05, dB: -85}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
}

function scheduleViolaNote(note, start, duration, gain) {
  gain /= dBToGain(-50);
  scheduleOscillator('triangle', note, start, duration, gain,
    [{time: 0.05, dB: -85}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sawtooth', note + 12, start, duration, gain,
    [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sine', note + 24, start, duration, gain,
    [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
  scheduleOscillator('square', note + 48, start, duration, gain,
    [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
}

function scheduleCelloNote(note, start, duration, gain) {
  gain /= dBToGain(-50);
  scheduleOscillator('triangle', note - 12, start, duration, gain,
    [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sawtooth', note, start, duration, gain,
    [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
}

function scheduleDoubleBassNote(note, start, duration, gain) {
  gain /= dBToGain(-50);
  scheduleOscillator('sawtooth', note - 12, start, duration, gain,
    [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
  scheduleOscillator('sawtooth', note, start, duration, gain,
    [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
}

////////////////////////////////////////////////////////////////////////////////

function configureReverb() {
  masterGain = context.createGain();
  masterGain.gain.value = 0.5;
  masterGain.connect(context.destination);

  reverbGain = context.createGain();
  reverbGain.gain.value = 1.0;
  reverbGain.connect(masterGain);

  predestination = reverbGain;

  reverb = context.createReverbFromUrl(
    'http://reverbjs.org/Library/R1NuclearReactorHall.wav',
    function () { console.log('Loaded reverb'); }
  );
  reverbGain.connect(reverb);
  reverb.connect(masterGain);
}

function frequencyToMIDINoteNumber(frequency) {
  var n = 12 * Math.log(frequency * Math.pow(2, 11 / 4) / 55) / Math.log(2),
    rounded = Math.round(n * 128) / 128;
  return rounded;
}

function getPieceAsMIDILikeData() {
  createPiece(pieceConfiguration());
  var pieceData = pieceAsMIDI(), csv = pieceAsCSV(), sortKey = "time";
  if (parityChecksum(csv) !== 6820566) {
    console.log('Warning: piece differs from original Steal This Piece');
  }
  console.log('Parity of CSV: ' + parityChecksum(csv));
  pieceData.sort(function (a, b) {
    if (a[sortKey] < b[sortKey]) {
      return -1;
    }
    if (a[sortKey] > b[sortKey]) {
      return 1;
    }
    return 0;
  });
  return pieceData;
}

function scheduleInstrumentalNote(instrument, midiNoteNumber, startTime,
  duration, velocity) {
  if (velocity === undefined) {
    velocity = 0.5;
  } else {
    velocity = Math.min(Math.max(velocity / 127, 0.01), 1);
  }
  var gain = 0.1 * velocity, instruments = [
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

/*global window, reverbjs*/

function processNextFrame() {
  if (midiQueue.length === 0) {
    return;
  }
  var playerCurrentTime = getCurrentTime() - playerStartTime,
    playerScheduleTime = playerCurrentTime + timeInAdvanceToSchedule,
    m;
  while (midiQueue[0] !== undefined && midiQueue[0].time < playerScheduleTime) {
    m = midiQueue.shift();
    scheduleInstrumentalNote(m.channel, m.pitch, m.time + playerStartTime,
      m.duration, m.velocity);
  }
  window.requestAnimationFrame(processNextFrame);
}

function schedulePiece() {
  scheduleInstrumentalNote(0, 60, 0, 0, 0); //just to get things going
  midiQueue = getPieceAsMIDILikeData();
  playerStartTime = getCurrentTime() + 1.0;
  processNextFrame();
}

function initialize() {
  if (window.AudioContext) {
    context = new window.AudioContext();
  } else {
    context = new window.webkitAudioContext();
  }
  reverbjs.extend(context);
  predestination = context.destination;
  configureReverb();
  schedulePiece();
}

function shutdownGracefully() {
  var start = getCurrentTime(), length = 0.5, progress = 0;
  while (progress <= 1) {
    masterGain.gain.value = (1 - progress) * 0.5;
    progress = (getCurrentTime() - start) / length;
  }
}

////////////////////////////////////////////////////////////////////////////////

if (isRunningUnderNodeJS()) {
  generateInConsole();
}
