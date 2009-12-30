/**
 *  @file Sleep.cpp
 *
 *  @date 30-dec-2009
 *  @author Ives van der Flaas
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
