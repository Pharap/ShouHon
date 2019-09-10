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
#include "FlashString.h"

template< typename SettingsType >
class ChoiceBox
{
public:
	using Settings = SettingsType;
	using Renderer = typename Settings::Renderer;
	using Printer = typename Settings::Printer;

	constexpr static uint8_t const ChoiceCapacity = Settings::ChoiceCapacity;
	constexpr static uint8_t const X = Settings::X;
	constexpr static uint8_t const Y = Settings::Y;
	constexpr static uint8_t const Width = Settings::Width;
	//constexpr static uint8_t const Height = Settings::Height;
	constexpr static uint8_t const CursorXOffset = Settings::CursorXOffset;
	constexpr static uint8_t const CursorYOffset = Settings::CursorYOffset;
	constexpr static uint8_t const LineHeight = Settings::LineHeight;
	
	constexpr static uint8_t const MarginX = Settings::MarginX;
	constexpr static uint8_t const MarginY = Settings::MarginY;
	constexpr static uint8_t const ChoiceMarginX = Settings::ChoiceMarginX;
	constexpr static uint8_t const ChoiceMarginY = Settings::ChoiceMarginY;
	
	constexpr static uint8_t const ChoiceWidth = Settings::ChoiceWidth;
	constexpr static uint8_t const ChoiceHeight = Settings::ChoiceHeight;

private:
	FlashString choices[ChoiceCapacity];
	uint8_t nextChoice = 0;
	uint8_t selectedIndex = 0;
	
	bool visible = false;

public:
	bool isEmpty(void) const
	{
		return this->nextChoice == 0;
	}
	
	bool isFull(void) const
	{
		return this->nextChoice >= ChoiceCapacity;
	}
	
	uint8_t getChoiceCount(void) const
	{
		return this->nextChoice;
	}
	
	uint8_t getSelectedIndex(void) const
	{
		return this->selectedIndex;
	}
	
	void setSelectedIndex(uint8_t index)
	{
		this->selectedIndex = index;
	}
	
	void increaseSelectedIndex(void)
	{
		if(this->selectedIndex < getChoiceCount() - 1)
			++this->selectedIndex;
	}
	
	void decreaseSelectedIndex(void)
	{
		if(this->selectedIndex > 0)
			--this->selectedIndex;
	}

	bool isVisible(void) const
	{
		return this->visible;
	}
	
	void show(void)
	{
		this->visible = true;
	}
	
	void hide(void)
	{
		this->visible = false;
	}

	bool add(FlashString choice)
	{
		if(this->nextChoice < ChoiceCapacity)
		{
			this->choices[this->nextChoice] = choice;
			++this->nextChoice;
			return true;
		}
		return false;
	}
	
	void clear(void)
	{
		this->nextChoice = 0;
	}
	
	void render(Renderer & renderer, Printer & printer)
	{
		if(this->visible)
		{
			uint8_t const Height = (ChoiceHeight * this->getChoiceCount()) + (ChoiceMarginY * 2);
			
			renderer.fillRect(X, Y, Width, Height, BLACK);
			renderer.drawRect(X, Y, Width, Height, WHITE);

			for(uint8_t i = 0; i < this->getChoiceCount(); ++i)
			{
				uint8_t const x = X + CursorXOffset;
				uint8_t const y = (Y + CursorYOffset) + (ChoiceHeight * i);
				
				printer.setCursor(x, y);
				printer.print(this->choices[i]);
				
				if(i == this->selectedIndex)
					renderer.drawRect(x - ChoiceMarginX, y - ChoiceMarginY, ChoiceWidth, ChoiceHeight);
			}
		}
	}
};