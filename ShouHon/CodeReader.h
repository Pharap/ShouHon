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

#include "Opcode.h"
#include "FlashString.h"

class CodeReader
{
private:
	uint8_t const * source = nullptr;
	uint16_t sourceIndex = 0;
	
public:
	CodeReader(void) = default;
	CodeReader(uint8_t const * source);
	
	uint8_t const * getSource(void) const;
	
	void jumpBy(int16_t const & offset);
	
	void jumpTo(uint16_t const & address);

	//FlashString readString(void);

	Opcode peekOpcode(void) const;
	
	Opcode readOpcode(void);
	
	uint8_t peekU8(void) const;
	
	uint8_t readU8(void);
	
	int8_t peekS8(void) const;
	
	int8_t readS8(void);
	
	uint16_t peekU16(void) const;
	
	uint16_t readU16(void);
	
	int16_t peekS16(void) const;
	
	int16_t readS16(void);
};