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

struct DefaultTextBoxSettings
{
	constexpr static uint8_t const RowCount = 2;
	constexpr static uint8_t const ColumnCount = 21;
	
	constexpr static uint8_t const CursorXOffset = 3;
	constexpr static uint8_t const CursorYOffset = 2;
	constexpr static uint8_t const LineHeight = 8;
	
	constexpr static uint8_t const X = 1;
	constexpr static uint8_t const Width = 128 - (X * 2);
	constexpr static uint8_t const Height = 20;
	constexpr static uint8_t const Y = 64 - Height;
	
	using Renderer = Arduboy2;
	using Printer = Arduboy2;
};

struct DefaultChoiceBoxSettings
{	
	constexpr static uint8_t const ChoiceCapacity = 4;
	constexpr static uint8_t const LineHeight = 8;
	
	constexpr static uint8_t const X = 15;
	constexpr static uint8_t const Y = 15;
	constexpr static uint8_t const Width = 128 - (X * 2);
	
	constexpr static uint8_t const MarginX = 2;
	constexpr static uint8_t const MarginY = 2;
	constexpr static uint8_t const ChoiceMarginX = 2;
	constexpr static uint8_t const ChoiceMarginY = 2;
	
	constexpr static uint8_t const CursorXOffset = MarginX + ChoiceMarginX;
	constexpr static uint8_t const CursorYOffset = MarginY + ChoiceMarginY;
	
	constexpr static uint8_t const ChoiceWidth = Width - (MarginX * 2);
	constexpr static uint8_t const ChoiceHeight = LineHeight + (ChoiceMarginY * 2);
	
	using Renderer = Arduboy2;
	using Printer = Arduboy2;
};

struct DefaultProcessorSettings
{
	constexpr static uint8_t const StackSize = 64;
	constexpr static uint8_t const MaxGlobals = 32;
	constexpr static uint8_t const MaxLocals = 32;
	constexpr static uint8_t const MaxImages = 16;
	constexpr static uint16_t const FastPrintDelay = 0;
	constexpr static uint16_t const SlowPrintDelay = 100;
	
	using TextBoxSettings = DefaultTextBoxSettings;
	using ChoiceBoxSettings = DefaultChoiceBoxSettings;
};

#include "Processor.h"

using DefaultProcessor = Processor<DefaultProcessorSettings>;