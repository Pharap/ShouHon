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

template< uint8_t Size >
class Stack
{
public:
	constexpr const static uint8_t Capacity = Size;

private:
	uint16_t stack[Capacity];
	uint8_t next;

public:
	
	uint8_t getCount(void) const
	{
		return this->next;
	}
	
	bool isEmpty(void) const
	{
		return (this->next == 0);
	}
	
	bool isFull(void) const
	{
		return (this->next == Capacity);
	}
	
	void overwrite(uint16_t value)
	{
		if(this->isEmpty())
			return;
		
		this->stack[this->next - 1] = value;
	}
	
	bool tryOverwrite(uint16_t value)
	{
		if(this->isEmpty())
			return false;
		
		this->stack[this->next - 1] = value;
		
		return true;
	
	}
	
	uint16_t peek(void) const
	{
		return this->stack[this->next - 1];
	}
	
	bool tryPeek(uint16_t & result) const
	{
		result = this->stack[this->next - 1];
		
		return true;
	}
	
	void push(const uint16_t & value)
	{
		if(this->isFull())
			return;
	
		this->stack[this->next] = value;
		++this->next;
	}
	
	bool tryPush(const uint16_t & value)
	{
		if(this->isFull())
			return false;
	
		this->stack[this->next] = value;
		++this->next;
		
		return true;
	}
	
	uint16_t pull(void)
	{
		if(this->isEmpty())
			return 0;
			
		--this->next;
		return this->stack[this->next];
	}
	
	bool tryPull(uint16_t & result)
	{
		if(this->isEmpty())
			return false;
			
		--this->next;
		result = this->stack[this->next];
		
		return true;
	}
	
	void drop(void)
	{
		if(this->isEmpty())
			return;
			
		--this->next;
	}
	
	void drop(uint8_t amount)
	{
		if(this->next > amount)
			return;
			
		this->next -= amount;
	}
	
	bool tryDrop(void)
	{
		if(this->isEmpty())
			return false;
			
		--this->next;
		
		return true;
	}

};