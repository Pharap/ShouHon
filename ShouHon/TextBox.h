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

//
// Declaration
//

template< typename SettingsType >
class TextBox : public Print
{
public:
	using Settings = SettingsType;
	using Renderer = typename SettingsType::Renderer;
	using Printer = typename SettingsType::Printer;
	
	constexpr static uint8_t const RowCount = Settings::RowCount;
	constexpr static uint8_t const ColumnCount = Settings::ColumnCount;
	constexpr static uint8_t const RowEnd = RowCount - 1;
	constexpr static uint8_t const ColumnEnd = ColumnCount - 1;
	constexpr static const uint8_t X = Settings::X;
	constexpr static const uint8_t Y = Settings::Y;
	constexpr static const uint8_t Width = Settings::Width;
	constexpr static const uint8_t Height = Settings::Height;
	constexpr static const uint8_t CursorXOffset = Settings::CursorXOffset;
	constexpr static const uint8_t CursorYOffset = Settings::CursorYOffset;
	constexpr static const uint8_t LineHeight = Settings::LineHeight;

private:
	char text[RowCount][ColumnCount] = {};
	
	uint8_t cursorX = 0;
	uint8_t cursorY = 0;
	
	bool visible = false;
	
public:
	uint8_t getColumnCount(void) const;
	
	uint8_t getRowCount(void) const;

	uint8_t getCursorX(void) const;
	
	uint8_t getCursorY(void) const;

	bool isVisible(void) const;
	
	void show(void);
	
	void hide(void);

	void resetCursor(void);
	
	void clear(void);
	
	void clearLine(void);
	
	void ensureBlankLine(void);
	
	void scroll(void);
	
	void newLine(void);
	
	size_t write(uint8_t c) override;
	
	void render(Renderer & renderer, Printer & printer);
	
private:
	char * getRow(const uint8_t & row);	
	char const* getRow(const uint8_t & row) const;
};

//
// Definition
//

template< typename SettingsType >
char * TextBox<SettingsType>::getRow(const uint8_t & row)
{
	return static_cast<char *>(&(text[row][0]));
}

template< typename SettingsType >
char const * TextBox<SettingsType>::getRow(const uint8_t & row) const
{
	return static_cast<char const *>(&(text[row][0]));
}

template< typename SettingsType >
uint8_t TextBox<SettingsType>::getColumnCount(void) const
{
	return ColumnEnd;
}

template< typename SettingsType >
uint8_t TextBox<SettingsType>::getRowCount(void) const
{
	return RowEnd;
}

template< typename SettingsType >
uint8_t TextBox<SettingsType>::getCursorX(void) const
{
	return this->cursorX;
}

template< typename SettingsType >
uint8_t TextBox<SettingsType>::getCursorY(void) const
{
	return this->cursorY;
}

template< typename SettingsType >
bool TextBox<SettingsType>::isVisible(void) const
{
	return this->visible;
}

template< typename SettingsType >
void TextBox<SettingsType>::show(void)
{
	this->visible = true;
}

template< typename SettingsType >
void TextBox<SettingsType>::hide(void)
{
	this->visible = false;
}

template< typename SettingsType >
void TextBox<SettingsType>::resetCursor(void)
{
	this->cursorY = 0;
	this->cursorX = 0;
}

template< typename SettingsType >
void TextBox<SettingsType>::clear(void)
{
	this->resetCursor();
	for(uint8_t i = 0; i < RowCount; ++i)
		memset(getRow(i), '\0', ColumnCount);
}

template< typename SettingsType >
void TextBox<SettingsType>::clearLine(void)
{
	this->cursorX = 0;
	memset(getRow(this->cursorY), '\0', ColumnCount);
}

template< typename SettingsType >
void TextBox<SettingsType>::ensureBlankLine(void)
{
	if(this->cursorX != 0)
		this->newLine();
}

template< typename SettingsType >
void TextBox<SettingsType>::scroll(void)
{
	for(uint8_t i = 0, j = 1; j < RowCount; ++i, ++j)
		memcpy(getRow(i), getRow(j), ColumnCount);
	memset(getRow(RowEnd), '\0', ColumnCount);
}

template< typename SettingsType >
void TextBox<SettingsType>::newLine(void)
{
	this->text[this->cursorY][this->cursorX] = '\0';
	this->cursorX = 0;
	if(this->cursorY < RowEnd)
		++this->cursorY;
	else
		this->scroll();
}

template< typename SettingsType >
size_t TextBox<SettingsType>::write(uint8_t c)
{
	if(c == '\n')
	{
		this->newLine();
	}	
	else if(cursorX < ColumnEnd)
	{	
		this->text[this->cursorY][this->cursorX] = c;
		++this->cursorX;
	}
	else if(cursorX == ColumnEnd)
	{	
		this->newLine();
		this->write(c);
	}
	return 1;
}

template< typename SettingsType >
void TextBox<SettingsType>::render(Renderer & renderer, Printer & printer)
{
	if(this->visible)
	{
		renderer.fillRect(X, Y, Width, Height, BLACK);
		renderer.drawRect(X, Y, Width, Height, WHITE);

		for(uint8_t y = 0; y < RowCount; ++y)
		{
			printer.setCursor(X + CursorXOffset, (Y + CursorYOffset) + (LineHeight * y));
			printer.println(getRow(y));
		}
	}
}