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

#include <Arduboy2.h>
#include "FlashUtils.h"

#include "TextBox.h"
#include "ChoiceBox.h"
#include "SimpleTimer.h"

#include "Stack.h"
#include "CodeReader.h"

#include "Opcode.h"
#include "OpcodeNames.h"

#include "ProcessorState.h"
#include "ProcessorStateNames.h"

//
// Declaration
//

template< typename SettingsType >
class Processor;

enum class ErrorType : uint8_t
{
	None,
	InvalidOpcode,
	StackOverflow,
	StackUnderflow,
	IndexOutOfBounds,
};

template< typename SettingsType >
class Processor
{
public:
	using Settings = SettingsType;
	using TextBoxSettings = typename SettingsType::TextBoxSettings;
	using ChoiceBoxSettings = typename SettingsType::ChoiceBoxSettings;

	constexpr static uint8_t StackSize = Settings::StackSize;
	constexpr static uint8_t MaxGlobals = Settings::MaxGlobals;
	constexpr static uint8_t MaxLocals = Settings::MaxLocals;
	constexpr static uint8_t MaxImages = Settings::MaxImages;
	constexpr static uint16_t FastPrintDelay = Settings::FastPrintDelay;
	constexpr static uint16_t SlowPrintDelay = Settings::SlowPrintDelay;
	
private:
	class Image
	{
	public:
		uint8_t index;
		uint8_t frame;
		uint8_t x;
		uint8_t y;
	};
	
	Image images[MaxImages];
	uint8_t nextImage = 0;

private:
	using ProcessorTextBox = TextBox<TextBoxSettings>;
	using ProcessorChoiceBox = ChoiceBox<ChoiceBoxSettings>;
	
private:
	constexpr static const uint8_t InvalidIndex = ~0;

private:
	Arduboy2 arduboy = Arduboy2();
	CodeReader reader = CodeReader();

	Stack<StackSize> stack = Stack<StackSize>();

	uint16_t globalVariables[MaxGlobals];
	uint16_t localVariables[MaxLocals];
	
	ProcessorTextBox textbox = ProcessorTextBox();
	ProcessorChoiceBox choicebox = ProcessorChoiceBox();
	SimpleTimer timer = SimpleTimer();

	FlashString * strings = nullptr;
	
	const uint8_t * backgrounds = nullptr;
	uint8_t backgroundIndex = InvalidIndex;

	const uint8_t * const * sourceImages = nullptr;
	
	const uint8_t * tracks = nullptr;
	uint8_t trackIndex = InvalidIndex;

	ProcessorState state = ProcessorState::Idle;
	ProcessorState previousState = ProcessorState::Idle;
	
	bool atSpace = true;
	bool progmemPrint = false;
	char formatBuffer[6] { '\0' };
	char const * printChar = nullptr;

public:
	Processor(const uint8_t * source, FlashString const * strings, const uint8_t * backgrounds, uint8_t const * const * sourceImages, const uint8_t * tracks)
		: reader(source), strings(strings), backgrounds(backgrounds), sourceImages(sourceImages), tracks(tracks)
	{
	}

	void setup();
	void loop();

private:
	void update();
	void render();

	void handleError(const ErrorType & error, const Opcode & opcode);
	
	void updateDelayingState();
	void updatePrintingState();
	void updateWaitingState();
	void updatePausedState();
	void updateSavingState();
	void updateChoosingState();
	void updateProcessingState();
	
	void printIndexedString(uint8_t index)
	{
		this->printChar = static_cast<const char *>(pgm_read_ptr(&this->strings[index]));
		this->progmemPrint = true;
		this->previousState = this->state;
		this->state = ProcessorState::Printing;
	}

	void causeDelay(const uint16_t & duration)
	{
		this->timer.setTargetDuration(duration);
		this->timer.start();
		this->previousState = this->state;
		this->state = ProcessorState::Delaying;
	}
};



//
// Definition
//

template< typename SettingsType >
void Processor<SettingsType>::setup()
{
	this->arduboy.begin();

	#if defined(AWAIT_SERIAL)
	while(!Serial);
	#endif

	this->state = ProcessorState::Processing;
	this->previousState = ProcessorState::Processing;
}

