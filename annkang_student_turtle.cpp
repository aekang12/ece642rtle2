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

// tracker is a 24 by 24 array that helps maze track how many times 
// each cell has been visited. trackerx and trackery keep track of turtle 
// position, initialized to the center of array
static struct tracker{
    uint8_t array[23][23] = {};
    uint8_t x = 11; 
    uint8_t y = 11; 
    
    // constructor for initialization 
    tracker() {
	array[11][11] = 1; 
    }
} turtle_tracker;

// this procedure tracks number of visits to each cell in the turtle's 
// local array. it takes in direction, the turtle's current direction
void track_turtle(int& direction) {
    switch ((Directions)direction) {
	case North:
	    turtle_tracker.y += 1;
	    break;
	case East:
	    turtle_tracker.x += 1;
	    break;
	case South:
	    turtle_tracker.y -= 1;
	    break;
	case West:
	    turtle_tracker.x -= 1;
	    break;
	default:
	    ROS_ERROR("Invalid direction!"); 
    }
    turtle_tracker.array[turtle_tracker.x][turtle_tracker.y] += 1;
    mazeVisits(turtle_tracker.array[turtle_tracker.x][turtle_tracker.y]);
    return; 
}

// this procedure recommends next move following the left hand rule 
// bumped is true if there is a wall in front of the turtle, false otherwise
Moves studentTurtleStep(bool bumped, int& direction) {
    static Moves move;

    // sleep for 1 second, changing sleep duration changes turtle speed
    sleep(0.1); 

    if (move == Straight) {
	move = Left;
	track_turtle(direction);
    } else if (bumped) {
	move = Right;
    } else {
	move = Straight;
    }
    
    ROS_INFO("Orientation=%i", direction);
    return move;
}

