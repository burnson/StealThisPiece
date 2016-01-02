'use strict';

var pieceConfiguration = {
  seed: 133,
  loopContinueRate: 5,
  codeLength: 10000,
  tapeLength: 1024,
  loopStep: 100,
  loopSkipCreateRate: 3,
  loopInnerStartLow: 100,
  loopInnerStartHigh: 100,
  loopInnerEndLow: 100,
  loopInnerEndHigh: 100,
  loopOuterEndLow: 50,
  loopOuterEndHigh: 50,
  longestNote: 4,
  probabilityInversionSections: 10,
  computationRateInversion: 0.9975,
  range: 0,
  tempo: 112,
  rhythmSixteenth: false,
  rhythmTripletEighth: true,
  rhythmEighth: true,
  rhythmTripletQuarter: true,
  rhythmQuarter: false,
  wrapDynamics: true,
  pitchClass: [
    true, true, true, true,
    true, true, true, true,
    true, true, true, true
  ],
  probabilityOf: {
    NullOp: 0,
    WhileBegin: 0,
    WhileEnd: 0,
    MoveBackward: 20000,
    MoveForward: 20000,
    DecrementData: 20000,
    IncrementData: 20000,
    DecrementDuration: 500,
    IncrementDuration: 500,
    EmitFlute: 40,
    EmitOboe: 40,
    EmitClarinet: 20,
    EmitBassoon: 20,
    EmitHorn: 10,
    EmitTrumpet: 20,
    EmitTrombone: 10,
    EmitBaritoneSax: 50,
    EmitVibraphone: 50,
    EmitCrotales: 10,
    EmitViolin: 50,
    EmitViola: 50,
    EmitCello: 30,
    EmitDoubleBass: 10,
    ToggleWinds: 100,
    ToggleBrass: 100,
    TogglePercussion: 100,
    ToggleStrings: 100,
    FluteSoft: 1,
    FluteLoud: 1,
    FluteSofter: 1,
    FluteLouder: 1,
    OboeSoft: 1,
    OboeLoud: 1,
    OboeSofter: 1,
    OboeLouder: 1,
    ClarinetSoft: 1,
    ClarinetLoud: 1,
    ClarinetSofter: 1,
    ClarinetLouder: 1,
    BassoonSoft: 1,
    BassoonLoud: 1,
    BassoonSofter: 1,
    BassoonLouder: 1,
    HornSoft: 1,
    HornLoud: 1,
    HornSofter: 1,
    HornLouder: 1,
    TrumpetSoft: 1,
    TrumpetLoud: 1,
    TrumpetSofter: 1,
    TrumpetLouder: 1,
    TromboneSoft: 1,
    TromboneLoud: 1,
    TromboneSofter: 1,
    TromboneLouder: 1,
    BaritoneSaxSoft: 1,
    BaritoneSaxLoud: 1,
    BaritoneSaxSofter: 1,
    BaritoneSaxLouder: 1,
    VibraphoneSoft: 1,
    VibraphoneLoud: 1,
    VibraphoneSofter: 1,
    VibraphoneLouder: 1,
    CrotalesSoft: 1,
    CrotalesLoud: 1,
    CrotalesSofter: 1,
    CrotalesLouder: 1,
    ViolinSoft: 1,
    ViolinLoud: 1,
    ViolinSofter: 1,
    ViolinLouder: 1,
    ViolaSoft: 1,
    ViolaLoud: 1,
    ViolaSofter: 1,
    ViolaLouder: 1,
    CelloSoft: 1,
    CelloLoud: 1,
    CelloSofter: 1,
    CelloLouder: 1,
    DoubleBassSoft: 1,
    DoubleBassLoud: 1,
    DoubleBassSofter: 1,
    DoubleBassLouder: 1
  }
};

////////////////////////////////////////////////////////////////////////////////