template< typename SettingsType >
void Processor<SettingsType>::loop()
{
	if(!this->arduboy.nextFrame()) return;

	this->arduboy.pollButtons();

	this->update();

	this->arduboy.clear();

	this->render();

	this->arduboy.display();
}

template< typename SettingsType >
void Processor<SettingsType>::update()
{
	#if defined(DO_SERIAL)
	Serial.print(F("STATE: "));
	Serial.println(GetStateName(this->state));
	#endif
	
	switch(this->state)
	{
		case ProcessorState::Idle: break;
		case ProcessorState::Terminated: break;
		case ProcessorState::Processing:
		{
			for(uint8_t i = 0; i < 64 && this->state == ProcessorState::Processing; ++i)
			this->updateProcessingState();
			break;
		}
		case ProcessorState::Printing:
		{
			//for(uint8_t i = 0; i < 100 && this->state == ProcessorState::Printing; ++i)
			this->updatePrintingState();
			break;
		}
		case ProcessorState::Waiting: this->updateWaitingState(); break;
		case ProcessorState::Delaying: this->updateDelayingState(); break;
		case ProcessorState::Paused: this->updatePausedState(); break;
		case ProcessorState::Saving: this->updateSavingState(); break;
		case ProcessorState::Choosing: this->updateChoosingState(); break;
	}
}

template< typename SettingsType >
void Processor<SettingsType>::render()
{
	if((this->backgrounds != nullptr) && (this->backgroundIndex != InvalidIndex))
	{
		Sprites::drawOverwrite(0, 0, this->backgrounds, this->backgroundIndex);
	}
	
	for(uint8_t i = 0; i < this->nextImage; ++i)
	{
		const auto & image = this->images[i];
		Sprites::drawOverwrite(image.x, image.y, reinterpret_cast<uint8_t const *>(pgm_read_word(&this->sourceImages[image.index])), image.frame);
	}

	this->textbox.render(this->arduboy, this->arduboy);
	this->choicebox.render(this->arduboy, this->arduboy);
}

template< typename SettingsType >
void Processor<SettingsType>::handleError(const ErrorType & error, const Opcode & opcode)
{
	static_cast<void>(opcode);
	
	switch(error)
	{
		case ErrorType::None: break;
		case ErrorType::InvalidOpcode: break;
		case ErrorType::StackOverflow: break;
		case ErrorType::StackUnderflow: break;
		case ErrorType::IndexOutOfBounds: break;
	}
}

template< typename SettingsType >
void Processor<SettingsType>::updateDelayingState()
{
	if(this->timer.isRunning())
	{
		if(this->timer.hasElapsed())
		{
			this->timer.stop();
			this->state = this->previousState;
		}
		else
		{
			// Try to save power
			Arduboy2Core::idle();
		}
	}
}

template< typename SettingsType >
void Processor<SettingsType>::updatePrintingState()
{
	if(this->atSpace)
	{
		const char * spacePointer = nullptr;
		for(const char * p = this->printChar;; ++p)
		{
			const char c = (this->progmemPrint) ? pgm_read_byte(p) : *p;
			if(c == ' ' || c == '\0')
			{
				spacePointer = p;
				break;
			}
		}
		
		const auto spaceDiff = spacePointer - this->printChar;
		const auto charsRemaining = this->textbox.getColumnCount() - this->textbox.getCursorX();
		
		if(spaceDiff > charsRemaining)
			this->textbox.newLine();
			
		this->atSpace = false;
	}
	else
	{
		const char c = (this->progmemPrint) ? pgm_read_byte(printChar) : *printChar;
		
		if(c == '\0')
		{
			this->atSpace = true;
			this->printChar = nullptr;
			this->state = ProcessorState::Processing;
		}
		else
		{
			this->textbox.write(c);
			++this->printChar;
			
			if(c == ' ')
				this->atSpace = true;
			
			if(FastPrintDelay > 0 || SlowPrintDelay > 0)
			{
				const auto delayPeriod = this->arduboy.pressed(B_BUTTON) ? FastPrintDelay : SlowPrintDelay;
				if(delayPeriod > 16)
					causeDelay(delayPeriod);
				else
					Arduboy2Core::idle();				
			}
		}
	}
}

