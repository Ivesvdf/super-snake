/**
 *  @file Sleep.cpp
 *
 *  @date 30-dec-2009
 *  @author Ives van der Flaas
 *
 *   Copyright 2009 Ives van der Flaas
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *   Unless required by applicable law or agreed to in writing, software distributed
 *   under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 *   CONDITIONS OF ANY KIND, either express or implied. See the License for the specific
 *   language governing permissions and limitations under the License.
 */

#ifdef __unix__
#include <ctime>
	void sleepSec(double seconds)
	{
		timespec t;
		t.tv_nsec = static_cast<long>(seconds * 1000000000);
		t.tv_sec = 0;
		nanosleep(&t, 0);
	}

#else
#error

#endif