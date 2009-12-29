/**
 *  @file Timer.h
 *
 *  @date 29-dec-2009
 *  @author Ives van der Flaas
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