template< typename SettingsType >
void Processor<SettingsType>::updateWaitingState()
{
	if(this->arduboy.justPressed(A_BUTTON))
		this->state = ProcessorState::Processing;
}

template< typename SettingsType >
void Processor<SettingsType>::updatePausedState()
{

}

template< typename SettingsType >
void Processor<SettingsType>::updateSavingState()
{

}

template< typename SettingsType >
void Processor<SettingsType>::updateChoosingState()
{	
	if(this->arduboy.justPressed(A_BUTTON))
	{
		this->choicebox.hide();
		this->stack.push(this->choicebox.getSelectedIndex());
		this->state = ProcessorState::Processing;
	}
	else if(this->arduboy.justPressed(UP_BUTTON))
	{
		this->choicebox.decreaseSelectedIndex();
	}
	else if(this->arduboy.justPressed(DOWN_BUTTON))
	{
		this->choicebox.increaseSelectedIndex();
	}
}

template< typename SettingsType >
void Processor<SettingsType>::updateProcessingState()
{
	Opcode opcode = this->reader.readOpcode();
	switch(opcode)
	{
		//
		// Infrastructure
		//
		case Opcode::Nop:
		{
			// Does nothing
			break;
		}
		case Opcode::End:
		{
			this->state = ProcessorState::Terminated;
			break;
		}
		case Opcode::Break:
		{
			// To do: implement debugging system
			break;
		}
		case Opcode::JumpR:
		{
			const auto offset = this->reader.readS8();
			this->reader.jumpBy(offset);
			break;
		}
		case Opcode::JumpA:
		{
			const auto address = this->reader.readU16();
			this->reader.jumpTo(address);
			break;
		}
		/*case Opcode::Call:
		{
			break;
		}*/
		/*case Opcode::Return:
		{
			break;
		}*/

		//
		// Stack manipulation
		//
		case Opcode::Push1:
		{
			const auto value = this->reader.readU8();
			this->stack.push(value);
			break;
		}
		case Opcode::Push2:
		{
			const auto value = this->reader.readU16();
			this->stack.push(value);
			break;
		}
		case Opcode::Drop:
		{
			this->stack.drop();
			break;
		}
		case Opcode::DropN:
		{
			const auto amount = this->reader.readU8();
			this->stack.drop(amount);
			break;
		}
		case Opcode::Dupe:
		{
			const auto value = this->stack.peek();
			this->stack.push(value);
			break;
		}
		case Opcode::Swap:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			this->stack.push(value1);
			this->stack.push(value2);
			break;
		}

		//
		// Branching
		//
		case Opcode::BrEqR:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto offset = this->reader.readS8();
			if(value1 == value2)
				this->reader.jumpBy(offset);
			break;
		}
		case Opcode::BrEqA:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto address = this->reader.readU16();
			if(value1 == value2)
				this->reader.jumpTo(address);
			break;
		}
		case Opcode::BrNER:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto offset = this->reader.readS8();
			if(value1 != value2)
				this->reader.jumpBy(offset);
			break;
		}
		case Opcode::BrNEA:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto address = this->reader.readU16();
			if(value1 != value2)
				this->reader.jumpTo(address);
			break;
		}
		case Opcode::BrGTR:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto offset = this->reader.readS8();
			if(value1 > value2)
				this->reader.jumpBy(offset);
			break;
		}
		case Opcode::BrGTA:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto address = this->reader.readU16();
			if(value1 > value2)
				this->reader.jumpTo(address);
			break;
		}
		case Opcode::BrGTER:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto offset = this->reader.readS8();
			if(value1 >= value2)
				this->reader.jumpBy(offset);
			break;
		}
		case Opcode::BrGTEA:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto address = this->reader.readU16();
			if(value1 >= value2)
				this->reader.jumpTo(address);
			break;
		}
		case Opcode::BrLTR:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto offset = this->reader.readS8();
			if(value1 < value2)
				this->reader.jumpBy(offset);
			break;
		}
		case Opcode::BrLTA:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto address = this->reader.readU16();
			if(value1 < value2)
				this->reader.jumpTo(address);
			break;
		}
		case Opcode::BrLTER:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto offset = this->reader.readS8();
			if(value1 <= value2)
				this->reader.jumpBy(offset);
			break;
		}
		case Opcode::BrLTEA:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			const auto address = this->reader.readU16();
			if(value1 <= value2)
				this->reader.jumpTo(address);
			break;
		}

		//
		// Bitwise operations
		//
		case Opcode::And:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			this->stack.push(value1 & value2);
			break;
		}
		case Opcode::AndI:
		{
			const auto value1 = this->stack.peek();
			const auto value2 = this->reader.readU8();
			this->stack.overwrite(value1 & value2);
			break;
		}
		case Opcode::Or:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			this->stack.push(value1 | value2);
			break;
		}
		case Opcode::OrI:
		{
			const auto value1 = this->stack.peek();
			const auto value2 = this->reader.readU8();
			this->stack.overwrite(value1 | value2);
			break;
		}
		case Opcode::ExOr:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			this->stack.push(value1 ^ value2);
			break;
		}
		case Opcode::ExOrI:
		{
			const auto value1 = this->stack.peek();
			const auto value2 = this->reader.readU8();
			this->stack.overwrite(value1 ^ value2);
			break;
		}
		case Opcode::ShL:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			this->stack.push(value1 << value2);
			break;
		}
		case Opcode::ShLI:
		{
			const auto value1 = this->stack.peek();
			const auto value2 = this->reader.readU8();
			this->stack.overwrite(value1 << value2);
			break;
		}
		case Opcode::ShR:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			this->stack.push(value1 >> value2);
			break;
		}
		case Opcode::ShRI:
		{
			const auto value1 = this->stack.peek();
			const auto value2 = this->reader.readU8();
			this->stack.overwrite(value1 >> value2);
			break;
		}
		case Opcode::Not:
		{
			const auto value = this->stack.peek();
			this->stack.overwrite(~value);
			break;
		}

		//
		// Arithmetic operations
		//
		case Opcode::Add:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			this->stack.push(value1 + value2);
			break;
		}
		case Opcode::AddI:
		{
			const auto value1 = this->stack.peek();
			const auto value2 = this->reader.readU8();
			this->stack.overwrite(value1 + value2);
			break;
		}
		case Opcode::Sub:
		{
			const auto value1 = this->stack.pull();
			const auto value2 = this->stack.pull();
			this->stack.push(value1 - value2);
			break;
		}
		case Opcode::SubI:
		{
			const auto value1 = this->stack.peek();
			const auto value2 = this->reader.readU8();
			this->stack.overwrite(value1 - value2);
			break;
		}
		case Opcode::Increment:
		{
			this->stack.overwrite(this->stack.peek() + 1);
			break;
		}
		case Opcode::Decrement:
		{
			this->stack.overwrite(this->stack.peek() - 1);
			break;
		}
		case Opcode::Negate:
		{
			const auto value = this->stack.peek();
			this->stack.overwrite(-value);
			break;
		}

		//
		// Variables
		//
		case Opcode::SetLocal:
		{
			const auto index = this->reader.readU8();
			if(index >= MaxLocals)
			{
				this->handleError(ErrorType::IndexOutOfBounds, opcode);
				return;
			}
			this->stack.push(this->localVariables[index]);
			break;
		}
		case Opcode::GetLocal:
		{
			const auto index = this->reader.readU8();
			if(index >= MaxLocals)
			{
				this->handleError(ErrorType::IndexOutOfBounds, opcode);
				return;
			}
			this->localVariables[index] = this->stack.pull();
			break;
		}
		case Opcode::SetGlobal:
		{
			const auto index = this->reader.readU8();
			if(index >= MaxGlobals)
			{
				this->handleError(ErrorType::IndexOutOfBounds, opcode);
				return;
			}
			this->stack.push(this->globalVariables[index]);
			break;
		}
		case Opcode::GetGlobal:
		{
			const auto index = this->reader.readU8();
			if(index >= MaxGlobals)
			{
				this->handleError(ErrorType::IndexOutOfBounds, opcode);
				return;
			}
			this->globalVariables[index] = this->stack.pull();
			break;
		}
		case Opcode::SaveGlobals:
		{
			// EEPROM.update(addr, val)
			break;
		}

		//
		// Time
		//
		case Opcode::DelayF:
		{
			const auto duration = this->reader.readU8();
			const auto low = static_cast<uint8_t>((duration >> 0) & 0x0F);
			const auto high = static_cast<uint8_t>((duration >> 4) & 0x0F);
			const auto milliseconds = ((low & 1) != 0) ? low * 62 : (low >> 1) * 125;
			const auto seconds = high * 1000;
			
			this->causeDelay(seconds + milliseconds);
			break;
		}
		case Opcode::DelayS:
		{
			const auto duration = this->reader.readU8();
			
			this->causeDelay(duration * 1000);
			break;
		}
		case Opcode::DelayDS:
		{
			const auto duration = this->reader.readU8();
			
			this->causeDelay(duration * 100);
			break;
		}
		case Opcode::DelayCS:
		{
			const auto duration = this->reader.readU8();
			
			this->causeDelay(duration * 10);
			break;
		}
		case Opcode::DelayMS:
		{
			const auto duration = this->reader.readU16();
			
			this->causeDelay(duration);
			break;
		}

		//
		// Buttons
		//
		case Opcode::AwaitInput:
		{
			this->state = ProcessorState::Waiting;
			break;
		}

		//
		// Images
		//
		case Opcode::Background:
		{
			this->backgroundIndex = this->reader.readU8();
			break;
		}
		case Opcode::ClearBackground:
		{
			this->backgroundIndex = InvalidIndex;
			break;
		}
		case Opcode::Foreground:
		{
			if(this->nextImage < MaxImages)
			{
				const auto index = this->reader.readU8();
				const auto frame = this->reader.readU8();
				const auto x = this->reader.readU8();
				const auto y = this->reader.readU8();
				
				this->images[this->nextImage] = Image(index, frame, x, y);
				++this->nextImage;
			}
			break;
		}
		case Opcode::ClearForeground:
		{
			this->nextImage = 0;
			break;
		}

		//
		// Music
		//
		case Opcode::PlayMusic:
		{
			this->trackIndex = this->reader.readU8();
			break;
		}
		case Opcode::StopMusic:
		{
			break;
		}

		//
		// Text
		//
		case Opcode::ShowTextBox:
		{
			this->textbox.show();
			break;
		}
		case Opcode::HideTextBox:
		{
			this->textbox.hide();
			break;
		}
		
		case Opcode::ClearTextBox:
		{
			this->textbox.clear();
			break;
		}
		case Opcode::ClearLine:
		{
			this->textbox.clearLine();
			break;
		}
		
		case Opcode::Scroll:
		{
			this->textbox.scroll();
			break;
		}
		case Opcode::NewLine:
		{
			this->textbox.newLine();
			break;
		}
		case Opcode::BlankLine:
		{
			this->textbox.ensureBlankLine();
			break;
		}
		
		case Opcode::PrintString:
		{
			const auto index = this->reader.readU8();
			
			this->printIndexedString(index);
			break;
		}
		case Opcode::PrintTop:
		{
			const auto value = this->stack.peek();
			
			itoa(value, &this->formatBuffer[0], 10);
			this->printChar = &this->formatBuffer[0];
			this->progmemPrint = false;
			this->state = ProcessorState::Printing;
			break;
		}
		
		case Opcode::BlankLinePrint:
		{
			const auto index = this->reader.readU8();
			
			this->textbox.ensureBlankLine();
			this->printIndexedString(index);
			break;
		}
		case Opcode::PrintNewLine:
		{
			const auto index = this->reader.readU8();
			
			this->printIndexedString(index);
			this->textbox.newLine();
			break;
		}

		//
		// Choice
		//
		case Opcode::ShowChoiceBox:
		{
			this->choicebox.show();
			this->state = ProcessorState::Choosing;
			break;
		}
		case Opcode::HideChoiceBox:
		{
			this->choicebox.hide();
			break;
		}		
		case Opcode::ClearChoiceBox:
		{
			this->choicebox.clear();
			break;
		}		
		case Opcode::AddChoice:
		{
			const auto index = this->reader.readU8();
			this->choicebox.add(AsFlashString(pgm_read_word(&this->strings[index])));
			break;
		}
		
		//default:
	}

	#if defined(DO_SERIAL)
	Serial.print(F("OP: "));
	Serial.println(GetOpcodeName(opcode));
	#endif
}