/**
 *  @file Timer.h
 *
 *  @date 29-dec-2009
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

#ifndef TIMER_H_
#define TIMER_H_

#include <ctime>


#ifdef __unix__
#include <unistd.h>
#include <sys/time.h>

class Timer
{
public:
	Timer(): last(new timeval), cur(new timeval){ gettimeofday(last, 0);}
	~Timer(){ delete cur; delete last; }

	double poll() const
	{
		gettimeofday(cur, 0);
		return cur->tv_sec-last->tv_sec + (cur->tv_usec - last->tv_usec)/1000000.0;
	}

	double reset()
	{
		double time = poll();
		*last = *cur;
		return time;
	}

private:
    timeval *last;
    timeval *cur;

};
#endif

#endif /* TIMER_H_ */
