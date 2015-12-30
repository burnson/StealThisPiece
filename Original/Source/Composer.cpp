/*----------------------------------------------------------------------------*\
|                                                                              |
| Steal This Piece                                                             |
| The machine that creates a machine that creates a piece (of music).          |
| Written in 2012 by William Andrew Burnson andrew@williamburnson.com          |
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

//----------------//
//Library Includes//
//----------------//

#define PRIM_COMPILE_INLINE
#define PRIM_WITH_MD5
#include "prim.h"
using namespace prim;

//------------//
//Instructions//
//------------//

enum Instructions
{
  NullOp,
  WhileBegin, WhileEnd,
  
  MoveBackward, MoveForward, DecrementData, IncrementData,
  DecrementDuration, IncrementDuration,
  
  Woodwinds,
  EmitFlute = Woodwinds, EmitOboe, EmitClarinet, EmitBassoon,
  
  Brass,
  EmitHorn = Brass, EmitTrumpet, EmitTrombone, EmitBaritoneSax,
  
  Percussion,
  EmitVibraphone = Percussion, EmitCrotales,
  
  Strings,
  EmitViolin = Strings, EmitViola, EmitCello, EmitDoubleBass,
  
  FirstInstrument = EmitFlute,
  LastInstrument = EmitDoubleBass,
  
  ToggleWinds, ToggleBrass, TogglePercussion, ToggleStrings,
  
  FluteSoft, FluteLoud, FluteSofter, FluteLouder,
  OboeSoft, OboeLoud, OboeSofter, OboeLouder,
  ClarinetSoft, ClarinetLoud, ClarinetSofter, ClarinetLouder,
  BassoonSoft, BassoonLoud, BassoonSofter, BassoonLouder,
  
  HornSoft, HornLoud, HornSofter, HornLouder,
  TrumpetSoft, TrumpetLoud, TrumpetSofter, TrumpetLouder,
  TromboneSoft, TromboneLoud, TromboneSofter, TromboneLouder,
  BaritoneSaxSoft, BaritoneSaxLoud, BaritoneSaxSofter, BaritoneSaxLouder,
  
  VibraphoneSoft, VibraphoneLoud, VibraphoneSofter, VibraphoneLouder,
  CrotalesSoft, CrotalesLoud, CrotalesSofter, CrotalesLouder,
  
  ViolinSoft, ViolinLoud, ViolinSofter, ViolinLouder,
  ViolaSoft, ViolaLoud, ViolaSofter, ViolaLouder,
  CelloSoft, CelloLoud, CelloSofter, CelloLouder,
  DoubleBassSoft, DoubleBassLoud, DoubleBassSofter, DoubleBassLouder,
  
  FirstDynamic = FluteSoft,
  LastDynamic = DoubleBassLouder,
  
  InstructionCount
};

//----------//
//Parameters//
//----------//

Array<number> Probabilities;

String EnsemblePaper = "11x17";
String PartPaper     = "letter";

#include "Piece.h"

//Disable computation rate inversion by setting:
//const count GlobalProbabilityInversionSections = 1;
const number ComputationRateInversion = 0.9975;

void DistributeProbabilities(number i)
{
  //Apply probability inversion if being used.
  Probabilities[MoveBackward] -=
    ComputationRateInversion * Probabilities[MoveBackward] * i;
  Probabilities[MoveForward] -=
    ComputationRateInversion * Probabilities[MoveForward] * i;
  Probabilities[DecrementData] -=
    ComputationRateInversion * Probabilities[DecrementData] * i;
  Probabilities[IncrementData] -=
    ComputationRateInversion * Probabilities[IncrementData] * i;
  
  //Turn the probabilities into a distribution.
  number Sum = 0;
  for(count i = 0; i < Probabilities.n(); i++)
  {
    Sum += Probabilities[i];
    Probabilities[i] = Sum;
  }
  
  //Normalize the distribution.
  for(count i = 0; i < Probabilities.n(); i++)
    Probabilities[i] /= Sum;
}

//-----------//
//Information//
//-----------//

count LowestDataAccess = 0;
count HighestDataAccess = 0;
String MathFile = "a={";

//-------//
//Globals//
//-------//

Random r(GlobalSeed);
Array<ascii> Instructions;
Array<byte> Data;
Array<byte> Result;
Array<count> Map;
count InstructionPointer = 0;
count DataPointer = 0;
Ratio GlobalTime = 0;
count CycleCount = 0;

//-------------//
//Toggle Groups//
//-------------//

bool Toggles[4] = {true, true, true, true};

//-----------//
//Pitch Class//
//-----------//
count PitchClass[12] = {GlobalPitch0, GlobalPitch1, GlobalPitch2, GlobalPitch3, 
  GlobalPitch4, GlobalPitch5, GlobalPitch6, GlobalPitch7, GlobalPitch8,
  GlobalPitch9, GlobalPitch10, GlobalPitch11}; 

//--------//
//Dynamics//
//--------//

const count Dynamics = 7;
Ratio Dynamic[Dynamics] = {Ratio(0, 7), Ratio(1, 7), Ratio(2, 7), Ratio(3, 7),
  Ratio(4, 7), Ratio(5, 7), Ratio(6, 7)};

//-------//
//Rhythms//
//-------//

count DurationIndex = 0;
Array<Ratio> Durations;
void CreateDurations(void)
{
  if(GlobalRhythmSixteenth) Durations.Add() = Ratio(1, 16);
  if(GlobalRhythmTripletEighth) Durations.Add() = Ratio(1, 12);
  if(GlobalRhythmEighth) Durations.Add() = Ratio(1, 8);
  if(GlobalRhythmTripletQuarter) Durations.Add() = Ratio(1, 6);
  if(GlobalRhythmQuarter) Durations.Add() = Ratio(1, 4);
}

//---------------//
//Notes and Parts//
//---------------//

struct Instrument;
Array<Instrument*> Instruments;

struct Note
{
  Ratio t, d;
  count p;
  Ratio m;
  Note() : t(0), d(0), p(0), m(0) {}
  Note(Ratio t, Ratio d, count p, Ratio m) : t(t), d(d), p(p), m(m) {}
  
  //Generate articulation to emphasize existing rhythm and dynamics.
  String Articulation(void)
  {
    if(d <= Ratio(1, 8)) //Short rhythm
    {
      if(m < Ratio(3, 7))
        return " [.] "; //Staccato for ppp, pp, p
      else if(m >= Ratio(4, 7) && m < Ratio(6, 7))
        return " [>] "; //Accent for f, ff
    }
    else if(d > Ratio(1, 2)) //Long rhythm
      return " [-] "; //Tenuto
    return "";
  }
};

struct Instrument
{
  count ID;
  String Name;
  count Low;
  count High;
  Array<Note> Notes;
  Ratio Offset;
  count DynamicMark;
  
  Instrument(count ID, String Name, count Low, count High) : ID(ID), Name(Name),
    Low(Low), High(High), Offset(0), DynamicMark(3) {}
  
  void ToFOMUS(String& s)
  {
    s >> "" >> "part: " << Name;
    for(count i = 0; i < Notes.n(); i++)
    {
      s >> "time: " << (Notes[i].t * 4).ToString() << " dur: " <<
        (Notes[i].d * 4).ToString() << " pitch: " << Notes[i].p << 
        " dynamic: " << (number)Notes[i].m << Notes[i].Articulation() << ";";
    }
  }
  
  void CreateHairpins(void)
  {
    count Start = 0;
    if(!Notes.n())
      return;
    Ratio StartDynamic = Notes[0].m; 
    for(count i = 1; i < Notes.n(); i++)
    {
      Ratio CurrentDynamic = Notes[i].m;
      if(CurrentDynamic != StartDynamic)
      {
        for(count j = Start + 1; j < i; j++)
        {
          Ratio Fraction = Ratio(j - Start - 1) / Ratio(i - Start - 1);
          Ratio Interpolated = StartDynamic + (CurrentDynamic - StartDynamic) *
            Fraction;
          Notes[j].m = Interpolated;
        }
        Start = i;
        StartDynamic = CurrentDynamic;
      }
    }
  }
  
  inline count LookupPitch(byte p)
  {
    int8 x = (int8)p;
    
    //Find the first C and make that 0.
    count NoteStart = Low;
    if(NoteStart % 12 != 0)
      NoteStart += (12 - (Low % 12));
    
    if(Low == High)
      return Low;
    
    if(x == 0)
      return NoteStart;
    if(x > 0)
    {
      for(count i = 0; i < x; i++)
      {
        while(!PitchClass[(++NoteStart) % 12]) {}
        if(NoteStart > High) //Octave down as far as possible if out of range.
          while(NoteStart - 12 >= Low)
            NoteStart -= 12; 
      }
    }
    else
    {
      for(count i = 0; i < -x; i++)
      {
        while(!PitchClass[(--NoteStart) % 12]) {}
        if(NoteStart < Low) //Octave up as far as possible if out of range.
          while(NoteStart + 12 <= High)
            NoteStart += 12; 
      }
    }
    return NoteStart;
  }
  
  count Group(void)
  {
    count Base = FirstInstrument;
    if(ID < Brass - FirstInstrument)
      return 0;
    else if(ID < Percussion - FirstInstrument)
      return 1;
    /*Note: <= is used below to compensate for a bug in the original where the
    Violin was considered part of the percussion group for toggling purposes. If
    backwards compatibility is not a concern then it can be changed to <.*/
    else if(ID <= Strings - FirstInstrument)
      return 2;
    return 3;
  }
  
  void Add(byte p)
  {
    bool On = Toggles[Group()];
    count ActualPitch = LookupPitch(p);
    if(Offset == GlobalTime)
    {
      Ratio d = Durations[DurationIndex];
      if(On)
        Notes.Add() = Note(Offset, d, ActualPitch, Dynamic[DynamicMark]);
      Offset += d;
      GlobalTime = Offset;
    }
    else if(Offset < GlobalTime)
    {
      if(GlobalTime - Offset > Ratio(GlobalLongestNote, (count)4))
        Offset = GlobalTime - Ratio(GlobalLongestNote, (count)4);
      Ratio d = GlobalTime - Offset;
      if(On)
        Notes.Add() = Note(Offset, d, ActualPitch, Dynamic[DynamicMark]);
      Offset += d;
    }
  }
};

