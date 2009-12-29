#ifdef __unix__
#include <unistd.h>
#include <sys/time.h>
#endif

#include "Game.h"

using std::vector;

int main()
{

	Game g;
	g.play();

	return 0;
}


