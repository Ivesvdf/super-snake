/**
 *  @file Game.cpp
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

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Timer.h"
#include "Sleep.h"


Game::Game():
	mainwnd(initscr()),
	boardWidth(78),
	boardHeight(22),
	maxBonusses(3),
	bonusses(0)

{

	array = new vector< vector<Cell> > (boardHeight, vector<Cell>(boardWidth, EMPTY));

	noecho();
	cbreak();
	nodelay(mainwnd, TRUE);
	keypad(mainwnd, TRUE);
	refresh();
	wrefresh(mainwnd);

	srand(time(0));

	// 1 character left, right, up and down is required to delimit the playing field
	screen = newwin(boardHeight+2, boardWidth+2, 0, 0);
	box(screen, ACS_VLINE, ACS_HLINE);
	nodelay(screen, TRUE);

	// enable arrow keys
	keypad(screen, TRUE);

	// hide cursor
	curs_set(0);



}

Game::~Game()
{
	delete array;
	endwin();
}

void Game::setCell(Position pos, Cell what)
{
	(*array)[pos.y()][pos.x()] = what;

	drawRel(pos,what);
}

Cell Game::getCell(Position pos) const
{
	return (*array)[pos.y()][pos.x()];
}
void Game::drawRel(Position pos, Cell what)
{
	char toPrint = ' ';
	switch(what)
	{
	case EMPTY:
		toPrint = ' ';
		break;
	case HEAD:
		toPrint = '@';
		break;
	case BONUS:
		toPrint = 'B';
		break;
	case LEFT:
	case RIGHT:
	case UP:
	case DOWN:
		toPrint = '#';
		break;
	}

	// Build temporary string from char
	char tmp[2];
	tmp[0] = toPrint;
	tmp[1] = 0;

	mvwprintw(screen, pos.y()+1, pos.x()+1, tmp);
}
void Game::play()
{

	Position startPos(10,10);

	Position head = startPos;
	Position tail = Position(startPos.x()-1, startPos.y());

	setCell(head, HEAD);
	setCell(tail, RIGHT);

	Cell direction = RIGHT;

	Timer timer;

	length = 3;

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
		setCell(head, direction);
		head.move(direction);

		//Test if head is out of bounds
		if(head.x() < 0 || head.x() >= boardWidth || head.y() < 0 || head.y() >= boardHeight)
		{
			return;
		}

		// Move head
		Cell nextPos = getCell(head);
		setCell(head, HEAD);

		// move tail if addLength == 0
		if(addLength == 0)
		{
			Cell dir = getCell(tail);

			setCell(tail, EMPTY);

			tail.move(dir);
		}
		else
		{
			addLength--;
			length++;
		}

		// if we hit a wall, quit game!
		if(nextPos != EMPTY)
		{
			if(nextPos == BONUS)
			{
				addLength = length / 2;
				bonusses--;
			}
			else
				return;
		}


		double pauzeTime = 0;

		// Since characters are higher than they are wide, if we would pauze the same amount
		// of time in both directions, the snake would go up and down incredibly fast en left to
		// right incredibly slow.
		if((direction == LEFT) || (direction == RIGHT))
			pauzeTime = 0.1;
		else
			pauzeTime = 0.16;

		while(timer.poll() < pauzeTime)
		{
			sleepSec(pauzeTime-timer.poll());
		}

		// Only put a new bonus on the screen if there are < max bonusses on screen already
		if(bonusses < maxBonusses)
		{
			// If we're lucky, place new bonus
			if(rand()% static_cast<int>(5.0/timer.poll()) == 0)
			{
				// Place bonus
				int x,y;
				do
				{
					x = rand()%boardWidth;
					y = rand()%boardHeight;
				}
				while(getCell(Position(x,y)) != EMPTY);

				setCell(Position(x,y), BONUS);
				bonusses++;
			}
		}

		timer.reset();
		wrefresh(screen);
		refresh();
   }
}