//-----------//
//Computation//
//-----------//

ascii GetInstruction(void) {return Instructions[InstructionPointer];}

byte& GetData(void)
{
  if(DataPointer < LowestDataAccess) LowestDataAccess = DataPointer;
  if(DataPointer > HighestDataAccess) HighestDataAccess = DataPointer;
  
  //Fancy bullet-proof wrap.
  count Position = (DataPointer + Data.n() * Abs(DataPointer)) % Data.n();
  byte& Value = Data[Position];
  MathFile << "{" << GlobalTime.ToPrettyString() << ", " << Position << ", " <<
    (count)(int8)Value << "}, ";
  return Value;
}

bool Halt(void)
{
  return InstructionPointer >= Instructions.n() || InstructionPointer < 0;
}

void Emit(ascii i)
{
  if(i == DecrementDuration)
    DurationIndex = Max((count)0, DurationIndex - 1);
  else if(i == IncrementDuration)
    DurationIndex = Min((count)Durations.n() - 1, DurationIndex + 1);
  else if(i >= FirstInstrument && i <= LastInstrument)
  {
    count InstrumentID = i - FirstInstrument;
    Instruments[InstrumentID]->Add(GetData());
  }
  else if(i >= ToggleWinds && i <= ToggleStrings)
  {
    Toggles[i - ToggleWinds] = !Toggles[i - ToggleWinds];
    if(!Toggles[0] && !Toggles[1] && !Toggles[2] && !Toggles[3])
      Toggles[0] = Toggles[1] = Toggles[2] = Toggles[3] = true;
  }
  else if(i >= FirstDynamic && i <= LastDynamic)
  {
    count DynamicID = i - FirstDynamic;
    count DynamicType = DynamicID % 4;
    count DynamicInstrument = (DynamicID - DynamicType) / 4;
    count& DynamicMark = Instruments[DynamicInstrument]->DynamicMark;
    if(DynamicType == 0)
      DynamicMark = 2;
    else if(DynamicType == 1)
      DynamicMark = 4;
    else if(DynamicType == 2)
    {
      if(GlobalWrapDynamics)
        DynamicMark = (Dynamics + DynamicMark - 1) % Dynamics;
      else
        DynamicMark = Max(DynamicMark - 1, (count)0);
    }
    else
    {
      if(GlobalWrapDynamics)
        DynamicMark = (Dynamics + DynamicMark + 1) % Dynamics;
      else
        DynamicMark = Min(DynamicMark + 1, Dynamics - 1);
    }
  }
}