var PieceGenerator = function PieceGenerator(configuration) {
  this.data = [];
  this.dataPointer = 0;
  this.distribution = {};
  this.durationIndex = 0;
  this.durationLCM = 48;
  this.durations = [];
  this.dynamic = [0, 1, 2, 3, 4, 5, 6];
  this.dynamics = 7;
  this.globalTime = 0;
  this.instructionPointer = 0;
  this.instructions = [];
  this.instruments = [];
  this.piece = configuration;
  this.probabilities = configuration.probabilityOf;
  this.random = null;
  this.toggles = [true, true, true, true];

  this.instructionSet = [
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
    "HornLouder", "TrumpetSoft", "TrumpetLoud", "TrumpetSofter",
    "TrumpetLouder", "TromboneSoft", "TromboneLoud", "TromboneSofter",
    "TromboneLouder", "BaritoneSaxSoft", "BaritoneSaxLoud", "BaritoneSaxSofter",
    "BaritoneSaxLouder", "VibraphoneSoft", "VibraphoneLoud",
    "VibraphoneSofter", "VibraphoneLouder", "CrotalesSoft", "CrotalesLoud",
    "CrotalesSofter", "CrotalesLouder", "ViolinSoft", "ViolinLoud",
    "ViolinSofter", "ViolinLouder", "ViolaSoft", "ViolaLoud", "ViolaSofter",
    "ViolaLouder", "CelloSoft", "CelloLoud", "CelloSofter", "CelloLouder",
    "DoubleBassSoft", "DoubleBassLoud", "DoubleBassSofter", "DoubleBassLouder",
    "InstructionCount"
  ];

  this.indexOf = (function (that) {
    var x = {}, i;
    for (i = 0; i < that.instructionSet.length; i += 1) {
      x[that.instructionSet[i]] = i;
    }
    return x;
  }(this));

  this.distributeProbabilities = function (inversionProbability) {
    var inversionAmount = this.piece.computationRateInversion * inversionProbability,
      sum = 0,
      instruction;
    this.distribution = {};
    for (instruction in this.probabilities) {
      if (this.probabilities.hasOwnProperty(instruction)) {
        this.distribution[instruction] = this.probabilities[instruction];
      }
    }

    // Apply probability inversion if being used.
    this.distribution.MoveBackward -= inversionAmount * this.distribution.MoveBackward;
    this.distribution.MoveForward -= inversionAmount * this.distribution.MoveForward;
    this.distribution.DecrementData -= inversionAmount * this.distribution.DecrementData;
    this.distribution.IncrementData -= inversionAmount * this.distribution.IncrementData;

    // Distribute the probabilities.
    for (instruction in this.distribution) {
      if (this.distribution.hasOwnProperty(instruction)) {
        sum += this.distribution[instruction];
        this.distribution[instruction] = sum;
      }
    }

    // Normalize the distribution.
    for (instruction in this.distribution) {
      if (this.distribution.hasOwnProperty(instruction)) {
        this.distribution[instruction] /= sum;
      }
    }
  };

  this.createDurations = function () {
    if (this.piece.rhythmSixteenth) {
      this.durations.push(this.durationLCM / 16);
    }
    if (this.piece.rhythmTripletEighth) {
      this.durations.push(this.durationLCM / 12);
    }
    if (this.piece.rhythmEighth) {
      this.durations.push(this.durationLCM / 8);
    }
    if (this.piece.rhythmTripletQuarter) {
      this.durations.push(this.durationLCM / 6);
    }
    if (this.piece.rhythmQuarter) {
      this.durations.push(this.durationLCM / 4);
    }
  };

  this.makeInstrument = function (index, group, name, low, high) {
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
  };

  this.createInstruments = function () {
    var i = [];
    i.push(this.makeInstrument(0,  0, "Flute",       67, 98 + this.piece.range)); //G4-D6
    i.push(this.makeInstrument(1,  0, "Oboe",        60, 84 + this.piece.range)); //C4-C6
    i.push(this.makeInstrument(2,  0, "Clarinet",    50, 79 + this.piece.range)); //D3-G5
    i.push(this.makeInstrument(3,  0, "Bassoon",     36, 67 + this.piece.range)); //C2-G4
    i.push(this.makeInstrument(4,  1, "Horn",        48, 72 + this.piece.range)); //C3-C5
    i.push(this.makeInstrument(5,  1, "Trumpet",     55, 79 + this.piece.range)); //G3-G5
    i.push(this.makeInstrument(6,  1, "Trombone",    43, 67 + this.piece.range)); //G2-G4
    i.push(this.makeInstrument(7,  1, "BaritoneSax", 43, 60 + this.piece.range)); //G2-C4
    i.push(this.makeInstrument(8,  2, "Vibraphone",  53, 89));               //F3-F6
    i.push(this.makeInstrument(9,  2, "Crotales",    60, 84));               //C2-C4
    i.push(this.makeInstrument(10, 3, "Violin",      55, 84 + this.piece.range)); //G3-C6
    i.push(this.makeInstrument(11, 3, "Viola",       48, 79 + this.piece.range)); //C3-G5
    i.push(this.makeInstrument(12, 3, "Cello",       36, 67 + this.piece.range)); //C2-G5
    i.push(this.makeInstrument(13, 3, "DoubleBass",  28, 48 + this.piece.range)); //E2-C4
    this.instruments = i;

    /*Backwards compatibility to express original behavior where Violin was
    considered part of the percussion group for toggling. This could be removed.*/
    this.instruments[10].group = 2;
  };

  this.planLoops = function () {
    var a = this.piece.loopInnerStartLow,
      b = a + this.piece.loopInnerStartHigh,
      c = b + this.piece.loopInnerEndLow,
      d = c + this.piece.loopInnerEndHigh,
      e = d + this.piece.loopOuterEndLow,
      f = e + this.piece.loopOuterEndHigh,
      g = f + this.piece.loopStep,
      i,
      whileBegin = this.indexOf.WhileBegin,
      whileEnd = this.indexOf.WhileEnd;
    for (i = 0; i < this.instructions.length - g; i += 1) {
      if (this.random.nextIntBetween(0, this.piece.loopSkipCreateRate) === 0) {
        this.instructions[i] = whileBegin;
        this.instructions[i + this.random.nextIntBetween(e, f)] = whileEnd;
        this.instructions[i + this.random.nextIntBetween(a, b)] = whileBegin;
        this.instructions[i + this.random.nextIntBetween(c, d)] = whileEnd;
        i += g;
      }
    }
  };

  this.getProbableInstruction = function (normalizedNumber) {
    var k, bestKey = 'NullOp', lowestValue = 2; //i.e. a number > 1
    for (k in this.distribution) {
      if (this.distribution.hasOwnProperty(k)) {
        if (normalizedNumber < this.distribution[k] &&
            this.distribution[k] < lowestValue) {
          lowestValue = this.distribution[k];
          bestKey = k;
        }
      }
    }
    return this.indexOf[bestKey];
  };

  this.planInstructions = function () {
    var i, n = this.instructions.length, inversionProbability;
    for (i = 0; i < n; i += 1) {
      inversionProbability = (Math.floor(i / Math.floor(n /
        this.piece.probabilityInversionSections)) % 2);
      this.distributeProbabilities(inversionProbability);
      if (this.instructions[i] === 0) {
        this.instructions[i] = this.getProbableInstruction(this.random.nextFloat());
      }
    }
  };

  this.halt = function () {
    return this.instructionPointer >= this.instructions.length || this.instructionPointer < 0;
  };

  this.getInstruction = function () {
    return this.instructionSet[this.instructions[this.instructionPointer]];
  };

  this.getCyclicDataPointer = function () {
    return (this.dataPointer + this.data.length * Math.abs(this.dataPointer)) % this.data.length;
  };

  this.getData = function () {
    return this.data[this.getCyclicDataPointer()];
  };

  this.addToData = function (amount) {
    var x = this.getCyclicDataPointer();
    this.data[x] = (this.data[x] + amount + 256) % 256;
  };

  this.lookupPitch = function (instrument, p) {
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
        while (!this.piece.pitchClass[noteStart % 12]) { noteStart += 1; }

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
        while (!this.piece.pitchClass[noteStart % 12]) { noteStart -= 1; }

        //Octave up as far as possible if out of range.
        if (noteStart < instrument.low) {
          while (noteStart + 12 <= instrument.high) {
            noteStart += 12;
          }
        }
      }
    }
    return noteStart;
  };

  this.makeNote = function (offset, duration, pitch, dynamicMark) {
    var n = {
      "time": offset,
      "duration": duration,
      "pitch": pitch,
      "dynamicMark": dynamicMark
    };
    return n;
  };

  this.addNote = function (instrument, data) {
    var instrumentIsOn = this.toggles[instrument.group],
      actualPitch = this.lookupPitch(instrument, data),
      duration,
      longestNote;
    if (instrument.offset === this.globalTime) {
      duration = this.durations[this.durationIndex];
      if (instrumentIsOn) {
        instrument.notes.push(this.makeNote(instrument.offset, duration,
          actualPitch, this.dynamic[instrument.dynamicMark]));
      }
      instrument.offset += duration;
      this.globalTime = instrument.offset;
    } else if (instrument.offset < this.globalTime) {
      longestNote = this.piece.longestNote * this.durationLCM / 4;
      if (this.globalTime - instrument.offset > longestNote) {
        instrument.offset = this.globalTime - longestNote;
      }
      duration = this.globalTime - instrument.offset;
      if (instrumentIsOn) {
        instrument.notes.push(this.makeNote(instrument.offset, duration,
          actualPitch, this.dynamic[instrument.dynamicMark]));
      }
      instrument.offset += duration;
    }
  };

  this.emit = function (i) {
    var index = this.indexOf[i], instrumentId, indexToToggle,
      dynamicId, dynamicType, dynamicInstrument, dynamicMark;
    if (i === 'DecrementDuration') {
      this.durationIndex = Math.max(0, this.durationIndex - 1);
    } else if (i === 'IncrementDuration') {
      this.durationIndex = Math.min(this.durations.length - 1, this.durationIndex + 1);
    } else if (index >= this.indexOf.EmitFlute &&
               index <= this.indexOf.EmitDoubleBass) {
      instrumentId = index - this.indexOf.EmitFlute;
      this.addNote(this.instruments[instrumentId], this.getData());
    } else if (index >= this.indexOf.ToggleWinds &&
               index <= this.indexOf.ToggleStrings) {
      indexToToggle = index - this.indexOf.ToggleWinds;
      this.toggles[indexToToggle] = !this.toggles[indexToToggle];
      if (!this.toggles[0] && !this.toggles[1] && !this.toggles[2] && !this.toggles[3]) {
        this.toggles = [true, true, true, true];
      }
    } else if (index >= this.indexOf.FluteSoft && index <= this.indexOf.DoubleBassLouder) {
      dynamicId = index - this.indexOf.FluteSoft;
      dynamicType = dynamicId % 4;
      dynamicInstrument = (dynamicId - dynamicType) / 4;
      dynamicMark = this.instruments[dynamicInstrument].dynamicMark;
      if (dynamicType === 0) {
        dynamicMark = 2;
      } else if (dynamicType === 1) {
        dynamicMark = 4;
      } else if (dynamicType === 2) {
        if (this.piece.wrapDynamics) {
          dynamicMark = (this.dynamics + dynamicMark - 1) % this.dynamics;
        } else {
          dynamicMark = Math.max(dynamicMark - 1, 0);
        }
      } else {
        if (this.piece.wrapDynamics) {
          dynamicMark = (this.dynamics + dynamicMark + 1) % this.dynamics;
        } else {
          dynamicMark = Math.min(dynamicMark + 1, this.dynamics - 1);
        }
      }
      this.instruments[dynamicInstrument].dynamicMark = dynamicMark;
    }
  };

  this.performInstruction = function () {
    if (this.halt()) {
      return false;
    }
    var i = this.getInstruction(), braceCount;
    if (i === "MoveForward") {
      this.dataPointer += 1;
    } else if (i === "MoveBackward") {
      this.dataPointer -= 1;
    } else if (i === "IncrementData") {
      this.addToData(1);
    } else if (i === "DecrementData") {
      this.addToData(-1);
    } else if ((i === "WhileBegin" && !this.getData()) || (i === "WhileEnd" && this.getData())) {
      if (i !== "WhileEnd" || this.random.nextIntBetween(0, this.piece.loopContinueRate)) {
        //Perform jump operation to emulate while loops.
        braceCount = 1;
        do {
          this.instructionPointer += (i === "WhileBegin" ? 1 : -1);
          if (this.halt()) {
            return false;
          }
          if (this.getInstruction() === (i === "WhileBegin" ? "WhileEnd" : "WhileBegin")) {
            braceCount -= 1;
          } else if (this.getInstruction() === (i === "WhileEnd" ? "WhileEnd" : "WhileBegin")) {
            braceCount += 1;
          }
        } while (braceCount > 0);
      }
    } else {
      this.emit(i);
    }
    this.instructionPointer += 1;
    return true;
  };

  this.createMultiplyWithCarryPRNG = function (seed) {
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
  };

  this.createPiece = function () {
    // Initialize random number generator;
    this.random = this.createMultiplyWithCarryPRNG(this.piece.seed);

    // Initialize constants and distributions.
    this.createDurations();
    this.createInstruments();

    // Initialize state and maps.
    var i, shouldContinue = true;
    for (i = 0; i < this.piece.codeLength; i += 1) { this.instructions[i] = 0; }
    for (i = 0; i < this.piece.tapeLength; i += 1) { this.data[i] = 0; }

    this.planLoops();
    this.planInstructions();
    while (shouldContinue) {
      shouldContinue = this.performInstruction();
    }
  };

  this.pieceAsCSV = function () {
    var i, j, pieceString = 'Instrument,Channel,Start,Duration,Key,Dynamic\n',
      instrument, note;
    for (i = 0; i < this.instruments.length; i += 1) {
      instrument = this.instruments[i];
      for (j = 0; j < instrument.notes.length; j += 1) {
        note = instrument.notes[j];
        pieceString += instrument.name + ',' + instrument.index + ',' +
          note.time + ',' + note.duration + ',' + note.pitch + ',' +
          note.dynamicMark + '\n';
      }
    }
    return pieceString.trim();
  };

  this.noteTimeToSeconds = function (noteTime) {
    return noteTime * 4 * 60 / this.piece.tempo / this.durationLCM;
  };

  this.dynamicMarkToVelocity = function (dynamicMark) {
    return Math.round(dynamicMark / 7 * 87) + 20;
  };

  this.pieceAsMIDI = function () {
    var midiData = [], instrument, note, i, j;
    for (i = 0; i < this.instruments.length; i += 1) {
      instrument = this.instruments[i];
      for (j = 0; j < instrument.notes.length; j += 1) {
        note = instrument.notes[j];
        midiData.push({
          "time": this.noteTimeToSeconds(note.time),
          "duration": this.noteTimeToSeconds(note.duration),
          "channel": instrument.index,
          "pitch": note.pitch,
          "velocity": this.dynamicMarkToVelocity(note.dynamicMark)
        });
      }
    }
    return midiData;
  };

  this.parityChecksum = function (s) {
    var parity = 0, i;
    for (i = 0; i < s.length; i += 1) {
      parity = (parity + s.charCodeAt(i)) >>> 0;
    }
    return parity;
  };
};


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
  var pieceGenerator, pieceCSV;
  pieceGenerator = new PieceGenerator(pieceConfiguration);
  pieceGenerator.createPiece();
  pieceCSV = pieceGenerator.pieceAsCSV();
  console.log('CSV of piece:\n' + pieceCSV);
  console.log('Parity of CSV: ' + pieceGenerator.parityChecksum(pieceCSV));
  if (pieceGenerator.parityChecksum(pieceCSV) !== 6820566) {
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
  var pieceGenerator, pieceData, csv, sortKey;
  pieceGenerator = new PieceGenerator(pieceConfiguration);
  pieceGenerator.createPiece();
  pieceData = pieceGenerator.pieceAsMIDI();
  csv = pieceGenerator.pieceAsCSV();
  sortKey = "time";
  if (pieceGenerator.parityChecksum(csv) !== 6820566) {
    console.log('Warning: piece differs from original Steal This Piece');
  }
  console.log('Parity of CSV: ' + pieceGenerator.parityChecksum(csv));
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

////////////////////////////////////////////////////////////////////////////////















