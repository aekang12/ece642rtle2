#include "annkang_student_mock.h"
#include <iostream>

static bool mock_error = false;
static uint8_t mock_memory[3]; 
static State mock_state; 
static uint8_t mock_remaining_lefts;
static uint8_t mock_remaining_rights;
static uint8_t mock_tracker[24][24];

// Getter functions called by unit tests
State test_state_result(){
    return mock_state; 
}
uint8_t* test_memory_result() {
    return mock_memory; 
}
uint8_t test_remaining_lefts_result() {
    return mock_remaining_lefts;
} 
uint8_t test_remaining_rights_result() {
    return mock_remaining_rights;
}
uint8_t test_tracker(uint8_t x, uint8_t y){
    return mock_tracker[x][y];
}

// Setter functions called by turtle 
void set_state_result(State state) {
    mock_state = state;
}
void set_memory_result(uint8_t memory[3]) {
    mock_memory[0] = memory[0];
    mock_memory[1] = memory[1];
    mock_memory[2] = memory[2];
}
void set_rlefts_result(uint8_t remaining_lefts) {
    mock_remaining_lefts = remaining_lefts;
}
void set_rrights_result(uint8_t remaining_rights) {
    mock_remaining_rights = remaining_rights;
}
void set_tracker_result(uint8_t tracker[24][24]) {
    for (uint8_t i=0; i<24; i++) {
	for (uint8_t j=0; j<24; j++) {
	    mock_tracker[i][j] = tracker[i][j];
	}
    }
}

// dummy ROS_ERROR
void ROS_ERROR(std::string e) {
    mock_error=true;
    std::cout << e <<std::endl;
}
