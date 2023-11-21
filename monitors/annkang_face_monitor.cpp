#include "monitor_interface.h"

// Keeps track of the last pose received
// moved is true if at least one pose has been received, false otherwise
static Endpoints bump_args;
static Endpoints wall; 

void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
  switch (o) {
    case NORTH:
      ROS_INFO("NORTH, (%d, %d)", x, y); 
      wall.x1 = x+1;
      wall.y1 = y+1;
      wall.x2 = x;
      wall.y2 = y+1;
      break;
    case EAST:
      ROS_INFO("EAST, (%d, %d)", x, y); 
      wall.x1 = x+1;
      wall.y1 = y;
      wall.x2 = x+1;
      wall.y2 = y+1;
      break;
    case SOUTH: 
      ROS_INFO("SOUTH, (%d, %d)", x, y); 
      wall.x1 = x;
      wall.y1 = y;
      wall.x2 = x+1;
      wall.y2 = y; 
      break;
    case WEST: 
      ROS_INFO("WEST, (%d, %d)", x, y); 
      wall.x1 = x;
      wall.y1 = y+1;
      wall.x2 = x;
      wall.y2 = y;
      break;
  }
    ROS_INFO("wall coords (%d, %d), (%d, %d)",wall.x1, wall.y1, wall.x2, wall.y2); 
  bool combo1 = (wall.x1==bump_args.x1 && wall.x2==bump_args.x2 && wall.y1==bump_args.y1 && wall.y2 == bump_args.y2);
  bool combo2 = (wall.x2==bump_args.x1 && wall.x1==bump_args.x2 && wall.y2==bump_args.y1 && wall.y1 == bump_args.y2); 
  if (!combo1 && !combo2) {
    ROS_WARN("Turtle is not facing direction it is bumping in!");
  } 
}

void tickInterrupt(ros::Time t) {
}

void visitInterrupt(ros::Time t, int visits) {
}

void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {
  ROS_INFO("bumped called with (%d, %d), (%d, %d)", x1, y1, x2, y2); 
  bump_args.x1 = x1;
  bump_args.y1 = y1; 
  bump_args.x2 = x2; 
  bump_args.y2 = y2; 
}

void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
}