bool PerformInstruction(void)
{
  CycleCount++;
  if(Halt()) return false;
  ascii i = GetInstruction();
  if(i == MoveForward) DataPointer++;
  else if(i == MoveBackward) DataPointer--;
  else if(i == IncrementData) GetData()++;
  else if(i == DecrementData) GetData()--;
  else if((i == WhileBegin && !GetData()) || (i == WhileEnd && GetData()))
  {
    if(i != WhileEnd || r.Between((count)0, GlobalLoopContinueRate))
    {
      //Perform jump operation to emulate while loops.
      count BraceCount = 1;
      do
      {
        InstructionPointer += (i == WhileBegin ? 1 : -1);
        if(Halt()) return false;
        if(GetInstruction() == (i == WhileBegin ? WhileEnd : WhileBegin))
          BraceCount--;
        else if(GetInstruction() == (i == WhileEnd ? WhileEnd : WhileBegin))
          BraceCount++;
      } while(BraceCount > 0);
    }
  }
  else
    Emit(i);
  InstructionPointer++;
  return true;
}

//------//
//Output//
//------//

void GenerateParts(void)
{
  String s;
  File::Read("out.ly", s);
  count i = s.Find("%% score");
  s.Erase(i, s.n() - 1);
  
  String h;
  h >> "%% score";
  h >> "\\score {";
  h >> "  <<";
  h >> "    #(set-accidental-style 'forget 'Score)";
  
  String f;
  f >> "    \\set Score.barNumberVisibility = "
    "#(every-nth-bar-number-visible 1)";
  f >> "    \\override Score.BarNumber #'break-visibility = #'#(#t #t #t)";
  f >> "    \\override Score.BarNumber #'font-size = #1";
  f >> "  >>";
  f >> "}";
  
  Array< Array<String> > Parts;
  Parts.Add();
  if(s.Contains("Flute")) Parts.Add().Add() = Parts.a().Add() = "Flute";
  if(s.Contains("Oboe")) Parts.Add().Add() = Parts.a().Add() = "Oboe";
  if(s.Contains("Clarinet")) Parts.Add().Add() = Parts.a().Add() = "Clarinet";
  if(s.Contains("Bassoon")) Parts.Add().Add() = Parts.a().Add() = "Bassoon";
  if(s.Contains("Horn")) Parts.Add().Add() = Parts.a().Add() = "Horn";
  if(s.Contains("Trumpet")) Parts.Add().Add() = Parts.a().Add() = "Trumpet";
  if(s.Contains("Trombone")) Parts.Add().Add() = Parts.a().Add() = "Trombone";
  if(s.Contains("BaritoneSax")) Parts.Add().Add() = Parts.a().Add() = "BaritoneSax";
  if(s.Contains("Vibraphone")) Parts.Add().Add() = Parts.a().Add() = "Vibraphone";
  if(s.Contains("Crotales")) Parts.Add().Add() = Parts.a().Add() = "Crotales";
  if(s.Contains("Violin")) Parts.Add().Add() = Parts.a().Add() = "Violin";
  if(s.Contains("Viola")) Parts.Add().Add() = Parts.a().Add() = "Viola";
  if(s.Contains("Cello")) Parts.Add().Add() = Parts.a().Add() = "Cello";
  if(s.Contains("DoubleBass")) Parts.Add().Add() = Parts.a().Add() = "DoubleBass";
  
  for(count i = 0; i < Parts.n(); i++)
  {
    String n;
    if(!i)
      n << "Ensemble";
    else
      n << Parts[i].a();
    n << ".ly";
    String g = s;
    if(i)
    {
      g.Replace(EnsemblePaper, PartPaper);
      g.Replace("'landscape", "'portrait");
    }
    else
    {
      if(Parts.n() > 15)
        g.Replace("'landscape", "'portrait");
    }
    
    //Get rid of any mezzo-pianos (on principle) and bump up dynamics.
    g.Replace("\\ff ", "\\fff ");
    g.Replace("\\ff\\", "\\fff\\");
    g.Replace("\\f ", "\\ff ");
    g.Replace("\\f\\", "\\ff\\");
    g.Replace("\\mf ", "\\f ");
    g.Replace("\\mf\\", "\\f\\");
    g.Replace("\\mp ", "\\mf ");
    g.Replace("\\mp\\", "\\mf\\");
    
    g >> h;
    for(count j = 0; j < Parts[i].n(); j++)
      g >> "    \\new Staff \\part" << Parts[i][j];
    g >> f;
    File::Write(n, g);
  }
  
  //Fix dynamics in MusicXML file too.
  File::Read("out.xml", s);
  s.Replace("<ff/>", "<fff/>");
  s.Replace("<f/>", "<ff/>");
  s.Replace("<mf/>", "<f/>");
  s.Replace("<mp/>", "<mf/>");
  File::Write("out.xml", s);
}

