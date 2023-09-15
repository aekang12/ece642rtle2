/* 
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME: Ann Kang
 * ANDREW ID: annkang
 * LAST UPDATE:
 *
 * This file is an algorithm to solve the ece642rtle maze
 * using the left-hand rule. The code is intentionaly left obfuscated.
 *
 */

#include "student.h"
#include <unistd.h>

// Ignore this line until project 5
turtleMove studentTurtleStep(bool bumped) {return MOVE;}

// OK TO MODIFY BELOW THIS LINE
		 
// this procedure takes the current turtle position and orientation and returns
// true=submit changes, false=do not submit changes
// Ground rule -- you are only allowed to call the helper functions "bumped(..)" and "atend(..)",
// and NO other turtle methods or maze methods (no peeking at the maze!)
bool studentMoveTurtle(QPointF& pos_, int& dir) {
    if (atend(pos_.x(), pos_.y())) {
	return false;
    }

    sleep(1);
    
    // vectors used for wall checking, indexed by turtle direction: 
    // {0, 1, 2, 3}, or {W, N, E, S}
    uint8_t wall_coords[4][4] = {{0,0,0,1}, {0,0,1,0}, {1,0,1,1}, {0,1,1,1}};
    enum Directions {W, N, E, S};
    enum Moves {Right, Left, Straight};
    static Moves move;

    if (move == Straight) {
	// add 3 to deal with mod of -1, turn left
	dir = (dir + 3) % 4;
	move = Left;
	return true;
    }
 
    // check if there is a wall in front of the turtle
    bool wall = bumped(pos_.x() + wall_coords[dir][0], \
    pos_.y() + wall_coords[dir][1], \
    pos_.x() + wall_coords[dir][2],pos_.y() + wall_coords[dir][3]);

    if (wall) {
	// turn right
	dir = (dir + 1) % 4; 
	move = Right;
	return true;
    }

    Directions dir_enum = (Directions) dir; 
    move = Straight;
    switch (dir_enum) {
	case N:
	    pos_.setY(pos_.y()-1);
	    break;
	case E:
	    pos_.setX(pos_.x()+1);
	    break;
	case S:
	    pos_.setY(pos_.y()+1);
	    break;
	case W:
	    pos_.setX(pos_.x()-1);
	    break;
	default:
	    ROS_ERROR("Invalid direction!"); 
    }
    
    ROS_INFO("Orientation=%i", dir);
    return true;
}
