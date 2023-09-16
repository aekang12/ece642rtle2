/* 
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME:
 * ANDREW ID:
 * LAST UPDATE:
 *
 * This file keeps track of where the turtle is in the maze
 * and updates the location when the turtle is moved. It shall not
 * contain the maze solving logic/algorithm.
 *
 * This file is used along with student_turtle.cpp. student_turtle.cpp shall
 * contain the maze solving logic/algorithm and shall not make use of the
 * absolute coordinates or orientation of the turtle.
 *
 * This file shall call studentTurtleStep(..) in student_turtle.cpp to determine
 * the next move the turtle will make, and shall use translatePos(..) and
 * translateOrnt(..) to translate this move into absolute coordinates
 * to display the turtle.
 *
 */

#include "student.h"

// this funtion takes in turtle position pos_ and 
// turtle direction dir and returns true if there is a wall 
// in front of the turtle and false otherwise
bool check_wall(QPointF& pos_, int& direction) {
    // wall_coords contains vectors to help check if 
    // there is a wall directly in front of the turtle 
    // Each vector has 4 elements:
	// {update to x1, update to y1, update to x2, update to y2}
	// the updates are either 1 or 0 since walls have length 1
    // There are 4 vectors total, indexed as follows: 
        // {vector for if turtle is facing West, 
	// vector for if turtle is facing North, 
	// vector for if turtle is facing East, 
	// vector for if turtle is facing South}
    uint8_t wall_coords[num_dirs][num_coords] = {{0,0,0,1}, {0,0,1,0},\
						{1,0,1,1}, {0,1,1,1}};
    // add appropriate wall coordinates to the turtle's position to 
    // get the endpoints of the wall direclty in front of the turtle
    bool wall_exists = bumped(pos_.x() + wall_coords[direction][0], \
    		       pos_.y() + wall_coords[direction][1], \
    		       pos_.x() + wall_coords[direction][2], \
		       pos_.y() + wall_coords[direction][3]);
}

/*
 * This procedure calls displayVisits to update the number of visits to 
 * the current maze cell
 */
void mazeVisits(uint8_t num_visits) {
    displayVisits(num_visits);
}

/*
 * This procedure takes the current turtle position and orientation and returns true=accept changes, false=do not accept changes
 * This file interfaces with functions in student_turtle.cpp
 */
bool moveTurtle(QPointF& pos_, int& direction)
{
    if (atend(pos_.x(), pos_.y())) {
	return false;
    }
    bool bumped = check_wall(pos_, direction);
    Moves nextMove = studentTurtleStep(bumped, direction); 
    pos_ = translatePos(pos_, direction, nextMove);
    direction = translateOrnt(direction, nextMove);
    return true;
}

/*
 * Takes a position and a Move and returns a new position
 * based on the move 
*/
QPointF translatePos(QPointF pos_, int direction, Moves nextMove) {
    if (nextMove != Straight) {
	return pos_;
    }

    switch ((Directions)direction) {
	case North:
	    pos_.setY(pos_.y()-1);
	    break;
	case East:
	    pos_.setX(pos_.x()+1);
	    break;
	case South:
	    pos_.setY(pos_.y()+1);
	    break;
	case West:
	    pos_.setX(pos_.x()-1);
	    break;
	default:
	    ROS_ERROR("Invalid direction!"); 
    }
    return pos_;
}

/*
 * Takes an orientation and a turtleMove and returns a new orienation
 * based on the move
 */
int translateOrnt(int orientation, Moves nextMove) {
    switch(nextMove) {
	case Straight:
	    break;
	case Left:
	    orientation = (orientation + (num_dirs-1)) % num_dirs;
	    break;
	case Right:
	    orientation = (orientation + 1) % num_dirs;
	    break;
	default:
	    ROS_ERROR("Invalid direction!");
    }
    return orientation;
}
