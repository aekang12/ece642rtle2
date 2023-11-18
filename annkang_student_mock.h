#include <iostream>
#include <stdint.h>

enum State {Turned_left, Turned_right, Moved, Sleeping};
enum Moves {Right, Left, Straight};
Moves studentTurtleStep(bool bumped, int& direction);
const uint8_t num_dirs = 4; 
const uint8_t num_coords = 4;
enum Directions {West, North, East, South};

void set_mock_state(State state);
void set_mock_memory(uint8_t memory[3]);
void set_mock_rlefts(int16_t remaining_lefts);
void set_mock_rrights(int16_t remaining_rights);
void set_mock_array(uint8_t array[24][24]);
void set_mock_x(uint8_t x); 
void set_mock_y(uint8_t y);

State get_mock_state();
uint8_t* get_mock_memory();
int16_t get_mock_rlefts();
int16_t get_mock_rrights();
uint8_t get_mock_visits(uint8_t x, uint8_t y); 
uint8_t (*get_mock_array())[24];
uint8_t get_mock_x(); 
uint8_t get_mock_y();

void ROS_ERROR_dummy(std::string e);
