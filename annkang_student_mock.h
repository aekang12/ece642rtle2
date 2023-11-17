#include <iostream>
#include <stdint.h>

enum State {Turned_left, Turned_right, Moved};
enum Moves {Right, Left, Straight};
Moves studentTurtleStep(bool bumped, int& direction);
const uint8_t num_dirs = 4; 
const uint8_t num_coords = 4;
enum Directions {West, North, East, South};

// Functions called by main testing program to get or set values
void set_state_result(State state);
void set_memory_result(uint8_t memory[3]);
void set_rlefts_result(uint8_t remaining_lefts);
void set_rrights_result(uint8_t remaining_rights);
void set_tracker_result(uint8_t array[24][24]);

void set_current_state(State current_state);
void set_remaining_lefts(uint16_t rlefts_test);
void set_remaining_rights(uint16_t rrights_test);
void set_tracker(uint8_t array[24][24], uint8_t x, uint8_t y);
void set_memory(uint8_t memory[3]);

State test_state_result();
uint8_t* test_memory_result();
uint8_t test_remaining_lefts_result();
uint8_t test_remaining_rights_result();
uint8_t test_tracker(uint8_t x, uint8_t y); 

void ROS_ERROR(std::string e);
