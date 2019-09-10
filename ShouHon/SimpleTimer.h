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

class SimpleTimer
{
public:
	using TimeType = decltype(millis());
	using DurationType = decltype(TimeType(0) - TimeType(0));

private:
	bool running = false;
	TimeType previousTime = ~0;
	DurationType targetDuration = ~0;
	
public:	
	DurationType getTargetDuration(void) const
	{
		return this->targetDuration;
	}
	
	void setTargetDuration(DurationType targetDuration)
	{
		this->targetDuration = targetDuration;
	}
	
	bool isRunning() const
	{
		return this->running;
	}
	
	bool hasElapsed() const
	{
		if(!this->running)
			return true;
			
		const auto now = millis();
		const auto duration = now - this->previousTime;
		return duration >= this->targetDuration;
	}
	
	void start(void)
	{
		this->previousTime = millis();
		this->running = true;
	}
	
	void stop(void)
	{
		this->running = false;
	}
};