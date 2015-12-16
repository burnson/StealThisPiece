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

function setDancePiece () {
  piece = {};
  piece.seed = 62;
  piece.loopContinueRate = 20;
  piece.codeLength = 3000;
  piece.tapeLength = 2;
  piece.loopStep = 200;
  piece.loopSkipCreateRate = 4;
  piece.loopInnerStartLow = 180;
  piece.loopInnerStartHigh = 100;
  piece.loopInnerEndLow = 100;
  piece.loopInnerEndHigh = 100;
  piece.loopOuterEndLow = 50;
  piece.loopOuterEndHigh = 50;
  piece.longestNote = 2;
  piece.probabilityInversionSections = 12;
  piece.computationRateInversion = 0.9975;
  piece.range = 12;
  piece.tempo = 500;
  piece.rhythmSixteenth = true;
  piece.rhythmTripletEighth = false;
  piece.rhythmEighth = true;
  piece.rhythmTripletQuarter = false;
  piece.rhythmQuarter = true;
  piece.useHairpins = true;
  piece.wrapDynamics = true;
  piece.pitchClass = [
    true, false, true, false,
    true, true, false, true,
    false, true, false, true
  ];
  
  probabilities = {};
  probabilities.MoveBackward = 200000;
  probabilities.MoveForward = 200000;
  probabilities.DecrementData = 400000;
  probabilities.IncrementData = 10000000;
  probabilities.DecrementDuration = 5700;
  probabilities.IncrementDuration = 5000;
  probabilities.EmitFlute = 0;
  probabilities.EmitOboe = 220;
  probabilities.EmitClarinet = 200;
  probabilities.EmitBassoon = 200;
  probabilities.EmitHorn = 200;
  probabilities.EmitTrumpet = 200;
  probabilities.EmitTrombone = 200;
  probabilities.EmitBaritoneSax = 200;
  probabilities.EmitVibraphone = 510;
  probabilities.EmitCrotales = 200;
  probabilities.EmitViolin = 500;
  probabilities.EmitViola = 0;
  probabilities.EmitCello = 410;
  probabilities.EmitDoubleBass = 0;
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


function setBaroquePiece () {
  piece = {};
  piece.seed = 62;
  piece.loopContinueRate = 20;
  piece.codeLength = 3000;
  piece.tapeLength = 2;
  piece.loopStep = 200;
  piece.loopSkipCreateRate = 4;
  piece.loopInnerStartLow = 180;
  piece.loopInnerStartHigh = 100;
  piece.loopInnerEndLow = 100;
  piece.loopInnerEndHigh = 100;
  piece.loopOuterEndLow = 50;
  piece.loopOuterEndHigh = 50;
  piece.longestNote = 2;
  piece.probabilityInversionSections = 12;
  piece.computationRateInversion = 0.9975;
  piece.range = 12;
  piece.tempo = 216;
  piece.rhythmSixteenth = true;
  piece.rhythmTripletEighth = false;
  piece.rhythmEighth = true;
  piece.rhythmTripletQuarter = false;
  piece.rhythmQuarter = true;
  piece.useHairpins = true;
  piece.wrapDynamics = true;
  piece.pitchClass = [
    true, false, true, false,
    true, true, false, true,
    false, true, false, true
  ];
  
  probabilities = {};
  probabilities.MoveBackward = 200000;
  probabilities.MoveForward = 200000;
  probabilities.DecrementData = 400000;
  probabilities.IncrementData = 10000000;
  probabilities.DecrementDuration = 5700;
  probabilities.IncrementDuration = 5000;
  probabilities.EmitFlute = 0;
  probabilities.EmitOboe = 220;
  probabilities.EmitClarinet = 200;
  probabilities.EmitBassoon = 200;
  probabilities.EmitHorn = 200;
  probabilities.EmitTrumpet = 200;
  probabilities.EmitTrombone = 200;
  probabilities.EmitBaritoneSax = 200;
  probabilities.EmitVibraphone = 0;
  probabilities.EmitCrotales = 0;
  probabilities.EmitViolin = 510;
  probabilities.EmitViola = 200;
  probabilities.EmitCello = 500;
  probabilities.EmitDoubleBass = 410;
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

function setThoughtfulPiece () {
  piece = {};
  piece.seed = 1;
  piece.loopContinueRate = 20;
  piece.codeLength = 3000;
  piece.tapeLength = 10;
  piece.loopStep = 200;
  piece.loopSkipCreateRate = 4;
  piece.loopInnerStartLow = 180;
  piece.loopInnerStartHigh = 100;
  piece.loopInnerEndLow = 100;
  piece.loopInnerEndHigh = 100;
  piece.loopOuterEndLow = 50;
  piece.loopOuterEndHigh = 50;
  piece.longestNote = 4;
  piece.probabilityInversionSections = 12;
  piece.computationRateInversion = 0.9975;
  piece.range = 12;
  piece.tempo = 100;
  piece.rhythmSixteenth = true;
  piece.rhythmTripletEighth = false;
  piece.rhythmEighth = true;
  piece.rhythmTripletQuarter = false;
  piece.rhythmQuarter = true;
  piece.useHairpins = true;
  piece.wrapDynamics = true;
  piece.pitchClass = [
    true, false, true, false,
    true, true, false, true,
    false, true, false, true
  ];
  
  probabilities = {};
  probabilities.MoveBackward = 200000;
  probabilities.MoveForward = 200000;
  probabilities.DecrementData = 400000;
  probabilities.IncrementData = 100000;
  probabilities.DecrementDuration = 5700;
  probabilities.IncrementDuration = 5000;
  probabilities.EmitFlute = 0;
  probabilities.EmitOboe = 0;
  probabilities.EmitClarinet = 0;
  probabilities.EmitBassoon = 0;
  probabilities.EmitHorn = 0;
  probabilities.EmitTrumpet = 0;
  probabilities.EmitTrombone = 0;
  probabilities.EmitBaritoneSax = 0;
  probabilities.EmitVibraphone = 200;
  probabilities.EmitCrotales = 0;
  probabilities.EmitViolin = 0;
  probabilities.EmitViola = 0;
  probabilities.EmitCello = 200;
  probabilities.EmitDoubleBass = 0;
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

function test () {
  createPiece();
  //console.log(JSON.stringify(pieceAsMIDI(), null, 2));
  var finalPiece = pieceAsCSV();
  console.log('CSV of piece:')
  console.log(finalPiece);
  console.log('Hash of CSV: ' + md5(finalPiece));

  if(md5(finalPiece) !== '0ca494dc0a5994afc36e3529d7059f6a') {
    console.log('WARNING: piece does not match reference');
  }
}

function testMath() {
  var generator = createMultiplyWithCarryPRNG(123);
  for(var i = 0; i < 1000; i++) {
    console.log(generator.nextFloat());
  }
}


////////////////////////////////////////////////////////////////////////////////


//A simple implementation of Marsaglia's Multiply-With-Carry PRNG.
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
      return (high + low) / 4503599627370496;
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


// MD5 implementation: http://www.myersdaily.org/joseph/javascript/md5-text.html
function md5(s) {
  function md5cycle(x, k) {
    var a = x[0], b = x[1], c = x[2], d = x[3];
    a = ff(a, b, c, d, k[0], 7, -680876936);
    d = ff(d, a, b, c, k[1], 12, -389564586);
    c = ff(c, d, a, b, k[2], 17, 606105819);
    b = ff(b, c, d, a, k[3], 22, -1044525330);
    a = ff(a, b, c, d, k[4], 7, -176418897);
    d = ff(d, a, b, c, k[5], 12,  1200080426);
    c = ff(c, d, a, b, k[6], 17, -1473231341);
    b = ff(b, c, d, a, k[7], 22, -45705983);
    a = ff(a, b, c, d, k[8], 7, 1770035416);
    d = ff(d, a, b, c, k[9], 12, -1958414417);
    c = ff(c, d, a, b, k[10], 17, -42063);
    b = ff(b, c, d, a, k[11], 22, -1990404162);
    a = ff(a, b, c, d, k[12], 7,  1804603682);
    d = ff(d, a, b, c, k[13], 12, -40341101);
    c = ff(c, d, a, b, k[14], 17, -1502002290);
    b = ff(b, c, d, a, k[15], 22, 1236535329);
    a = gg(a, b, c, d, k[1], 5, -165796510);
    d = gg(d, a, b, c, k[6], 9, -1069501632);
    c = gg(c, d, a, b, k[11], 14, 643717713);
    b = gg(b, c, d, a, k[0], 20, -373897302);
    a = gg(a, b, c, d, k[5], 5, -701558691);
    d = gg(d, a, b, c, k[10], 9, 38016083);
    c = gg(c, d, a, b, k[15], 14, -660478335);
    b = gg(b, c, d, a, k[4], 20, -405537848);
    a = gg(a, b, c, d, k[9], 5,  568446438);
    d = gg(d, a, b, c, k[14], 9, -1019803690);
    c = gg(c, d, a, b, k[3], 14, -187363961);
    b = gg(b, c, d, a, k[8], 20, 1163531501);
    a = gg(a, b, c, d, k[13], 5, -1444681467);
    d = gg(d, a, b, c, k[2], 9, -51403784);
    c = gg(c, d, a, b, k[7], 14, 1735328473);
    b = gg(b, c, d, a, k[12], 20, -1926607734);
    a = hh(a, b, c, d, k[5], 4, -378558);
    d = hh(d, a, b, c, k[8], 11, -2022574463);
    c = hh(c, d, a, b, k[11], 16, 1839030562);
    b = hh(b, c, d, a, k[14], 23, -35309556);
    a = hh(a, b, c, d, k[1], 4, -1530992060);
    d = hh(d, a, b, c, k[4], 11, 1272893353);
    c = hh(c, d, a, b, k[7], 16, -155497632);
    b = hh(b, c, d, a, k[10], 23, -1094730640);
    a = hh(a, b, c, d, k[13], 4, 681279174);
    d = hh(d, a, b, c, k[0], 11, -358537222);
    c = hh(c, d, a, b, k[3], 16, -722521979);
    b = hh(b, c, d, a, k[6], 23, 76029189);
    a = hh(a, b, c, d, k[9], 4, -640364487);
    d = hh(d, a, b, c, k[12], 11, -421815835);
    c = hh(c, d, a, b, k[15], 16, 530742520);
    b = hh(b, c, d, a, k[2], 23, -995338651);
    a = ii(a, b, c, d, k[0], 6, -198630844);
    d = ii(d, a, b, c, k[7], 10, 1126891415);
    c = ii(c, d, a, b, k[14], 15, -1416354905);
    b = ii(b, c, d, a, k[5], 21, -57434055);
    a = ii(a, b, c, d, k[12], 6, 1700485571);
    d = ii(d, a, b, c, k[3], 10, -1894986606);
    c = ii(c, d, a, b, k[10], 15, -1051523);
    b = ii(b, c, d, a, k[1], 21, -2054922799);
    a = ii(a, b, c, d, k[8], 6, 1873313359);
    d = ii(d, a, b, c, k[15], 10, -30611744);
    c = ii(c, d, a, b, k[6], 15, -1560198380);
    b = ii(b, c, d, a, k[13], 21, 1309151649);
    a = ii(a, b, c, d, k[4], 6, -145523070);
    d = ii(d, a, b, c, k[11], 10, -1120210379);
    c = ii(c, d, a, b, k[2], 15, 718787259);
    b = ii(b, c, d, a, k[9], 21, -343485551);
    x[0] = add32(a, x[0]);
    x[1] = add32(b, x[1]);
    x[2] = add32(c, x[2]);
    x[3] = add32(d, x[3]);
  }

  function cmn(q, a, b, x, s, t) {
    a = add32(add32(a, q), add32(x, t));
    return add32((a << s) | (a >>> (32 - s)), b);
  }

  function ff(a, b, c, d, x, s, t) {
    return cmn((b & c) | ((~b) & d), a, b, x, s, t);
  }

  function gg(a, b, c, d, x, s, t) {
    return cmn((b & d) | (c & (~d)), a, b, x, s, t);
  }

  function hh(a, b, c, d, x, s, t) {
    return cmn(b ^ c ^ d, a, b, x, s, t);
  }

  function ii(a, b, c, d, x, s, t) {
    return cmn(c ^ (b | (~d)), a, b, x, s, t);
  }

  function md51(s) {
    txt = '';
    var n = s.length,
    state = [1732584193, -271733879, -1732584194, 271733878], i;
    for (i = 64; i <= s.length; i += 64) {
      md5cycle(state, md5blk(s.substring(i - 64, i)));
    }
    s = s.substring(i - 64);
    var tail = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    for (i = 0; i < s.length; i++) {
      tail[i >> 2] |= s.charCodeAt(i) << ((i % 4) << 3);
    }
    tail[i >> 2] |= 0x80 << ((i % 4) << 3);
    if (i > 55) {
      md5cycle(state, tail);
      for (i = 0; i < 16; i++) {
        tail[i] = 0;
      }
    }
    tail[14] = n * 8;
    md5cycle(state, tail);
    return state;
  }

  function md5blk(s) {
    var md5blks = [], i;
    for (i = 0; i < 64; i += 4) {
      md5blks[i >> 2] = s.charCodeAt(i)
        + (s.charCodeAt(i + 1) << 8)
        + (s.charCodeAt(i + 2) << 16)
        + (s.charCodeAt(i + 3) << 24);
    }
    return md5blks;
  }

  var hex_chr = '0123456789abcdef'.split('');

  function rhex(n) {
    var s = '', j = 0;
    for(; j < 4; j++) {
      s += hex_chr[(n >> (j * 8 + 4)) & 0x0F] + hex_chr[(n >> (j * 8)) & 0x0F];
    }
    return s;
  }

  function hex(x) {
    for (var i = 0; i < x.length; i++)
    x[i] = rhex(x[i]);
    return x.join('');
  }

  function add32(a, b) {
    return (a + b) & 0xFFFFFFFF;
  }
  return hex(md51(s));
}

if (md5('hello') != '5d41402abc4b2a76b9719d911017c592') {
  console.log('Warning: MD5 self test failed.');
}


////////////////////////////////////////////////////////////////////////////////


if (isRunningUnderNodeJS()) {
  test();
}
