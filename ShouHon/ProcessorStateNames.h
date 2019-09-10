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

#include "FlashUtils.h"
#include "ProcessorState.h"

FlashString GetStateName(ProcessorState processorState)
{
	switch(processorState)
	{
		case ProcessorState::Idle:
			return F("IDLE");
		case ProcessorState::Terminated:
			return F("TERMINATED");
		case ProcessorState::Processing:
			return F("PROCESSING");
		case ProcessorState::Printing:
			return F("PRINTING");
		case ProcessorState::Waiting:
			return F("WAITING");
		case ProcessorState::Delaying:
			return F("DELAYING");
		case ProcessorState::Paused:
			return F("PAUSED");
		case ProcessorState::Saving:
			return F("SAVING");
		case ProcessorState::Choosing:
			return F("CHOOSING");
		default:
			return F("INVALID");
	}
}