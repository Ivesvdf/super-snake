/**
 *  @file Sleep.h
 *
 *  @date 29-dec-2009
 *  @author Ives van der Flaas
 */

#ifndef SLEEP_H_
#define SLEEP_H_

#ifdef __unix__
	void sleep(double seconds)
	{
		timespec t;
		t.tv_nsec = static_cast<long>(seconds * 1000000000);
		t.tv_sec = 0;
		nanosleep(&t, 0);
	}
#else
#error

#endif

#endif /* SLEEP_H_ */
