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

// tracker is a 24 by 24 array that helps turtle track how many times 
// each cell has been visited. trackerx and trackery keep track of turtle 
// position, initialized to the center of array
static struct Tracker{
    uint8_t array[23][23] = {};
    uint8_t x = 11; 
    uint8_t y = 11; 
} tracker;
// memory is an array storing number of visits to the cells ahead on the
// right, left, and straight of the turtle
static uint8_t memory[3] = {0}; 
typedef struct coordinates coordinates; 
struct coordinates {
    uint8_t x;
    uint8_t y;
};
// if there is a wall to the left/right/straight of the turtle, set that
// memory value to be 100
const uint8_t wall_value = 100;

// clear the turtle's memory 
void clear_memory() {
    memory[(uint8_t)Straight] = 0; 
    memory[(uint8_t)Left] = 0; 
    memory[(uint8_t)Right] = 0; 
}

// update tracker when turtle moves straight
void update_pos(int& direction) {
    switch ((Directions)direction) {
	case North:
	    tracker.y = uint8_t(tracker.y+1);
	    break;
	case East:
	    tracker.x = uint8_t(tracker.x+1);
	    break;
	case South:
	    tracker.y = uint8_t(tracker.y-1);
	    break;
	case West:
	    tracker.x = uint8_t(tracker.x-1);
	    break;
	default:
	    ROS_ERROR("Invalid direction!"); 
    }
    tracker.array[tracker.x][tracker.y] =(uint8_t)(tracker.array[tracker.x][tracker.y] + 1);
    mazeVisits(tracker.array[tracker.x][tracker.y]);
    return; 
}

// gets coordinates of the cell direclty in front of it 
coordinates get_pos_ahead(int& direction) {
    coordinates c; 
    switch ((Directions)direction) {
	case North:
	    c.x = (uint8_t)(tracker.x);
	    c.y = (uint8_t)(tracker.y +1);
	    break;
	case East:
	    c.x = (uint8_t)(tracker.x+1);
	    c.y = (uint8_t)(tracker.y); 
	    break;
	case South:
	    c.x = (uint8_t)(tracker.x);
	    c.y = (uint8_t)(tracker.y-1); 
	    break;
	case West:
	    c.x = (uint8_t)(tracker.x-1);
	    c.y = (uint8_t)(tracker.y); 
	    break;
	default:
	    ROS_ERROR("Invalid direction!"); 
	    break;
    }
    return c;
}

// updates the turtle's memory of what's direclty in front of it 
uint8_t look_ahead(bool bumped, int& direction) {
    const uint8_t wall_val = (uint8_t)wall_value;
    if (bumped) {
	return wall_val; 
    } else {
	coordinates c = get_pos_ahead(direction); 
    	return tracker.array[c.x][c.y];
    }
}

// check if the turlte is in a dead end
bool all_walls(uint8_t memory[3]) {
    uint8_t min_value = wall_value;
    for (uint8_t i = 0; i < 3; ++i) {
	if (memory[i] < min_value) {
	    min_value = memory[i];
	}
    }
    if (min_value == wall_value) {
	// dead end, return empty DIRS
	return true; 
    }
    return false;
}

// get DIRS, a list of directions to turn in to face the least 
// visited path 
std::list<Moves> get_DIRS(uint8_t memory[3]) {
    uint8_t min_value = wall_value;
    uint8_t min_index = 0;
    for (uint8_t i = 0; i < 3; ++i) {
	if (memory[i] < min_value) {
	    min_value = memory[i];
	    min_index = i;
	}
    }
    if ((Moves)min_index == Right) {
	return {}; 
    } else if ((Moves)min_index == Left) {
	return {Left, Left};
    } else {
	return {Left};
    }
}

// this procedure recommends next move following DFS 
// bumped is true if there is a wall in front of the turtle, false otherwise
Moves studentTurtleStep(bool bumped, int& direction) {
    static State state = Moved;
    static int remaining_rights = 0;
    static std::list<Moves> DIRS;
    uint8_t num_visits;

    // sleep for x seconds, changing sleep duration changes turtle speed
    sleep(0.1);
    switch (state) {
	case Moved:
	    num_visits = look_ahead(bumped, direction);
	    memory[(uint8_t)Straight] = num_visits;
            if (num_visits == 0) {
		clear_memory();
	        update_pos(direction);
		state = Moved;
		return Straight;
	    } else {
	        state = Turned_left; 
		return Left;
	    } 
	case Turned_left:
	    num_visits = look_ahead(bumped, direction);
	    memory[(uint8_t)Left] = num_visits;
            if (num_visits == 0) {
		clear_memory();
	        update_pos(direction);
		state = Moved;
		return Straight;
	    } else {
		remaining_rights = 2; 
		state = Turned_right; 
		return Right;
	    }
	case Turned_right:
	    remaining_rights -= 1; 
	    if (remaining_rights > 0) {
		state = Turned_right; 
		return Right; 
	    }
	    num_visits = look_ahead(bumped, direction);
	    memory[(uint8_t)Right] = num_visits;
            if (num_visits == 0) {
		clear_memory();
	        update_pos(direction);
		state = Moved;
		return Straight;
	    } else {
		if (all_walls(memory)) {
		    state = Back;
		    return Right;
		}
		DIRS = get_DIRS(memory);
		if (DIRS.empty()) {
		    clear_memory();
	            update_pos(direction);
		    state = Moved;
		    return Straight;
		}
		state = Turn_min;
		Moves next = DIRS.front();  
		DIRS.pop_front();
		return next;
	    }
	case Back:
	    clear_memory();
	    update_pos(direction);
	    state = Moved;
	    return Straight;
	case Turn_min:
	    if (DIRS.empty()) {
	    	clear_memory();
	    	update_pos(direction);
	    	state = Moved;
		return Straight;
	    } else {
		Moves next = DIRS.front();
		DIRS.pop_front(); 
		return next; 
	    }
	default:
	    ROS_ERROR("Invalid direction!"); 
    }
    return Left;
}


