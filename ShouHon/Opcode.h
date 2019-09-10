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

#pragma once

enum class Opcode : uint8_t
{
	//
	// Infrastructure
	//

	// NOP
	Nop,

	// END
	End,

	// BRK
	Break,

	// JMPR offset:s8
	JumpR,

	// JMPA address:u16
	JumpA,

	// CALL address:u16
	//Call,

	// RET
	//Return,

	//
	// Stack manipulation
	//

	// PUSH value:u8
	Push1,

	// PUSH value:u16
	Push2,

	// DROP
	Drop,

	// DROPN count:u8
	DropN,

	// DUPE
	Dupe,

	// SWAP
	Swap,

	//
	// Variables
	//

	// SETLOCAL index:u8
	SetLocal,

	// GETLOCAL index:u8
	GetLocal,

	// SETGLOBAL index:u8
	SetGlobal,

	// GETGLOBAL index:u8
	GetGlobal,

	// SAVEGLOBAL index:u8
	SaveGlobal,

	// SAVEGLOBALS
	SaveGlobals,

	//
	// Branching
	//

	BrEqR,
	BrEqA,
	BrNER,
	BrNEA,
	BrGTR,
	BrGTA,
	BrGTER,
	BrGTEA,
	BrLTR,
	BrLTA,
	BrLTER,
	BrLTEA,

	//
	// Bitwise operations
	//

	// AND
	And,

	// ANDI value:u8
	AndI,

	// OR
	Or,

	// ORI value:u8
	OrI,

	// EXOR
	ExOr,

	// EXORI value:u8
	ExOrI,

	// SHL
	ShL,

	// SHLI value:u8
	ShLI,

	// SHR
	ShR,

	// SHRI value:u8
	ShRI,

	// NOT
	Not,

	//
	// Arithmetic operations
	//

	// ADD
	Add,

	// ADDI value:u8
	AddI,

	// SUB
	Sub,

	// SUBI value:u8
	SubI,

	// INC
	Increment,

	// DEC
	Decrement,

	// NEG
	Negate,

	//
	// Time
	//

	// DELAYF fraction:u8
	DelayF,

	// DELAYS seconds:u8
	DelayS,

	// DELAYCS deciseconds:u8
	DelayDS,

	// DELAYCS centiseconds:u8
	DelayCS,

	// DELAYMS milliseconds:u16
	DelayMS,

	//
	// Buttons
	//

	AwaitInput,

	//
	// Images
	//

	Background,
	ClearBackground,
	Foreground,
	ClearForeground,

	//
	// Music
	//

	PlayMusic,
	StopMusic,

	//
	// Text
	//

	ShowTextBox,
	HideTextBox,
	ClearTextBox,

	ClearLine,

	Scroll,
	NewLine,
	BlankLine,

	PrintString,
	PrintTop,

	PrintNewLine,
	BlankLinePrint,

	//
	// Choice
	//

	ShowChoiceBox,
	HideChoiceBox,
	ClearChoiceBox,

	// ADDCHOICE index:u8
	AddChoice,
};