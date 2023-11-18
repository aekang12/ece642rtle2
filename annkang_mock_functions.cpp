#include "annkang_student_mock.h"
#include <iostream>

static bool mock_error = false;
static uint8_t mock_memory[3]; 
static State mock_state; 
static int16_t mock_remaining_lefts;
static int16_t mock_remaining_rights;
static uint8_t mock_tracker[24][24];
static uint8_t mock_x;
static uint8_t mock_y;

// Getter functions called by unit tests
State get_mock_state(){
    return mock_state; 
}
uint8_t* get_mock_memory() {
    return mock_memory; 
}
int16_t get_mock_rlefts() {
    return mock_remaining_lefts;
} 
int16_t get_mock_rrights() {
    return mock_remaining_rights;
}
uint8_t get_mock_visits(uint8_t x, uint8_t y){
    return mock_tracker[x][y];
}
uint8_t (*get_mock_array())[24] {
    return mock_tracker;
}
uint8_t get_mock_x() {
    return mock_x;
}
uint8_t get_mock_y() {
    return mock_y;
}

// Setter functions for results called by turtle 
void set_mock_state(State state) {
    mock_state = state;
}
void set_mock_memory(uint8_t memory[3]) {
    mock_memory[0] = memory[0];
    mock_memory[1] = memory[1]; 
    mock_memory[2] = memory[2];
}
void set_mock_rlefts(int16_t remaining_lefts) {
    mock_remaining_lefts = remaining_lefts;
}
void set_mock_rrights(int16_t remaining_rights) {
    mock_remaining_rights = remaining_rights;
}
void set_mock_array(uint8_t tracker[24][24]) {
    for (uint8_t i=0; i<24; i++) {
	for (uint8_t j=0; j<24; j++) {
	    mock_tracker[i][j] = tracker[i][j];
	}
    }
}
void set_mock_x(uint8_t x) {
    mock_x = x;
}
void set_mock_y(uint8_t y) {
    mock_y = y;
}

// dummy ROS_ERROR
void ROS_ERROR_dummy(std::string e) {
    mock_error=true;
    std::cout << e;
}
