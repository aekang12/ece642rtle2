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

#ifdef testing
#include "annkang_student_mock.h"
#endif
#ifndef testing
#include "student.h"
#include "ros/ros.h"
#endif
#include <unistd.h>
#include <cstring>
#include <cstdio>

// tracker is a 24 by 24 array that helps turtle track how many times 
// each cell has been visited. trackerx and trackery keep track of turtle 
// position, initialized to the center of array
static struct Tracker{
    uint8_t array[24][24];
    uint8_t x; 
    uint8_t y;
    Tracker() : x(11), y(11) {
	std::memset(array, 0, sizeof(array)); 
    } 
} tracker;
typedef struct coordinates coordinates; 
struct coordinates {
    uint8_t x;
    uint8_t y;
};
// if there is a wall to the left/right/straight of the turtle, set that
// memory value to be 100
const uint8_t wall_value = 100;

// REQUIRES: turtle is going straight 
// clear the turtle's memory and update tracker 
void clearmem_updatepos(uint8_t memory[3], int& direction) {
    memory[(uint8_t)Straight] = 0; 
    memory[(uint8_t)Left] = 0; 
    memory[(uint8_t)Right] = 0; 
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
	    #ifdef testing
	    ROS_ERROR_dummy("Invalid direction!"); 
	    #endif 
	    #ifndef testing
	    ROS_ERROR("Invalid direction!"); 
	    #endif
    }
    tracker.array[tracker.x][tracker.y] =(uint8_t)(tracker.array[tracker.x][tracker.y] + 1);
    #ifndef testing 
        mazeVisits(tracker.array[tracker.x][tracker.y]);
    #endif
    return; 
}

// gets coordinates of the cell direclty in front of turtle 
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
	    #ifdef testing
	    ROS_ERROR_dummy("Invalid direction!"); 
	    #endif 
	    #ifndef testing
	    ROS_ERROR("Invalid direction!"); 
	    #endif
	    break;
    }
    return c;
}

// return true if turtle should go straight, false otherwise 
// checks if cell in front of turtle is unvisited 
uint8_t go_straight(bool bumped, Moves move, int& direction, uint8_t memory[3]) {
    const uint8_t wall_val = (uint8_t)wall_value;
    uint8_t num_visits = 0;
    if (bumped) {
	memory[(uint8_t)move] = wall_val;
	return false;
    } else {
	coordinates c = get_pos_ahead(direction);
	num_visits = tracker.array[c.x][c.y];
	if (num_visits ==0) {
	    clearmem_updatepos(memory, direction);
	    return true;
	} else {
	    coordinates c = get_pos_ahead(direction); 
	    memory[(uint8_t)move] = tracker.array[c.x][c.y];
	    return false; 
	}
    }
}

// return how many lefts the turtle should turn to face the least 
// visited path 
int16_t count_lefts(uint8_t memory[3]) {
    uint8_t min_value = wall_value;
    uint8_t min_index = 0;
    for (uint8_t i = 0; i < 3; ++i) {
	if (memory[i] < min_value) {
	    min_value = memory[i];
	    min_index = i;
	}
    }
    if (min_value == wall_value) {
	return 3; 
    } else if ((Moves)min_index == Right) {
	return 0; 
    } else if ((Moves)min_index == Left) {
	return 2;
    } else {
	return 1;
    }
}

// this procedure recommends next move following DFS 
Moves studentTurtleStep(bool bumped, int& direction) {
    static State state = Moved;
    static Moves next_move = Straight;
    static int16_t remaining_rights = -1;
    static int16_t remaining_lefts = -1;
    // memory is an array storing number of visits to the cells ahead on the
    // right, left, and straight of the turtle
    static uint8_t memory[3] = {0}; 

    #ifdef testing    
    // for unit testing:
    state = get_mock_state();
    remaining_rights = get_mock_rrights(); 
    remaining_lefts = get_mock_rlefts(); 
    uint8_t (*set_array)[24] = get_mock_array();
    for (int i=0; i<24; i++) {
	for (int j=0; j<24; j++) {
    	    tracker.array[i][j] = set_array[i][j];
	}
    } 	
    tracker.x = get_mock_x();
    tracker.y = get_mock_y();
    uint8_t *set_memory = get_mock_memory(); 
    memory[0] = set_memory[0];
    memory[1] = set_memory[1]; 
    memory[2] = set_memory[2];  
    #endif

    // sleep for x seconds, changing sleep duration changes turtle speed
    sleep(0.1);
    switch (state) {
	case Moved: 
	    if (go_straight(bumped,Straight, direction, memory)) { 
		next_move = Straight;
	    } else {
	        state = Turned_left; 
		next_move = Left;
	    } 
	    break;
	case Turned_left:
	    remaining_lefts = int16_t(remaining_lefts - 1); 
	    if (remaining_lefts > 0) {
		next_move = Left; 
	    }
	    else if (remaining_lefts == 0) {
	        clearmem_updatepos(memory, direction);
		state = Moved;
		next_move = Straight;
	    }
	    else if (go_straight(bumped,Left, direction, memory)) {
		state = Moved; 
		next_move =  Straight;
	    } else {
		remaining_rights = 2; 
		state = Turned_right; 
		next_move =  Right;
	    }
	    break;
	case Turned_right:
	    remaining_rights = int16_t(remaining_rights -1); 
	    if (remaining_rights > 0) {
		next_move = Right; 
	    }
	    else if (go_straight(bumped,Right, direction, memory)) {
		state = Moved;
		next_move = Straight;
	    }
	    else if (count_lefts(memory) == 0) {
		clearmem_updatepos(memory, direction);
	  	state = Moved;
		next_move = Straight;
	    } else {
	        remaining_lefts = count_lefts(memory);
	        state = Turned_left; 
	        next_move = Left;
	    } 
	    break;
	default:
	    #ifdef testing
	    ROS_ERROR_dummy("Invalid direction!"); 
	    #endif 
	    #ifndef testing
	    ROS_ERROR("Invalid direction!"); 
	    #endif
    }

	// for unit testing 
	#ifdef testing
	set_mock_state(state);
	set_mock_memory(memory);
	set_mock_rlefts(remaining_lefts);
	set_mock_rrights(remaining_rights);
	set_mock_array(tracker.array);
	set_mock_x(tracker.x);
	set_mock_y(tracker.y);
	#endif
    return next_move;
}