bool InstrumentUsed(count EmitCode)
{
  return (bool)Instruments[EmitCode - FirstInstrument]->Notes.n();
}

String GetFOMUSHeader(void)
{
  String s;
  s >> "dyns=yes" >> "layout=orchestra" >> "lily-landscape=yes";
  s >> "lily-papersize=\"" << EnsemblePaper << "\"";
  s >> "lily-file-topheader=\"\\\\header{\\ntitle=\\\"" << InfoTitle <<
    "\\\"\\ncomposer=\\\"" << InfoComposer << "\\\"\\ntagline=##f}\\n\\\\paper "
    "{\\n#(define bottom-margin (* 0.75 in))\\n#(define top-margin (* 0.75 "
    "in))\\n#(define left-margin (* 1.0 in))\\n#(define right-margin (* 0.75 "
    "in))}\"";
  s >> "lily-exe-path=\"\"" >> "dyn-repeat=yes" >> "dynphrase-maxrestdur=16";
  s >> "dyn-sticky=0" >> "dyn-wedge-maxrestdur=20" >> "max-tupletdur=1";
  s >> "transpose-keysigs=no" >> "init-tempo=" << GlobalTempo;
  s >> "accs-diatonic-note-score=1000";
  
  if(InstrumentUsed(EmitFlute))
    s >> "part <id: Flute inst: <template: flute> abbr: \"Fl.\">";
  if(InstrumentUsed(EmitOboe))
    s >> "part <id: Oboe inst: <template: oboe> abbr: \"Ob.\">";
  if(InstrumentUsed(EmitClarinet))
    s >> "part <id: Clarinet inst: <template: bflat-clarinet> transpose-part:"
      " yes abbr: \"Cl.\">";
  if(InstrumentUsed(EmitBassoon))
    s >> "part <id: Bassoon inst: <template: bassoon> abbr: \"Fg.\">";
  if(InstrumentUsed(EmitHorn))
    s >> "part <id: Horn inst: <template: horn> transpose-part: yes abbr: "
      "\"Hn.\">";
  if(InstrumentUsed(EmitTrumpet))
    s >> "part <id: Trumpet inst: <template: c-trumpet> abbr: \"Trp.\">";
  if(InstrumentUsed(EmitTrombone))
    s >> "part <id: Trombone inst: <template: tenor-trombone> abbr: "
      "\"Trmb.\">";
  if(InstrumentUsed(EmitBaritoneSax))
    s >> "part <id: BaritoneSax inst: <template: baritone-saxophone> "
      "transpose-part: yes abbr: \"Bar-Sax.\">";
  if(InstrumentUsed(EmitVibraphone))
    s >> "part <id: Vibraphone inst: <template: vibraphone> abbr: \"Vib.\">";
  if(InstrumentUsed(EmitCrotales))
    s >> "part <id: Crotales inst: <template: vibraphone> name: \"Crotales\" "
      "abbr: \"Crot.\" min-pitch: 60 max-pitch: 84>";
  if(InstrumentUsed(EmitViolin))
    s >> "part <id: Violin inst: <template: violin> abbr: \"Vn.\">";
  if(InstrumentUsed(EmitViola))
    s >> "part <id: Viola inst: <template: viola> abbr: \"Va.\">";
  if(InstrumentUsed(EmitCello))
    s >> "part <id: Cello inst: <template: cello> abbr: \"Vc.\">";
  if(InstrumentUsed(EmitDoubleBass))
    s >> "part <id: DoubleBass inst: <template: contrabass> abbr: \"Cb.\">";
  return s;
}

