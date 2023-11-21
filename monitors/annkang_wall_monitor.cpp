#include "monitor_interface.h"

// Keeps track of the last pose received
// moved is true if at least one pose has been received, false otherwise
static Endpoints last_wall; 
static bool last_bumped; 
static bool moved = false;
static Pose last_pose; 

// Flag that doesn't print pose updates if the turtle has moved 0 steps
static const bool suppress_double_visits = true;

Endpoints get_wallcoords(int x, int y, Orientation o) {
  Endpoints wall; 
  switch (o) {
    case NORTH:
      wall.x1 = x+1;
      wall.y1 = y+1;
      wall.x2 = x;
      wall.y2 = y+1;
    case EAST:
      wall.x1 = x+1;
      wall.y1 = y;
      wall.x2 = x+1;
      wall.y2 = y+1;
    case SOUTH:  
      wall.x1 = x;
      wall.y1 = y;
      wall.x2 = x+1;
      wall.y2 = y; 
    case WEST: 
      wall.x1 = x;
      wall.y1 = y+1;
      wall.x2 = x;
      wall.y2 = y;
  }
  return wall; 
}

bool equal_endpoints(Endpoints wall, Endpoints bump_args) {
  bool combo1 = (wall.x1==bump_args.x1 && wall.x2==bump_args.x2 && wall.y1==bump_args.y1 && wall.y2 == bump_args.y2);
  bool combo2 = (wall.x2==bump_args.x1 && wall.x1==bump_args.x2 && wall.y2==bump_args.y1 && wall.y1 == bump_args.y2); 
  if (!combo1 && !combo2) {
    return false;
  } else {
    return true;
  } 
}

void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
  // Print pose info
  // Last conditional makes sure that if suppress_double_visits is
  // true, that the same pose isn't printed twice
  if (!suppress_double_visits || !moved ||
      (last_pose.x != x || last_pose.y != y)) {
    ROS_INFO("[[%ld ns]] 'Pose' was sent. Data: x = %d, y=%d", t.toNSec(), x, y);
  }
  
  // if turtle moved, check that it checked the wall and that bumped was false
  if (moved) {
  Endpoints wall = get_wallcoords(x, y, o); 
  if (x != last_pose.x || y!=last_pose.y) {
    if (!equal_endpoints) {
      ROS_WARN("VIOLATION: Turtle didn't check for bumped before moving!");
    } else if (last_bumped) {
      ROS_WARN("VIOLATION: Turtle walked through a wall!");
    }
  }
  }

  // store last Pose in memory
  last_pose.x = x;
  last_pose.y = y;

  // Update this flag the first time the turtle moves
  if (!moved) {
    moved = true;
  }
}

void tickInterrupt(ros::Time t) {
}

void visitInterrupt(ros::Time t, int visits) {
}

void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {
  last_wall.x1 = x1; 
  last_wall.y1 = y1; 
  last_wall.x2 = x2; 
  last_wall.y2 = y2; 
  last_bumped = bumped; 
}

void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
}
