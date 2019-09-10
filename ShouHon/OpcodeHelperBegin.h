//
// Copyright (C) 2018 Pharap (@Pharap)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#define INSTRUCTION(op) static_cast<uint8_t>(Opcode::op),
#define BYTE(x) static_cast<uint8_t>(x),
#define WORD(x) static_cast<uint8_t>((x >> 8) & 0xFF), static_cast<uint8_t>((x >> 0) & 0xFF),

#define I(op) INSTRUCTION(op)
#define IB(op, x) INSTRUCTION(op) BYTE(x)
#define IW(op, x) INSTRUCTION(op) WORD(x)
#define IB4(op, a, b, c, d) INSTRUCTION(op) BYTE(a) BYTE(b) BYTE(c) BYTE(d)

#define PROGRAM(name) \
	const uint8_t name [] PROGMEM = \
	{

#define ENDPROGRAM };

//
// Infrastructure
//

#define NOP I(Nop)
#define END I(End)
#define BRK I(Break)
#define JMPR(offset) IB(JumpR, offset)
#define JMPA(address) IW(JumpA, address)
//#define CALL(address) IW(Call, address)
//#define RET I(Return)

//
// Stack manipulation
//

#define PUSH1(value) IB(Push1, value)
#define PUSH2(value) IW(Push2, value)
#define DROP I(Drop)
#define DROPN(amount) IB(DropN, amount)
#define DUPE I(Dupe)
#define SWAP I(Swap)


//
// Variables
//

#define SETLOCAL(index) IB(SetLocal, index)
#define GETLOCAL(index) IB(GetLocal, index)
#define SETGLOBAL(index) IB(SetGlobal, index)
#define GETGLOBAL(index) IB(GetGlobal, index)
#define SAVEGLOBAL(index) IB(SaveGlobal, index)
#define SAVEGLOBALS I(SaveGlobals)

//
// Branching
//

#define EQR(offset) IB(BrEqR, offset)
#define EQA(address) IW(BrEqA, address)
#define NER(offset) IB(BrNER, offset)
#define NEA(address) IW(BrNEA, address)
#define GTR(offset) IB(BrGTR, offset)
#define GTA(address) IW(BrGTA, address)
#define GTER(offset) IB(BrGTER, offset)
#define GTEA(address) IW(BrGTEA, address)
#define LTR(offset) IB(BrLTR, offset)
#define LTA(address) IW(BrLTA, address)
#define LTER(offset) IB(BrLTER, offset)
#define LTEA(address) IW(BrLTEA, address)

//
// Bitwise operations
//

#define AND I(And)
#define ANDI(immediate) IB(AndI, immediate)
#define OR I(Or)
#define ORI(immediate) IB(OrI, immediate)
#define EOR I(ExOr)
#define EORI(immediate) IB(ExOrI, immediate)
#define SHL I(ShL)
#define SHLI(immediate) IB(ShLI, immediate)
#define SHR I(ShR)
#define SHRI(immediate) IB(ShRI, immediate)
#define NOT I(Not)

//
// Arithmetic operations
//

#define ADD I(Add)
#define ADDI(immediate) I(AddI, immediate)
#define SUB I(Sub)
#define SUBI(immediate) I(SubI, immediate)
#define INC I(Increment)
#pragma push_macro("DEC")
#undef DEC
#define DEC I(Decrement)
#define NEG I(Negate)

//
// Time
//

#define DELAYF(fraction) IB(DelayF, fraction)
#define DELAYS(seconds) IB(DelayS, seconds)
#define DELAYDS(deciseconds) IB(DelayDS, deciseconds)
#define DELAYCS(centiseconds) IB(DelayCS, centiseconds)
#define DELAYMS(milliseconds) IW(DelayMS, milliseconds)

//
// Buttons
//

#define WAIT I(AwaitInput)

//
// Images
//

#define BG(index) IB(Background, index)
#define CLEARBG(index) I(ClearBackground)
#define FG(index, x, y, frame) IB4(Foreground, index, x, y, frame)
#define CLEARFG(index) I(ClearForeground)

//
// Music
//

#define PLAY(index) IB(PlayMusic, index)
#define STOP(index) IB(StopMusic, index)

//
// Text
//

#define SHOWTEXT I(ShowTextBox)
#define HIDETEXT I(HideTextBox)
#define CLEARTEXT I(ClearTextBox)
#define CLEARLINE I(ClearLine)
#define SCROLL I(Scroll)
#define NL I(NewLine)
#define BL I(BlankLine)
#define PRINT(index) IB(Print, index)
#define PRINTTOP I(PrintTop)
#define PRINTNL(index) IB(PrintNewLine, index)
#define BLPRINT(index) IB(BlankLinePrint, index)

//
// Choice
//

#define SHOWCHOICE I(ShowChoiceBox)
#define HIDECHOICE I(HideChoiceBox)
#define CLEARCHOICE I(ClearChoiceBox)
#define ADDCHOICE(index) IB(AddChoice, index)
