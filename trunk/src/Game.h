/**
 *  @file Game.h
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

	int length;

	vector< vector<Cell> > *array;
};

#endif /* GAME_H_ */
