/**
 *  @file Game.h
 *
 *  @date 29-dec-2009
 *  @author Ives van der Flaas
 */

#ifndef GAME_H_
#define GAME_H_

#include <curses.h>
#include <vector>
#include "Position.h"
#include "Cell.h"

using std::vector;

class Game
{
public:
	Game();
	virtual ~Game();

	void play();
	void drawRel(Position pos, Cell what);
	void setCell(Position pos, Cell what);
	Cell getCell(Position pos) const;

private:
	WINDOW *mainwnd;
	WINDOW *screen;

	const int boardWidth;
	const int boardHeight;

	const int maxBonusses;
	int bonusses;

	vector< vector<Cell> > *array;
};

#endif /* GAME_H_ */
