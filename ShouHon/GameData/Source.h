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

#include "../Opcode.h"

#include "../OpcodeHelperBegin.h"

#if defined(CHOICE_TEST)

PROGRAM(Source)
/*0*/	WAIT
	
/*1*/	BG(0)
/*3*/	WAIT
	
/*4*/	SHOWTEXT
/*5*/	WAIT
	
/*6*/	BLPRINT(0)
/*8*/	WAIT
	
/*9*/	CLEARCHOICE
		// MUSHY PEAS
/*10*/	ADDCHOICE(1)
		// GREEN SPAGHETTI
/*12*/	ADDCHOICE(2)
		// A LADLE
/*14*/	//ADDCHOICE(3)
/*16*/	SHOWCHOICE
/*16B*/	CLEARTEXT

		// MUSHY PEAS
/*17*/	DUPE
/*18*/	PUSH1(0)
/*20*/	NER(+5) // 27 = 22 + 5
/*22*/	BLPRINT(4)
/*24*/	WAIT
/*25*/	JMPR(-12) // 16 = 27 - 11

		// A LADLE
/*27*/	DUPE
/*28*/	PUSH1(2)
/*30*/	NER(+4) // 36 = 32 + 4
/*32*/	BLPRINT(6)
/*34*/	WAIT	
/*35*/	END

		// GREEN SPAGHETTI
/*36*/	DUPE
/*37*/	PUSH1(1)
/*39*/	NER(+4) // 45 = 41 + 4
/*41*/	BLPRINT(5)
/*43*/	WAIT	
/*44*/	END
	
		// IMPOSSIBLE
/*45*/	BLPRINT(7)
/*47*/	WAIT
/*48*/	END
ENDPROGRAM

#elif defined(TIMER_TEST)

PROGRAM(Source)
	WAIT
	
	BG(0)
	WAIT
	
	SHOWTEXT
	WAIT
	
	BLPRINT(0)
	DELAYS(1)
	
	BLPRINT(1)
	DELAYS(2)
	
	BLPRINT(2)
	WAIT
	
	END
ENDPROGRAM

#elif defined(IMAGE_TEST)

const uint8_t Source[] PROGMEM =
{
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::Background), 0,
	static_cast<uint8_t>(Opcode::AwaitInput),
	
	static_cast<uint8_t>(Opcode::ShowTextBox),
	static_cast<uint8_t>(Opcode::AwaitInput),
	
	static_cast<uint8_t>(Opcode::BlankLinePrint), 0,
	static_cast<uint8_t>(Opcode::AwaitInput),
	
	static_cast<uint8_t>(Opcode::Foreground), 0, 0, 8, 8,
	static_cast<uint8_t>(Opcode::BlankLinePrint), 1,
	static_cast<uint8_t>(Opcode::AwaitInput),
	
	static_cast<uint8_t>(Opcode::BlankLine),
	static_cast<uint8_t>(Opcode::Push1), 128,
	static_cast<uint8_t>(Opcode::PrintTop),
	static_cast<uint8_t>(Opcode::AwaitInput),
		
	static_cast<uint8_t>(Opcode::Foreground), 0, 1, 16, 8,
	static_cast<uint8_t>(Opcode::BlankLinePrint), 2,
	static_cast<uint8_t>(Opcode::AwaitInput),
	
	static_cast<uint8_t>(Opcode::Foreground), 1, 0, 32, 8,
	static_cast<uint8_t>(Opcode::BlankLinePrint), 3,
	static_cast<uint8_t>(Opcode::AwaitInput),
	
	static_cast<uint8_t>(Opcode::Foreground), 1, 1, 64, 8,
	static_cast<uint8_t>(Opcode::BlankLinePrint), 4,
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::End)
};

#elif defined(LONG_TEST)

const uint8_t Source[] PROGMEM =
{
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::Background), 0,
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::ShowTextBox),
	static_cast<uint8_t>(Opcode::BlankLinePrint), 0,
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::BlankLinePrint), 5,
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::BlankLinePrint), 6,
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::ClearTextBox),
	static_cast<uint8_t>(Opcode::BlankLinePrint), 7,
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::BlankLinePrint), 8,
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::ClearTextBox),
	static_cast<uint8_t>(Opcode::BlankLinePrint), 9,
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::BlankLinePrint), 1,
	static_cast<uint8_t>(Opcode::AwaitInput),

	static_cast<uint8_t>(Opcode::ClearTextBox),
	static_cast<uint8_t>(Opcode::Push1), 3,

	static_cast<uint8_t>(Opcode::BlankLinePrint), 2,
	static_cast<uint8_t>(Opcode::PrintTop),
	static_cast<uint8_t>(Opcode::PrintString), 3,

	static_cast<uint8_t>(Opcode::Decrement),
	static_cast<uint8_t>(Opcode::Dupe),
	static_cast<uint8_t>(Opcode::Push1), 0,
	static_cast<uint8_t>(Opcode::AwaitInput),
	static_cast<uint8_t>(Opcode::BrLTR), static_cast<uint8_t>(-12),
	static_cast<uint8_t>(Opcode::PrintString), 4,
	static_cast<uint8_t>(Opcode::End)
};

#endif

#include "../OpcodeHelperEnd.h"