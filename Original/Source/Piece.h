/*----------------------------------------------------------------------------*\
|                                                                              |
| Steal This Piece                                                             |
| The machine that creates a machine that creates a piece (of music).          |
| Written in 2012 by Andi Brae                                                 |
|                                                                              |
| To the extent possible under law, the author has dedicated all copyright     |
| and related and neighboring rights to this software to the public domain     |
| worldwide. This software is distributed without any warranty.                |
|                                                                              |
| You should have received a copy of the CC0 Public Domain Dedication along    |
| with this software. If not, see:                                             |
| <http://creativecommons.org/publicdomain/zero/1.0/>.                         |
|                                                                              |
\*----------------------------------------------------------------------------*/

//This file uniquely describes a piece created by Steal This Piece.

String InfoTitle = "Untitled";
String InfoComposer = "Anonymous";

const count GlobalSeed = 100;
const count GlobalLoopContinueRate = 5;
const count GlobalCodeLength = 3000;
const count GlobalTapeLength = 1024;
const count GlobalLoopStep = 100;
const count GlobalLoopSkipCreateRate = 3;
const count GlobalLoopInnerStartLow = 100;
const count GlobalLoopInnerStartHigh = 100;
const count GlobalLoopInnerEndLow = 100;
const count GlobalLoopInnerEndHigh = 100;
const count GlobalLoopOuterEndLow = 100;
const count GlobalLoopOuterEndHigh = 100;
const count GlobalLongestNote = 4;
const count GlobalProbabilityInversionSections = 10;
const count GlobalRange = 0;
const count GlobalTempo = 100;
const count GlobalRhythmSixteenth = 0;
const count GlobalRhythmTripletEighth = 1;
const count GlobalRhythmEighth = 1;
const count GlobalRhythmTripletQuarter = 1;
const count GlobalRhythmQuarter = 0;
const count GlobalUseHairpins = 1;
const count GlobalWrapDynamics = 1;
const count GlobalPitch0 = 1;
const count GlobalPitch1 = 1;
const count GlobalPitch2 = 1;
const count GlobalPitch3 = 1;
const count GlobalPitch4 = 1;
const count GlobalPitch5 = 1;
const count GlobalPitch6 = 1;
const count GlobalPitch7 = 1;
const count GlobalPitch8 = 1;
const count GlobalPitch9 = 1;
const count GlobalPitch10 = 1;
const count GlobalPitch11 = 1;

void SetPlanProbabilities(void)
{
  Probabilities.n(InstructionCount);
  Probabilities.Zero();
  Probabilities[MoveBackward] = 2000;
  Probabilities[MoveForward] = 2000;
  Probabilities[DecrementData] = 2000;
  Probabilities[IncrementData] = 2000;
  Probabilities[DecrementDuration] = 500;
  Probabilities[IncrementDuration] = 500;
  Probabilities[EmitFlute] = 500;
  Probabilities[EmitOboe] = 500;
  Probabilities[EmitClarinet] = 500;
  Probabilities[EmitBassoon] = 500;
  Probabilities[EmitHorn] = 500;
  Probabilities[EmitTrumpet] = 500;
  Probabilities[EmitTrombone] = 500;
  Probabilities[EmitBaritoneSax] = 500;
  Probabilities[EmitVibraphone] = 500;
  Probabilities[EmitCrotales] = 500;
  Probabilities[EmitViolin] = 500;
  Probabilities[EmitViola] = 500;
  Probabilities[EmitCello] = 300;
  Probabilities[EmitDoubleBass] = 500;
  Probabilities[ToggleWinds] = 1000;
  Probabilities[ToggleBrass] = 1000;
  Probabilities[TogglePercussion] = 1000;
  Probabilities[ToggleStrings] = 1000;
  Probabilities[FluteSoft] = 10;
  Probabilities[FluteLoud] = 10;
  Probabilities[FluteSofter] = 10;
  Probabilities[FluteLouder] = 10;
  Probabilities[OboeSoft] = 10;
  Probabilities[OboeLoud] = 10;
  Probabilities[OboeSofter] = 10;
  Probabilities[OboeLouder] = 10;
  Probabilities[ClarinetSoft] = 10;
  Probabilities[ClarinetLoud] = 10;
  Probabilities[ClarinetSofter] = 10;
  Probabilities[ClarinetLouder] = 10;
  Probabilities[BassoonSoft] = 10;
  Probabilities[BassoonLoud] = 10;
  Probabilities[BassoonSofter] = 10;
  Probabilities[BassoonLouder] = 10;
  Probabilities[HornSoft] = 10;
  Probabilities[HornLoud] = 10;
  Probabilities[HornSofter] = 10;
  Probabilities[HornLouder] = 10;
  Probabilities[TrumpetSoft] = 10;
  Probabilities[TrumpetLoud] = 10;
  Probabilities[TrumpetSofter] = 10;
  Probabilities[TrumpetLouder] = 10;
  Probabilities[TromboneSoft] = 10;
  Probabilities[TromboneLoud] = 10;
  Probabilities[TromboneSofter] = 10;
  Probabilities[TromboneLouder] = 10;
  Probabilities[BaritoneSaxSoft] = 10;
  Probabilities[BaritoneSaxLoud] = 10;
  Probabilities[BaritoneSaxSofter] = 10;
  Probabilities[BaritoneSaxLouder] = 10;
  Probabilities[VibraphoneSoft] = 10;
  Probabilities[VibraphoneLoud] = 10;
  Probabilities[VibraphoneSofter] = 10;
  Probabilities[VibraphoneLouder] = 10;
  Probabilities[CrotalesSoft] = 10;
  Probabilities[CrotalesLoud] = 10;
  Probabilities[CrotalesSofter] = 10;
  Probabilities[CrotalesLouder] = 10;
  Probabilities[ViolinSoft] = 10;
  Probabilities[ViolinLoud] = 10;
  Probabilities[ViolinSofter] = 10;
  Probabilities[ViolinLouder] = 10;
  Probabilities[ViolaSoft] = 10;
  Probabilities[ViolaLoud] = 10;
  Probabilities[ViolaSofter] = 10;
  Probabilities[ViolaLouder] = 10;
  Probabilities[CelloSoft] = 10;
  Probabilities[CelloLoud] = 10;
  Probabilities[CelloSofter] = 10;
  Probabilities[CelloLouder] = 10;
  Probabilities[DoubleBassSoft] = 10;
  Probabilities[DoubleBassLoud] = 10;
  Probabilities[DoubleBassSofter] = 10;
  Probabilities[DoubleBassLouder] = 10;
}
