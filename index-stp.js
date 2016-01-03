/* Steal This Piece!

  "The machine that creates a machine that creates a piece of music"

  (A sort of probabilistic music program generator, that is to say,
  not a random music generator, but a sonifier of random programs.)

  dedicated to the public domain by William Andrew Burnson under the
  Creative Commons Zero license.

  The following is the entire source to Steal This Piece and is comprised of
  a PieceConfiguration, a PieceGenerator, and a PiecePlayer. In this new
  JavaScript port, a Web Audio API synth player is used to realize the music.

  The easiest way to try it out is to change some of the parameters below
  and see what happens.
*/
var StealThisPiece = function () {
  'use strict';
  this.PieceConfiguration = {
    // Seed for the random number generator so that pieces can be reproduced.
    seed: 133, // (integer, 0..1000000)

    // BPM of quarter note.
    tempo: 95.85, // (float, 10-1000)
    
    /* Reverb to use. Some good ones to try are:
      * ElvedenHallSmokingRoom
      * R1NuclearReactorHall
      * StMarysAbbeyReconstructionPhase1
      * TerrysFactoryWarehouse
      * YorkMinster
    See http://reverbjs.org for the full list.*/
    reverb: 'R1NuclearReactorHall',

    // Number of instructions to generate.
    instructionLength: 10000, // (integer, 1..1000000)

    // Length of the circular buffer containing the program's state.
    tapeLength: 1024, // (integer, 1..1000000)

    // Number of quarter notes in longest possible note.
    longestNote: 4, // (integer, 1..16)

    // Additional high notes to add to instrument's default range.
    additionalRange: 0, // (integer, 0..36)

    // Should sixteenth durations be used?
    rhythmSixteenth: false, // (true/false)

    // Should triplet-eight durations be used?
    rhythmTripletEighth: true, // (true/false)

    // Should eighth durations be used?
    rhythmEighth: true, // (true/false)

    // Should triple-quarter durations be used?
    rhythmTripletQuarter: true, // (true/false)

    // Should quarter durations be used?
    rhythmQuarter: false, // (true/false)

    /* If true, then making an instrument that is already at its loudest
    any louder will instead wrap around to the softest value and vice-versa.
    Otherwise, dynamic changes will be clipped to softest and loudest.*/
    wrapDynamics: true, // (true/false)

    // Whether or not to use a given pitch starting with C, C sharp, D, etc.
    pitchClass: [
      true, true, true, true,
      true, true, true, true,
      true, true, true, true
    ], // [(true/false), ...]

    // Relative probabilities of instructions (range: float, 0-1000000)
    probabilityOf: {
      // Probability of moving the data pointer forward or backward.
      moveBackward: 20000,
      moveForward: 20000,

      // Probability of incrementing or decrementing the data pointed to.
      decrementData: 20000,
      incrementData: 20000,

      // Probability of moving to next smallest or largest rhythmic duration.
      decrementDuration: 500,
      incrementDuration: 500,

      // Probability of emitting notes from various instruments.
      emitFlute: 40,
      emitOboe: 40,
      emitClarinet: 20,
      emitBassoon: 20,
      emitHorn: 10,
      emitTrumpet: 20,
      emitTrombone: 10,
      emitBaritoneSax: 50,
      emitVibraphone: 50,
      emitCrotales: 10,
      emitViolin: 50,
      emitViola: 50,
      emitCello: 30,
      emitDoubleBass: 10,

      // Probabilities of toggle on and off an entire instrument section.
      toggleWinds: 100,
      toggleBrass: 100,
      togglePercussion: 100,
      toggleStrings: 100,

      /* Probabilities of changing the instruments' dynamics. Soft and loud are
      piano and forte, respectively. Softer means go down by one dynamic mark,
      and louder means go up by one dynamic mark.*/
      fluteSoft: 1,
      fluteLoud: 1,
      fluteSofter: 1,
      fluteLouder: 1,
      oboeSoft: 1,
      oboeLoud: 1,
      oboeSofter: 1,
      oboeLouder: 1,
      clarinetSoft: 1,
      clarinetLoud: 1,
      clarinetSofter: 1,
      clarinetLouder: 1,
      bassoonSoft: 1,
      bassoonLoud: 1,
      bassoonSofter: 1,
      bassoonLouder: 1,
      hornSoft: 1,
      hornLoud: 1,
      hornSofter: 1,
      hornLouder: 1,
      trumpetSoft: 1,
      trumpetLoud: 1,
      trumpetSofter: 1,
      trumpetLouder: 1,
      tromboneSoft: 1,
      tromboneLoud: 1,
      tromboneSofter: 1,
      tromboneLouder: 1,
      baritoneSaxSoft: 1,
      baritoneSaxLoud: 1,
      baritoneSaxSofter: 1,
      baritoneSaxLouder: 1,
      vibraphoneSoft: 1,
      vibraphoneLoud: 1,
      vibraphoneSofter: 1,
      vibraphoneLouder: 1,
      crotalesSoft: 1,
      crotalesLoud: 1,
      crotalesSofter: 1,
      crotalesLouder: 1,
      violinSoft: 1,
      violinLoud: 1,
      violinSofter: 1,
      violinLouder: 1,
      violaSoft: 1,
      violaLoud: 1,
      violaSofter: 1,
      violaLouder: 1,
      celloSoft: 1,
      celloLoud: 1,
      celloSofter: 1,
      celloLouder: 1,
      doubleBassSoft: 1,
      doubleBassLoud: 1,
      doubleBassSofter: 1,
      doubleBassLouder: 1
    },

    /* All control flow is planned using nested while-loops of the form:
    
    while(current data byte pointed to is non-zero) {
      ...region A...
      ...region B...
      while(current data byte pointed to is non-zero) {
        ...region B cont'd...
        ...region C...
        ...region D...
      }
      ...region D cont'd...
      ...region E...
      ...region F...
    }
    ...region F cont'd...
    ...region G...
    <...next while loop structure..>

    The regions are then filled with instructions. The sizes of the regions are
    determined by the following constants.*/

    // Size of region A. The instructions here precede the inner while loop.
    regionASize: 100, // (integer, 1..10000)

    // Size of region B. The inner while loop begins randomly within region B.
    regionBSize: 100, // (integer, 1..10000)

    // Size of region C. The instructions here are in the inner while loop.
    regionCSize: 100, // (integer, 1..10000)

    // Size of region D. The inner while loop ends randomly within region D.
    regionDSize: 100, // (integer, 1..10000)

    // Size of region E. The instructions here follow the inner while loop.
    regionESize: 50, // (integer, 1..10000)

    // Size of region F. The outer while loop ends randomly within region F.
    regionFSize: 50, // (integer, 1..10000)

    // Size of region G. The instructions here follow the outer while loop.
    regionGSize: 100, // (integer, 1..10000)

    /* One out of this many times, an area being considered for a nested
    while-loop will actually have a loop created there. This is used to decrease
    the density of looping structures in the instruction tape. A higher number
    causes fewer loops to be created.*/
    loopCreationRate: 3, // (integer, 1..10000)

    /* One out of this many times, the instruction pointer will
    probabilistically fall through the end of a while loop without testing the
    condition. This is used to prevent the instruction tape from getting stuck
    in an infinite loop. A higher number causes loops to live for longer.*/
    loopFallThroughRate: 5, // (integer, 1..10000)

    /* During a probability inversion section, the likelihood of
    move backward/forward and decrement/increment data instructions is
    suppressed (the computation-related instructions). This allows music-related
    instructions to appear more frequently. You can disable this feature by
    setting the computation rate inversion to zero.*/

    // Percentage of computation-related probabilities to suppress when enabled.
    computationRateInversion: 0.9975, // (float, 0-1)

    // Number of probability-inversion sections to use in piece.
    probabilityInversionSections: 10 // (integer, 1..10000)
  };

// To learn how the piece is generated, check out createPiece() below...

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  this.PieceGenerator = function PieceGenerator(configuration) {
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
      "nullOp", "whileBegin", "whileEnd", "moveBackward", "moveForward",
      "decrementData", "incrementData", "decrementDuration",
      "incrementDuration", "emitFlute", "emitOboe", "emitClarinet",
      "emitBassoon", "emitHorn", "emitTrumpet", "emitTrombone",
      "emitBaritoneSax", "emitVibraphone", "emitCrotales", "emitViolin",
      "emitViola", "emitCello", "emitDoubleBass", "toggleWinds", "toggleBrass",
      "togglePercussion", "toggleStrings", "fluteSoft", "fluteLoud",
      "fluteSofter", "fluteLouder", "oboeSoft", "oboeLoud", "oboeSofter",
      "oboeLouder", "clarinetSoft", "clarinetLoud", "clarinetSofter",
      "clarinetLouder", "bassoonSoft", "bassoonLoud", "bassoonSofter",
      "bassoonLouder", "hornSoft", "hornLoud", "hornSofter", "hornLouder",
      "trumpetSoft", "trumpetLoud", "trumpetSofter", "trumpetLouder",
      "tromboneSoft", "tromboneLoud", "tromboneSofter", "tromboneLouder",
      "baritoneSaxSoft", "baritoneSaxLoud", "baritoneSaxSofter",
      "baritoneSaxLouder", "vibraphoneSoft", "vibraphoneLoud",
      "vibraphoneSofter", "vibraphoneLouder", "crotalesSoft", "crotalesLoud",
      "crotalesSofter", "crotalesLouder", "violinSoft", "violinLoud",
      "violinSofter", "violinLouder", "violaSoft", "violaLoud", "violaSofter",
      "violaLouder", "celloSoft", "celloLoud", "celloSofter", "celloLouder",
      "doubleBassSoft", "doubleBassLoud", "doubleBassSofter", "doubleBassLouder"
    ];

    this.indexOf = (function (that) {
      var x = {}, i;
      for (i = 0; i < that.instructionSet.length; i += 1) {
        x[that.instructionSet[i]] = i;
      }
      return x;
    }(this));

    this.distributeProbabilities = function (inversionProbability) {
      var p, sum = 0, instruction;
      p = this.piece.computationRateInversion * inversionProbability;
      this.distribution = {};
      for (instruction in this.probabilities) {
        if (this.probabilities.hasOwnProperty(instruction)) {
          this.distribution[instruction] = this.probabilities[instruction];
        }
      }

      // Apply probability inversion if being used.
      this.distribution.moveBackward -= p * this.distribution.moveBackward;
      this.distribution.moveForward -= p * this.distribution.moveForward;
      this.distribution.decrementData -= p * this.distribution.decrementData;
      this.distribution.incrementData -= p * this.distribution.incrementData;

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
      var i = [], r = this.piece.additionalRange;
      i.push(this.makeInstrument(0,  0, "Flute",       67, 98 + r)); //G4-D6
      i.push(this.makeInstrument(1,  0, "Oboe",        60, 84 + r)); //C4-C6
      i.push(this.makeInstrument(2,  0, "Clarinet",    50, 79 + r)); //D3-G5
      i.push(this.makeInstrument(3,  0, "Bassoon",     36, 67 + r)); //C2-G4
      i.push(this.makeInstrument(4,  1, "Horn",        48, 72 + r)); //C3-C5
      i.push(this.makeInstrument(5,  1, "Trumpet",     55, 79 + r)); //G3-G5
      i.push(this.makeInstrument(6,  1, "Trombone",    43, 67 + r)); //G2-G4
      i.push(this.makeInstrument(7,  1, "BaritoneSax", 43, 60 + r)); //G2-C4
      i.push(this.makeInstrument(8,  2, "Vibraphone",  53, 89));     //F3-F6
      i.push(this.makeInstrument(9,  2, "Crotales",    60, 84));     //C2-C4
      i.push(this.makeInstrument(10, 3, "Violin",      55, 84 + r)); //G3-C6
      i.push(this.makeInstrument(11, 3, "Viola",       48, 79 + r)); //C3-G5
      i.push(this.makeInstrument(12, 3, "Cello",       36, 67 + r)); //C2-G5
      i.push(this.makeInstrument(13, 3, "DoubleBass",  28, 48 + r)); //E2-C4
      this.instruments = i;

      /*Backwards compatibility to express original behavior where Violin was
      considered part of the percussion group for toggling. Could be removed.*/
      this.instruments[10].group = 2;
    };

    this.planLoops = function () {
      var a = this.piece.regionASize,
        b = a + this.piece.regionBSize,
        c = b + this.piece.regionCSize,
        d = c + this.piece.regionDSize,
        e = d + this.piece.regionESize,
        f = e + this.piece.regionFSize,
        g = f + this.piece.regionGSize,
        i,
        whileBegin = this.indexOf.whileBegin,
        whileEnd = this.indexOf.whileEnd;
      for (i = 0; i < this.instructions.length - g; i += 1) {
        if (this.random.nextIntBetween(0, this.piece.loopCreationRate) === 0) {
          this.instructions[i] = whileBegin;
          this.instructions[i + this.random.nextIntBetween(e, f)] = whileEnd;
          this.instructions[i + this.random.nextIntBetween(a, b)] = whileBegin;
          this.instructions[i + this.random.nextIntBetween(c, d)] = whileEnd;
          i += g;
        }
      }
    };

    this.getProbableInstruction = function (normalizedNumber) {
      var k, bestKey = 'nullOp', lowestValue = 2; //i.e. a number > 1
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
          this.instructions[i] = this.getProbableInstruction(
            this.random.nextFloat()
          );
        }
      }
    };

    this.halt = function () {
      return (this.instructionPointer >= this.instructions.length ||
        this.instructionPointer < 0);
    };

    this.getInstruction = function () {
      return this.instructionSet[this.instructions[this.instructionPointer]];
    };

    this.getCyclicDataPointer = function () {
      return ((this.dataPointer + this.data.length *
        Math.abs(this.dataPointer)) % this.data.length);
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
      if (i === 'decrementDuration') {
        this.durationIndex = Math.max(0, this.durationIndex - 1);
      } else if (i === 'incrementDuration') {
        this.durationIndex = Math.min(this.durations.length - 1,
          this.durationIndex + 1
          );
      } else if (index >= this.indexOf.emitFlute &&
                 index <= this.indexOf.emitDoubleBass) {
        instrumentId = index - this.indexOf.emitFlute;
        this.addNote(this.instruments[instrumentId], this.getData());
      } else if (index >= this.indexOf.toggleWinds &&
                 index <= this.indexOf.toggleStrings) {
        indexToToggle = index - this.indexOf.toggleWinds;
        this.toggles[indexToToggle] = !this.toggles[indexToToggle];
        if (!this.toggles[0] && !this.toggles[1] && !this.toggles[2] &&
            !this.toggles[3]) {
          this.toggles = [true, true, true, true];
        }
      } else if (index >= this.indexOf.fluteSoft && index <=
          this.indexOf.doubleBassLouder) {
        dynamicId = index - this.indexOf.fluteSoft;
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
      if (i === "moveForward") {
        this.dataPointer += 1;
      } else if (i === "moveBackward") {
        this.dataPointer -= 1;
      } else if (i === "incrementData") {
        this.addToData(1);
      } else if (i === "decrementData") {
        this.addToData(-1);
      } else if ((i === "whileBegin" && !this.getData()) || (i === "whileEnd" &&
          this.getData())) {
        if (i !== "whileEnd" || this.random.nextIntBetween(0,
            this.piece.loopFallThroughRate)) {
          //Perform jump operation to emulate while loops.
          braceCount = 1;
          do {
            this.instructionPointer += (i === "whileBegin" ? 1 : -1);
            if (this.halt()) {
              return false;
            }
            if (this.getInstruction() ===
                (i === "whileBegin" ? "whileEnd" : "whileBegin")) {
              braceCount -= 1;
            } else if (this.getInstruction() ===
                (i === "whileEnd" ? "whileEnd" : "whileBegin")) {
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
          var magicNumbers = [5115, 1776, 1492, 2111111111],
            low = 0,
            high = 0,
            i;
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
      for (i = 0; i < this.piece.instructionLength; i += 1) {
        this.instructions[i] = 0;
      }
      for (i = 0; i < this.piece.tapeLength; i += 1) {
        this.data[i] = 0;
      }

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
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  this.PiecePlayer = function PiecePlayer() {
    /*global window, reverbjs*/
    this.context = null;
    this.masterGain = null;
    this.masterVolume = 0.5;
    this.concertVolume = 0.5;
    this.midiQueue = null;
    this.playerStartTime = 0;
    this.noteOutput = null;
    this.reverb = null;
    this.reverbGain = null;
    this.timeInAdvanceToSchedule = 1.0;

    this.dBToGain = function (dB) {
      if (dB <= -100) {
        return 0;
      }
      return Math.pow(10, dB / 10);
    };

    this.getCurrentTime = function () {
      return this.context.currentTime;
    };

    this.midiNoteNumberToFrequency = function (midiNoteNumber) {
      return 55 * Math.pow(2, (midiNoteNumber - 33) / 12);
    };

    this.scheduleOscillator = function (type, note, startTime, duration, gain,
        shape) {
      if (startTime < this.getCurrentTime()) {
        console.log('Warning: dropped note that started in past');
        return;
      }
      var gainShaper = this.context.createGain(), i, g, t, oscillator;
      gainShaper.gain.value = 0;
      gainShaper.gain.setValueAtTime(0, startTime);
      for (i in shape) {
        if (shape.hasOwnProperty(i)) {
          g = this.dBToGain(shape[i].dB) * gain;
          t = startTime + shape[i].time * duration;
          gainShaper.gain.linearRampToValueAtTime(g, t);
        }
      }
      gainShaper.connect(this.noteOutput);

      oscillator = this.context.createOscillator();
      oscillator.type = type;
      oscillator.frequency.value = this.midiNoteNumberToFrequency(note);
      oscillator.start(startTime);
      oscillator.stop(startTime + duration);
      oscillator.connect(gainShaper);
    };

    this.scheduleFluteNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-28);
      this.scheduleOscillator('sine', note, start, duration, gain,
        [{time: 0.3, dB: -32}, {time: 0.9, dB: -32}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 12, start, duration, gain,
        [{time: 0.1, dB: -38}, {time: 0.9, dB: -38}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.3, dB: -42}, {time: 0.9, dB: -42}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 36, start, duration, gain,
        [{time: 0.3, dB: -48}, {time: 0.9, dB: -48}, {time: 1.0, dB: -100}]);
    };

    this.scheduleOboeNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-47);
      this.scheduleOscillator('sine', note, start, duration, gain,
        [{time: 0.1, dB: -50}, {time: 0.9, dB: -50}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('triangle', note + 12, start, duration, gain,
        [{time: 0.1, dB: -55}, {time: 0.9, dB: -55}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.3, dB: -60}, {time: 0.9, dB: -60}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 36, start, duration, gain,
        [{time: 0.3, dB: -65}, {time: 0.9, dB: -65}, {time: 1.0, dB: -100}]);
    };

    this.scheduleClarinetNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-50);
      this.scheduleOscillator('sine', note, start, duration, gain,
        [{time: 0.1, dB: -79}, {time: 0.9, dB: -79}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 12, start, duration, gain,
        [{time: 0.1, dB: -65}, {time: 0.9, dB: -65}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.3, dB: -50}, {time: 0.9, dB: -50}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 36, start, duration, gain,
        [{time: 0.3, dB: -55}, {time: 0.9, dB: -55}, {time: 1.0, dB: -100}]);
    };

    this.scheduleBassoonNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-55);
      this.scheduleOscillator('sine', note, start, duration, gain,
        [{time: 0.05, dB: -65}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 12, start, duration, gain,
        [{time: 0.05, dB: -68}, {time: 0.95, dB: -68}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.05, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 48, start, duration, gain,
        [{time: 0.05, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
    };

    this.scheduleHornNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-55);
      this.scheduleOscillator('triangle', note, start, duration, gain,
        [{time: 0.05, dB: -65}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('triangle', note + 12, start, duration, gain,
        [{time: 0.05, dB: -68}, {time: 0.95, dB: -68}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 48, start, duration, gain,
        [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
    };

    this.scheduleTromboneNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-58);
      this.scheduleOscillator('triangle', note, start, duration, gain,
        [{time: 0.05, dB: -65}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sawtooth', note + 12, start, duration, gain,
        [{time: 0.05, dB: -55}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('square', note + 48, start, duration, gain,
        [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
    };

    this.scheduleTrumpetNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-50);
      this.scheduleOscillator('triangle', note, start, duration, gain,
        [{time: 0.05, dB: -65}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sawtooth', note + 12, start, duration, gain,
        [{time: 0.05, dB: -55}, {time: 0.95, dB: -60}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('square', note + 48, start, duration, gain,
        [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
    };

    this.scheduleBaritoneSaxNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-50);
      this.scheduleOscillator('square', note, start, duration, gain,
        [{time: 0.05, dB: -62}, {time: 0.15, dB: -65}, {time: 0.95, dB: -65},
          {time: 1.0, dB: -100}]);
      this.scheduleOscillator('triangle', note + 12, start, duration, gain,
        [{time: 0.05, dB: -52}, {time: 0.15, dB: -55}, {time: 0.95, dB: -55},
          {time: 1.0, dB: -100}]);
      this.scheduleOscillator('triangle', note + 24, start, duration, gain,
        [{time: 0.05, dB: -58}, {time: 0.15, dB: -58}, {time: 0.95, dB: -58},
          {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 48, start, duration, gain,
        [{time: 0.05, dB: -75}, {time: 0.15, dB: -75}, {time: 0.95, dB: -75},
          {time: 1.0, dB: -100}]);
    };

    this.scheduleVibraphoneNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-6);
      this.scheduleOscillator('triangle', note, start, duration, gain,
        [{time: 0.05, dB: -3}, {time: 0.15, dB: -12}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 12, start, duration, gain,
        [{time: 0.05, dB: -6}, {time: 0.15, dB: -6}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.05, dB: -12}, {time: 0.15, dB: -42}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 48, start, duration, gain,
        [{time: 0.05, dB: -24}, {time: 0.15, dB: -54}, {time: 1.0, dB: -100}]);
    };

    this.scheduleCrotalesNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-12);
      this.scheduleOscillator('sine', note, start, duration, gain,
        [{time: 0.01, dB: -3}, {time: 0.05, dB: -30}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 12, start, duration, gain,
        [{time: 0.05, dB: -6}, {time: 0.15, dB: -12}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('triangle', note + 24, start, duration, gain,
        [{time: 0.01, dB: -12}, {time: 0.05, dB: -30}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('triangle', note + 48, start, duration, gain,
        [{time: 0.01, dB: -24}, {time: 0.05, dB: -30}, {time: 1.0, dB: -100}]);
    };

    this.scheduleViolinNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-55);
      this.scheduleOscillator('triangle', note, start, duration, gain,
        [{time: 0.05, dB: -85}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sawtooth', note + 12, start, duration, gain,
        [{time: 0.05, dB: -85}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('square', note + 48, start, duration, gain,
        [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
    };

    this.scheduleViolaNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-50);
      this.scheduleOscillator('triangle', note, start, duration, gain,
        [{time: 0.05, dB: -85}, {time: 0.95, dB: -65}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sawtooth', note + 12, start, duration, gain,
        [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sine', note + 24, start, duration, gain,
        [{time: 0.2, dB: -58}, {time: 0.95, dB: -58}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('square', note + 48, start, duration, gain,
        [{time: 0.2, dB: -75}, {time: 0.95, dB: -75}, {time: 1.0, dB: -100}]);
    };

    this.scheduleCelloNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-50);
      this.scheduleOscillator('triangle', note - 12, start, duration, gain,
        [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sawtooth', note, start, duration, gain,
        [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
    };

    this.scheduleDoubleBassNote = function (note, start, duration, gain) {
      gain /= this.dBToGain(-50);
      this.scheduleOscillator('sawtooth', note - 12, start, duration, gain,
        [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
      this.scheduleOscillator('sawtooth', note, start, duration, gain,
        [{time: 0.05, dB: -75}, {time: 0.95, dB: -55}, {time: 1.0, dB: -100}]);
    };

    this.configureAudioGraph = function (callback) {
      var that = this;
      this.masterGain = this.context.createGain();
      this.masterGain.gain.value = this.masterVolume;
      this.masterGain.connect(this.context.destination);

      window.onbeforeunload = function () {
        that.shutdownGracefully.apply(that)
      };

      this.reverbGain = this.context.createGain();
      this.reverbGain.gain.value = 1.0;
      // this.reverbGain.connect(this.masterGain);

      this.noteOutput = this.reverbGain;
      this.reverb = this.context.createReverbFromUrl(
        'http://reverbjs.org/Library/' +
        window.PieceConfiguration.reverb + '.wav',
        function () {
          that.concert = that.context.createSourceFromUrl(
            'http://stealthispiece.com/Resources/StealThisPiece.m4a',
            function () {
              callback(that);
            }
          )
          that.concertGain = that.context.createGain();
          that.concertGain.gain.value = 0.0;
          that.concert.connect(that.concertGain);
          that.concertGain.connect(that.context.destination);
        }
      );
      this.reverbGain.connect(this.reverb);
      this.reverb.connect(this.masterGain);
    };

    this.frequencyToMIDINoteNumber = function (frequency) {
      var n = 12 * Math.log(frequency * Math.pow(2, 11 / 4) / 55) / Math.log(2),
        rounded = Math.round(n * 128) / 128;
      return rounded;
    };

    this.getPieceAsMIDILikeData = function () {
      var pieceGenerator, pieceData, csv, sortKey;
      pieceGenerator = new window.PieceGenerator(window.PieceConfiguration);
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
    };

    this.scheduleInstrumentalNote = function (instrument, midiNoteNumber,
        startTime, duration, velocity) {
      if (velocity === undefined) {
        velocity = 0.5;
      } else {
        velocity = Math.min(Math.max(velocity / 127, 0.01), 1);
      }
      var gain = 0.1 * velocity, instruments = [
        this.scheduleFluteNote,
        this.scheduleOboeNote,
        this.scheduleClarinetNote,
        this.scheduleBassoonNote,
        this.scheduleHornNote,
        this.scheduleTrumpetNote,
        this.scheduleTromboneNote,
        this.scheduleBaritoneSaxNote,
        this.scheduleVibraphoneNote,
        this.scheduleCrotalesNote,
        this.scheduleViolinNote,
        this.scheduleViolaNote,
        this.scheduleCelloNote,
        this.scheduleDoubleBassNote
      ];
      instruments[instrument].apply(this,
        [midiNoteNumber, startTime, duration, gain]);
    };

    this.processNextFrame = function () {
      if (this.midiQueue === null || this.midiQueue.length === 0) {
        return;
      }
      var playerCurrentTime = this.getCurrentTime() - this.playerStartTime,
        playerScheduleTime = playerCurrentTime + this.timeInAdvanceToSchedule,
        m,
        that = this;
      while (this.midiQueue[0] !== undefined &&
          this.midiQueue[0].time < playerScheduleTime) {
        m = this.midiQueue.shift();
        this.scheduleInstrumentalNote(m.channel, m.pitch,
          m.time + this.playerStartTime, m.duration, m.velocity);
      }
      window.setTimeout(function () {
        that.processNextFrame();
      }, 10);
    };

    this.schedulePiece = function (that) {
      var startDelay = 1.0;
      that.scheduleInstrumentalNote(0, 60, 0, 0, 0); //just to get things going
      that.midiQueue = that.getPieceAsMIDILikeData();
      that.playerStartTime = that.getCurrentTime() + startDelay;
      that.processNextFrame();
      window.setTimeout(function() {
        that.concert.start();
      }, startDelay * 1000)
    };

    this.initialize = function () {
      if (!this.context) {
        if (window.hasOwnProperty("currentAudioContext")) {
          this.context = window.currentAudioContext;
        } else if (window.AudioContext) {
          this.context = new window.AudioContext();
        } else {
          this.context = new window.webkitAudioContext();
        }
        window.currentAudioContext = this.context;
        reverbjs.extend(this.context);
      }
      this.noteOutput = this.context.destination;
      this.configureAudioGraph(this.schedulePiece);
    };

    this.shutdownGracefully = function () {
      if (this.masterGain === null) {
        return;
      }
      var start = this.getCurrentTime(), length = 0.05, progress = 0;
      while (progress <= 1) {
        this.masterGain.gain.value = (1 - progress) * this.masterVolume;
        progress = (this.getCurrentTime() - start) / length;
      }
    };

    this.stop = function () {
      if (this.masterGain !== null) {
        this.shutdownGracefully();
      }
      if (this.masterGain) {
        this.masterGain.disconnect();
        this.masterGain = null;
      }
      if (this.concertGain) {
        this.concertGain.disconnect();
        this.concertGain = null;
      }
      this.midiQueue = null;
      this.playerStartTime = 0;
      if (this.noteOutput) {
        this.noteOutput.disconnect();
        this.noteOutput = null;
      }
      if (this.reverb) {
        this.reverb.disconnect();
        this.reverb = null;
      }
      if (this.reverbGain) {
        this.reverbGain.disconnect();
        this.reverbGain = null;
      }
    };

    this.start = function () {
      this.stop();
      this.initialize();
    };

    this.muteConcert = function(muted) {
      var g = muted ? 0 : this.concertVolume;
      var t = this.context.currentTime;
      this.concertGain.gain.setValueAtTime(this.concertVolume - g, t + 0.1);
      this.concertGain.gain.linearRampToValueAtTime(g, t + 1.0);
    };

    this.muteGenerated = function(muted) {
      var g = muted ? 0 : this.masterVolume;
      var t = this.context.currentTime;
      this.masterGain.gain.setValueAtTime(this.masterVolume - g, t + 0.1);
      this.masterGain.gain.linearRampToValueAtTime(g, t + 1.0);
    }
  };

  var generateInConsoleIfRunningUnderNodeJS = function () {
    if (typeof window === 'object') { return; }
    var pieceGenerator, pieceCSV;
    pieceGenerator = new this.PieceGenerator(this.PieceConfiguration);
    pieceGenerator.createPiece();
    pieceCSV = pieceGenerator.pieceAsCSV();
    console.log('CSV of piece:\n' + pieceCSV);
    console.log('Parity of CSV: ' + pieceGenerator.parityChecksum(pieceCSV));
    if (pieceGenerator.parityChecksum(pieceCSV) !== 6820566) {
      console.log('WARNING: piece does not match reference');
    }
  };
  generateInConsoleIfRunningUnderNodeJS.apply(this);
};
StealThisPiece.apply(typeof window === 'object' ? window : StealThisPiece);
