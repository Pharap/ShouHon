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

#undef INSTRUCTION
#undef BYTE
#undef WORD

#undef I
#undef IB
#undef IW
#undef IB4

#undef PROGRAM
#undef ENDPROGRAM

//
// Infrastructure
//

#undef NOP
#undef END
#undef BRK
#undef JMPR
#undef JMPA
#undef CALL
#undef RET

//
// Stack manipulation
//

#undef PUSH1
#undef PUSH2
#undef DROP
#undef DROPN
#undef DUPE
#undef SWAP


//
// Variables
//

#undef SETLOCAL
#undef GETLOCAL
#undef SETGLOBAL
#undef GETGLOBAL
#undef SAVEGLOBAL
#undef SAVEGLOBALS

//
// Branching
//

#undef EQR
#undef EQA
#undef NER
#undef NEA
#undef GTR
#undef GTA
#undef GTER
#undef GTEA
#undef LTR
#undef LTA
#undef LTER
#undef LTEA

//
// Bitwise operations
//

#undef AND
#undef ANDI
#undef OR
#undef ORI
#undef EOR
#undef EORI
#undef SHL
#undef SHLI
#undef SHR
#undef SHRI
#undef NOT

//
// Arithmetic operations
//

#undef ADD
#undef ADDI
#undef SUB
#undef SUBI
#undef INC
#undef DEC
#pragma pop_macro("DEC")
#undef NEG

//
// Time
//

#undef DELAYF
#undef DELAYS
#undef DELAYDS
#undef DELAYCS
#undef DELAYMS

//
// Buttons
//

#undef WAIT

//
// Images
//

#undef BG
#undef CLEARBG
#undef FG
#undef CLEARFG

//
// Music
//

#undef PLAY
#undef STOP

//
// Text
//

#undef SHOWTEXT
#undef HIDETEXT
#undef CLEARTEXT
#undef CLEARLINE
#undef SCROLL
#undef NL
#undef BL
#undef PRINT
#undef PRINTTOP
#undef PRINTNL
#undef BLPRINT

//
// Choice
//

#undef SHOWCHOICE
#undef HIDECHOICE
#undef CLEARCHOICE
#undef ADDCHOICE