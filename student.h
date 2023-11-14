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

// Functions to interface with ROS. Don't change these lines!
bool bumped(int x1,int y1,int x2,int y2);
bool atend(int x, int y);
void displayVisits(int visits);
bool moveTurtle(QPointF& pos_, int& nw_or);

// Scope-preserving changes to these lines permitted (see p5 writeup)
enum turtleMove {MOVE};
enum Directions {West, North, East, South};
enum State {Turned_left, Turned_right, Moved};
enum Moves {Right, Left, Straight};
const uint8_t num_dirs = 4; 
const uint8_t num_coords = 4;
QPointF translatePos(QPointF pos_, int direction, Moves nextMove);
int translateOrnt(int orientation, Moves nextMove);
Moves studentTurtleStep(bool bumped, int& direction);
void mazeVisits(uint8_t num_visits);

// OK to change below this line
bool studentMoveTurtle(QPointF& pos_, int& nw_or);


