#include <curses.h>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#ifdef __unix__
#include <unistd.h>
#include <sys/time.h>



#endif


using std::vector;

int current_getch;
static WINDOW *mainwnd;
static WINDOW *screen;
WINDOW *my_win;

enum Cell { UP, DOWN, LEFT, RIGHT, HEAD, EMPTY, WALL, BONUS};

#ifdef __unix__
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



class Position
{
public:
	Position(int ix, int iy): fx(ix), fy(iy) {}

	/**
	 * Will move current coordinates in the direction
	 * in c.
	 * @param c Either UP, DOWN, LEFT or RIGHT
	 */
	void move(Cell c)
	{
		switch(c)
		{
		case UP:
			fy--;
			break;
		case DOWN:
			fy++;
			break;
		case LEFT:
			fx--;
			break;
		case RIGHT:
			fx++;
			break;
		}
	}

	int x() const { return fx; }
	int y() const { return fy; }
private:
	int fx,fy;
};


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

int main()
{
	srand(time(0));

	mainwnd = initscr();
	noecho();
	cbreak();
	nodelay(mainwnd, TRUE);
	keypad(mainwnd, TRUE);
	refresh();
	wrefresh(mainwnd);

	const int boardWidth = 79;
	const int boardHeight = 23;


	vector< vector<Cell> > array(boardHeight, vector<Cell>(boardWidth, EMPTY));


	Position startPos(10,10);

	Position head = startPos;
	Position tail = Position(startPos.x()-1, startPos.y());

	array[head.y()][head.x()] = HEAD;
	array[tail.y()][tail.x()] = RIGHT;

	screen = newwin(boardHeight+1, boardWidth+1, 0, 0);
	box(screen, ACS_VLINE, ACS_HLINE);
	nodelay(screen, TRUE);
	keypad(screen, TRUE);

	Cell direction = RIGHT;

	Timer timer;

	int addLength = 0;

	while (true)
	{
		int input = getch();

		// Direction we'll be using
		switch(input)
		{
		case KEY_LEFT:
			direction = LEFT;
			break;
		case KEY_RIGHT:
			direction = RIGHT;
			break;
		case KEY_UP:
			direction = UP;
			break;
		case KEY_DOWN:
			direction = DOWN;
			break;
		}


		// move head
		array[head.y()][head.x()] = direction;
		head.move(direction);

		//Test if head is out of bounds
		if(head.x() < 0 || head.x() >= boardWidth || head.y() < 0 || head.y() >= boardHeight)
		{
			return 1;
		}
		Cell nextPos = array[head.y()][head.x()];
		mvwprintw(screen, head.y(),head.x(), "X");
		array[head.y()][head.x()] = HEAD;

		// move tail if addLength != 0
		if(addLength != 0)
		{
			Cell dir = array[tail.y()][tail.x()];
			array[tail.y()][tail.x()] = EMPTY;
			mvwprintw(screen, tail.y(),tail.x(), " ");
			tail.move(dir);
		}
		else
		{
			addLength--;
		}

		// if we hit a wall, quit game!
		if(nextPos != EMPTY)
		{
			if(nextPos == BONUS)
				addLength++;
			else
				return 1;
		}



		while(timer.poll() < 0.1)
		{
			sleep(0.1-timer.poll());
		}

		if(rand()% static_cast<int>(5.0/timer.poll()) == 0)
		{
			// Place bonus
			int x,y;
			do
			{
				x = rand()%boardWidth;
				y = rand()%boardHeight;
			}
			while(array[y][x] != EMPTY);

			array[y][x] = BONUS;
			mvwprintw(screen, y, x, "B");


		}

		timer.reset();
		curs_set(0);
		wrefresh(screen);
		refresh();
   }
	endwin();
	return 0;
}


/*
int main()
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();

	WINDOW* win = newwin(20,20,20,20);
	box(win,ACS_VLINE, ACS_HLINE);
	wrefresh(win);
	refresh();

	while(true)
	{

		int input = getch();

		switch(input)
		{
		case KEY_LEFT:
			printw("Pressing left");
			break;
		case KEY_RIGHT:
			printw("Pressing right");
			break;
		case KEY_UP:
			printw("Pressing up");
			break;
		case KEY_DOWN:
			printw("Pressing down");
			break;
		}
	}

	endwin();


	return 0;
}*/
