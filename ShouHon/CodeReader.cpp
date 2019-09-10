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

#include <Arduino.h>

#include "CodeReader.h"
	
CodeReader::CodeReader(uint8_t const * source)
	: source(source)
{
}
	
uint8_t const * CodeReader::getSource(void) const
{
	return this->source;
}
	
void CodeReader::jumpBy(int16_t const & offset)
{
	this->sourceIndex += offset;
}
	
void CodeReader::jumpTo(uint16_t const & address)
{
	this->sourceIndex = address;
}

/*FlashString CodeReader::readString(void)
{
	const auto length = this->readU8();
	const auto result = AsFlashString(&this->source[this->sourceIndex]);
	this->sourceIndex += length;
	return result;
}*/

Opcode CodeReader::peekOpcode() const
{
	return static_cast<Opcode>(this->peekU8());
}

Opcode CodeReader::readOpcode()
{
	return static_cast<Opcode>(this->readU8());
}

uint8_t CodeReader::peekU8() const
{
	return static_cast<uint8_t>(pgm_read_byte(&this->source[this->sourceIndex]));
}

uint8_t CodeReader::readU8()
{
	const auto result = static_cast<uint8_t>(pgm_read_byte(&this->source[this->sourceIndex]));
	++this->sourceIndex;
	return result;
}

int8_t CodeReader::peekS8() const
{
	return static_cast<int8_t>(this->peekU8());
}

int8_t CodeReader::readS8()
{
	return static_cast<int8_t>(this->readU8());
}

uint16_t CodeReader::peekU16() const
{
	const uint16_t high = static_cast<uint8_t>(pgm_read_byte(&this->source[this->sourceIndex + 0]));
	const uint16_t low = static_cast<uint8_t>(pgm_read_byte(&this->source[this->sourceIndex + 1]));
	return (high << 8 | low);
}

uint16_t CodeReader::readU16()
{
	uint16_t result = this->readU8();
	result <<= 8;
	result |= this->readU8();
	return result;
	
	/*const uint16_t high = static_cast<uint8_t>(pgm_read_byte(&this->source[this->sourceIndex + 0]));
	const uint16_t low = static_cast<uint8_t>(pgm_read_byte(&this->source[this->sourceIndex + 1]));
	this->sourceIndex += 2;
	return (high << 8 | low);*/
}

int16_t CodeReader::peekS16() const
{
	return static_cast<int16_t>(this->peekU16());
}

int16_t CodeReader::readS16()
{
	return static_cast<int16_t>(this->readU16());
}