void FinalizeMathFile(void)
{
  MathFile.Erase(MathFile.n() - 2, MathFile.n() - 1);
  MathFile << "};";
  MathFile >> "Export[\"xy.png\",ListPointPlot3D[a, PlotRange->All,ViewPoint->"
    "{0,0,Infinity},PlotLabel->\"Time vs. Memory Head Location\"],"
    "ImageSize->1000]";
  MathFile >> "Export[\"xz.png\",ListPointPlot3D[a, PlotRange->All,ViewPoint->"
    "{0,-Infinity,0},PlotLabel->\"Time vs. Memory Value\"],ImageSize->1000]";
  MathFile >> "Export[\"yz.png\",ListPointPlot3D[a, PlotRange->All,ViewPoint->"
    "{Infinity,0,0},PlotLabel->\"Memory Head Location vs. Memory Value\"],"
    "ImageSize->1000]";
  MathFile >> "Export[\"xyz.png\",ListPointPlot3D[a, PlotRange->All,"
    "ViewPoint->{10000,-10000,10000},PlotLabel->\"Time vs. Memory Location vs. "
    "Memory Value\"],ImageSize->1000]";
}

//--------------//
//Piece Creation//
//--------------//

void CreateInstruments(Array<Instrument*>& i)
{
  i.Add() = new Instrument(0,  "Flute",       67, 98 + GlobalRange); //G4-D6
  i.Add() = new Instrument(1,  "Oboe",        60, 84 + GlobalRange); //C4-C6
  i.Add() = new Instrument(2,  "Clarinet",    50, 79 + GlobalRange); //D3-G5
  i.Add() = new Instrument(3,  "Bassoon",     36, 67 + GlobalRange); //C2-G4
  i.Add() = new Instrument(4,  "Horn",        48, 72 + GlobalRange); //C3-C5
  i.Add() = new Instrument(5,  "Trumpet",     55, 79 + GlobalRange); //G3-G5
  i.Add() = new Instrument(6,  "Trombone",    43, 67 + GlobalRange); //G2-G4
  i.Add() = new Instrument(7,  "BaritoneSax", 43, 60 + GlobalRange); //G2-C4
  i.Add() = new Instrument(8,  "Vibraphone",  53, 89);               //F3-F6
  i.Add() = new Instrument(9,  "Crotales",    60, 84);               //C2-C4
  i.Add() = new Instrument(10, "Violin",      55, 84 + GlobalRange); //G3-C6
  i.Add() = new Instrument(11, "Viola",       48, 79 + GlobalRange); //C3-G5
  i.Add() = new Instrument(12, "Cello",       36, 67 + GlobalRange); //C2-G5
  i.Add() = new Instrument(13, "DoubleBass",  28, 48 + GlobalRange); //E2-C4
}

