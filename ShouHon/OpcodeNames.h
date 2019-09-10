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

#include "FlashUtils.h"
#include "Opcode.h"

FlashString GetOpcodeName(Opcode opcode)
{
	switch(opcode)
	{
		//
		// Infrastructure
		//
		case Opcode::Nop: return F("NOP");
		case Opcode::End: return F("END");
		case Opcode::Break: return F("BRK");
		case Opcode::JumpR: return F("JMPR");
		case Opcode::JumpA: return F("JMPA");
		//case Opcode::Call: return F("CALL");
		//case Opcode::Return: return F("RET");

		//
		// Stack manipulation
		//
		case Opcode::Push1: return F("PUSH1");
		case Opcode::Push2: return F("PUSH2");
		case Opcode::Drop: return F("DROP");
		case Opcode::DropN: return F("DROPN");
		case Opcode::Dupe: return F("DUPE");
		case Opcode::Swap: return F("SWAP");

		//
		// Variables
		//
		case Opcode::SetLocal: return F("SETLOCAL");
		case Opcode::GetLocal: return F("GETLOCAL");
		case Opcode::SetGlobal: return F("SETGLOBAL");
		case Opcode::GetGlobal: return F("GETGLOBAL");
		case Opcode::SaveGlobal: return F("SAVEGLOBAL");
		case Opcode::SaveGlobals: return F("SAVEGLOBALS");

		//
		// Branching
		//
		case Opcode::BrEqR: return F("EQR");
		case Opcode::BrEqA: return F("EQA");
		case Opcode::BrNER: return F("NER");
		case Opcode::BrNEA: return F("NEA");
		case Opcode::BrGTR: return F("GTR");
		case Opcode::BrGTA: return F("GTA");
		case Opcode::BrGTER: return F("GTER");
		case Opcode::BrGTEA: return F("GTEA");
		case Opcode::BrLTR: return F("LTR");
		case Opcode::BrLTA: return F("LTA");
		case Opcode::BrLTER: return F("LTER");
		case Opcode::BrLTEA: return F("LTEA");

		//
		// Bitwise operations
		//
		case Opcode::And: return F("AND");
		case Opcode::AndI: return F("ANDI");
		case Opcode::Or: return F("OR");
		case Opcode::OrI: return F("ORI");
		case Opcode::ExOr: return F("EOR");
		case Opcode::ExOrI: return F("EORI");
		case Opcode::ShL: return F("SHL");
		case Opcode::ShLI: return F("SHLI");
		case Opcode::ShR: return F("SHR");
		case Opcode::ShRI: return F("SHRI");
		case Opcode::Not: return F("NOT");

		//
		// Arithmetic operations
		//
		case Opcode::Add: return F("ADD");
		case Opcode::AddI: return F("ADDI");
		case Opcode::Sub: return F("SUB");
		case Opcode::SubI: return F("SUB");
		case Opcode::Increment: return F("INC");
		case Opcode::Decrement: return F("DEC");
		case Opcode::Negate: return F("NEG");

		//
		// Time
		//
		case Opcode::DelayF: return F("DELAYF");
		case Opcode::DelayS: return F("DELAYS");
		case Opcode::DelayDS: return F("DELAYDS");
		case Opcode::DelayCS: return F("DELAYCS");
		case Opcode::DelayMS: return F("DELAYMS");

		//
		// Buttons
		//
		case Opcode::AwaitInput: return F("WAIT");

		//
		// Images
		//
		case Opcode::Background: return F("BG");
		case Opcode::ClearBackground: return F("CLEARBG");
		case Opcode::Foreground: return F("FG");
		case Opcode::ClearForeground: return F("CLEARFG");

		//
		// Music
		//
		case Opcode::PlayMusic: return F("PLAY");
		case Opcode::StopMusic: return F("STOP");

		//
		// Text
		//
		case Opcode::ShowTextBox: return F("SHOWTEXT");
		case Opcode::HideTextBox: return F("HIDETEXT");
		case Opcode::ClearTextBox: return F("CLEARTEXT");
		
		case Opcode::ClearLine: return F("CLEARLINE");
		
		case Opcode::Scroll: return F("SCROLL");
		case Opcode::NewLine: return F("NL");
		case Opcode::BlankLine: return F("BL");
		
		case Opcode::PrintString: return F("PRINT");
		case Opcode::PrintTop: return F("PRINTTOP");
		case Opcode::PrintNewLine: return F("PRINTNL");
		case Opcode::BlankLinePrint: return F("BLPRINT");

		//
		// Choice
		//
		case Opcode::ShowChoiceBox: return F("SHOWCHOICE");
		case Opcode::HideChoiceBox: return F("HIDECHOICE");
		case Opcode::ClearChoiceBox: return F("CLEARCHOICE");
		case Opcode::AddChoice: return F("ADDCHOICE");

		default: return F("INVALID");
	}
}