#include <iostream>
#include <ros/ros.h>
#include <boost/bind.hpp>
#include <ece642rtle/timeInt8.h>
#include <std_msgs/Empty.h>
#include <ece642rtle/RTIbump.h>
#include <ece642rtle/RTIatend.h>
#include <ece642rtle/PoseOrntBundle.h>
#include <ece642rtle/bumpEcho.h>
#include <ece642rtle/aendEcho.h>
#include <QPointF>

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
void set_tracker_result(Tracker tracker);

State test_state_result();
uint8_t* test_memory_result();
uint8_t test_remaining_lefts_result();
uint8_t test_remaining_rights_result();

void ROS_ERROR(std::string e);