count GetProbableInstruction(number NormalizedNumber)
{
  for(count i = 0; i < Probabilities.n(); i++)
    if(NormalizedNumber < Probabilities[i])
      return i;
  return 0;
}

void CreatePiece(void)
{
  //Initialize constants and distributions.
  CreateDurations();
  CreateInstruments(Instruments);
  SetPlanProbabilities();
  DistributeProbabilities(0.0);
  
  //Initialize state and maps
  Instructions.n(GlobalCodeLength);
  Instructions.Zero();
  InstructionPointer = 0;
  Data.n(GlobalTapeLength);
  Data.Zero();
  
  //Plan loops.
  {
    count a = GlobalLoopInnerStartLow;
    count b = a + GlobalLoopInnerStartHigh;
    count c = b + GlobalLoopInnerEndLow;
    count d = c + GlobalLoopInnerEndHigh;
    count e = d + GlobalLoopOuterEndLow;
    count f = e + GlobalLoopOuterEndHigh;
    count g = f + GlobalLoopStep;
    for(count i = 0; i < Instructions.n() - g; i++)
    {
      if(r.Between((count)0, GlobalLoopSkipCreateRate))
        continue;
      Instructions[i] = WhileBegin;
      Instructions[i + r.Between(e, f)] = WhileEnd;
      Instructions[i + r.Between(a, b)] = WhileBegin;
      Instructions[i + r.Between(c, d)] = WhileEnd;
      i += g;
    }
  }
  
  //Plan instructions.
  for(count i = 0; i < Instructions.n(); i++)
  {
    SetPlanProbabilities();
    DistributeProbabilities((number)((i / (Instructions.n() / 
      GlobalProbabilityInversionSections)) % 2));
    if(!Instructions[i])
      Instructions[i] = GetProbableInstruction(r.NextNumber());
  }
  
  //Run the program.
  while(PerformInstruction()) {}
  
  //Create hash.
  String s;
  for(count i = LowestDataAccess; i <= HighestDataAccess; i++)
  {
    if(LowestDataAccess < 0 && !i) s >> "[0x0000]" >> "";
    s << (count)(int8)Data[(i + Data.n()) % Data.n()];
    if(i < HighestDataAccess)
      s << ", ";
  }
  String DataHash = MD5::Hex(s.Merge());
  
  //Output information.
  c >> "Unique Hash: " << DataHash;
  c >> "Tape Size: " << GlobalTapeLength;
  c >> "Tape Used: " << (HighestDataAccess - LowestDataAccess + 1);
  c >> "Cycles expended: " << CycleCount;
  c >> "Length: " << (number)(GlobalTime * 4) / (number)GlobalTempo <<
    " minutes @ " << GlobalTempo << " bpm";
  c++;
  
  //Output Mathematica file.
  FinalizeMathFile();
  File::Write("Generated/out.m", MathFile);
  
  //Export the FOMUS file.
  String Out = GetFOMUSHeader();
  for(count i = 0; i < Instruments.n(); i++)
  {
    if(InstrumentUsed(i + FirstInstrument))
    {
      if(GlobalUseHairpins)
        Instruments[i]->CreateHairpins();
      Instruments[i]->ToFOMUS(Out);
    }
  }
  File::Write("Generated/out.fms", Out);
  
  //Clean up.
  Instruments.ClearAndDeleteAll();
}

int main(int ArgumentCount, const char** Arguments)
{
  if(ArgumentCount == 2 && String(Arguments[1]) == "--generateparts")
    GenerateParts();
  else
    CreatePiece();
  return 0;
}
