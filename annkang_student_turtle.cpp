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
enum Directions {West, North, East, South};
enum Moves {Right, Left, Straight};
// tracker is a 24 by 24 array that helps maze track how many times 
// each cell has been visited. trackerx and trackery keep track of turtle 
// position, initialized to the center of array
struct tracker{
    uint8_t array[23][23] = {};
    uint8_t x = 11; 
    uint8_t y = 11; 
    
    // constructor for initialization 
    tracker() {
	array[11][11] = 1; 
    }
} turtle_tracker;

// this funtion takes in turtle position pos_ and 
// turtle direction dir and returns true if there is a wall 
// in front of the turtle and false otherwise
bool check_wall(QPointF& pos_, int& direction) {
    const uint8_t num_dirs = 4; 
    const uint8_t num_coords = 4;
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

// this function takes in turtle position and direction, and saves 
// changes such that the turtle moves straight 1 unit forward 
void move_straight(QPointF& pos_, int& direction) {
    switch ((Directions)direction) {
	case North:
	    pos_.setY(pos_.y()-1);
	    turtle_tracker.y += 1; 
	    break;
	case East:
	    pos_.setX(pos_.x()+1);
	    turtle_tracker.x += 1;
	    break;
	case South:
	    pos_.setY(pos_.y()+1);
	    turtle_tracker.y -= 1; 
	    break;
	case West:
	    pos_.setX(pos_.x()-1);
	    turtle_tracker.x -= 1; 
	    break;
	default:
	    ROS_ERROR("Invalid direction!"); 
    }
    turtle_tracker.array[turtle_tracker.x][turtle_tracker.y] += 1;
    return; 
}
		 
// this procedure takes the current turtle position and orientation and returns
// true=submit changes, false=do not submit changes
bool studentMoveTurtle(QPointF& pos_, int& direction) {
    static Moves move;
    const uint8_t num_dirs = 4; 
    const uint8_t num_coords = 4;
    
    // if turtle is at end, return false
    if (atend(pos_.x(), pos_.y())) {
	return false;
    }

    // sleep for 1 second, changing sleep duration changes turtle speed
    sleep(0.1); 

    if (move == Straight) {
	// Turn left by decrementing direction by 1
	direction = (direction + (num_dirs-1)) % num_dirs;
	move = Left;
    } else if (check_wall(pos_, direction)) {
	// turn right by incrementing direction by 1
	direction = (direction + 1) % num_dirs; 
	move = Right;
    } else {
	move = Straight;
	move_straight(pos_, direction); 
    }
    
    ROS_INFO("Orientation=%i", direction);
    displayVisits(turtle_tracker.array[turtle_tracker.x][turtle_tracker.y]);
    return true;
}
