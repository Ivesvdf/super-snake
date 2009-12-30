/**
 *  @file Position.h
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

#ifndef POSITION_H_
#define POSITION_H_

#include "Cell.h"

#undef move

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

#endif /* POSITION_H_ */
