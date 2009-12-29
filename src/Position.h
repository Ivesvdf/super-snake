/**
 *  @file Position.h
 *
 *  @date 29-dec-2009
 *  @author Ives van der Flaas
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
