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
static struct Tracker{
    uint8_t array[23][23] = {};
    uint8_t x = 11; 
    uint8_t y = 11; 
} tracker;
static int memory[3] = {0}; 
typedef struct coordinates coordinates; 
struct coordinates {
    uint8_t x;
    uint8_t y;
};

// clear the turtle's memory 
void clear_memory() {
    memory[(int)Straight] = 0; 
    memory[(int)Left] = 0; 
    memory[(int)Right] = 0; 
}

// update turtle's local (x,y) position
void update_pos(int& direction) {
    switch ((Directions)direction) {
	case North:
	    tracker.y += 1;
	    break;
	case East:
	    tracker.x += 1;
	    break;
	case South:
	    tracker.y -= 1;
	    break;
	case West:
	    tracker.x -= 1;
	    break;
	default:
	    ROS_ERROR("Invalid direction!"); 
    }
    tracker.array[tracker.x][tracker.y] += 1;
    mazeVisits(tracker.array[tracker.x][tracker.y]);
    return; 
}

// gets coordinates of the cell direclty in front of it 
coordinates get_pos_ahead(int& direction) {
    coordinates c; 
    switch ((Directions)direction) {
	case North:
	    c.x = tracker.x;
	    c.y = tracker.y + 1;
	    break;
	case East:
	    c.x = tracker.x+1;
	    c.y = tracker.y; 
	    break;
	case South:
	    c.x = tracker.x;
	    c.y = tracker.y-1; 
	    break;
	case West:
	    c.x = tracker.x-1;
	    c.y = tracker.y; 
	    break;
	default:
	    ROS_ERROR("Invalid direction!"); 
	    break;
    }
    return c;
}

// updates the turtle's memory of what's direclty in front of it 
int look_ahead(bool bumped, int& direction) {
    const int wall_val = 1000;
    if (bumped) {
	return wall_val; 
    } else {
	coordinates c = get_pos_ahead(direction); 
    	return tracker.array[c.x][c.y];
    }
}

// check if the turlte is in a dead end
bool all_walls(int memory[3]) {
    int min_value = 1000;
    int min_index = 0;
    std::list<int> DIRS;  
    for (int i = 0; i < 3; ++i) {
	if (memory[i] < min_value) {
	    min_value = memory[i];
	    min_index = i;
	}
    }
    if (min_value == 1000) {
	// dead end, return empty DIRS
	return true; 
    }
    return false;
}

// get DIRS, a list of directions to turn in to face the minimum 
// visited path 
std::list<Moves> get_DIRS(int memory[3]) {
    int min_value = 1000;
    int min_index = 0;
    for (int i = 0; i < 3; ++i) {
	if (memory[i] < min_value) {
	    min_value = memory[i];
	    min_index = i;
	}
    }
    if ((Moves)min_index == Right) {
	return {}; 
    } else if ((Moves)min_index == Left) {
	return {Left, Left};
    } else if ((Moves)min_index == Straight) {
	return {Left};
    }
}

// this procedure recommends next move following DFS 
// bumped is true if there is a wall in front of the turtle, false otherwise
Moves studentTurtleStep(bool bumped, int& direction) {
    static Moves move;
    static State state = Moved;
    static int remaining_rights = 0;
    static std::list<Moves> DIRS;
    int num_visits;

    // sleep for 1 second, changing sleep duration changes turtle speed
    sleep(0.1);
    switch (state) {
	case Spawned:
	    // this is assuming turtle never spawns facing a wall
	    update_pos(direction);
	    state = Moved; 
	    return Straight;
	case Moved:
	    num_visits = look_ahead(bumped, direction);
	    memory[(int)Straight] = num_visits;
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
	    memory[(int)Left] = num_visits;
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
	    memory[(int)Right] = num_visits;
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
	    // note that turtle will never be in Goal state since 
	    // maze.cpp will stop calling turtle.cpp so it is not included 
	    // in this switch statement
	    ROS_ERROR("Invalid direction!"); 
    }
    
    ROS_INFO("Orientation=%i", direction);
    return Left;
	    	ROS_INFO("STATE IS LEFT");
}


