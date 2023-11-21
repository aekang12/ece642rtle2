#include "monitor_interface.h"

// Keeps track of the last pose received
// moved is true if at least one pose has been received, false otherwise
static Pose last_pose;
static bool moved = false;

// Flag that doesn't print pose updates if the turtle has moved 0 steps
static const bool suppress_double_visits = true;

/*
 * Returns absolute value of x
 * WARNING: unsafe for edge-case values
 */
inline int abs(int x) {
  return x < 0 ? -1*x : x;
}

void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
  // Print pose info
  // Last conditional makes sure that if suppress_double_visits is
  // true, that the same pose isn't printed twice
  if (!suppress_double_visits || !moved ||
      (last_pose.x != x || last_pose.y != y)) {
    ROS_INFO("[[%ld ns]] 'Pose' was sent. Data: x = %d, y=%d", t.toNSec(), x, y);
  }
  
  // if turtle moved, check that it's facing the right orientation
  if (moved) {
  if (x > last_pose.x) { // moved west
    if (o != EAST) {
      ROS_WARN("VIOLATION: Turtle moved East but was not facing East");
    }
  } else if (x < last_pose.x) { //moved west
    if (o != WEST) {
      ROS_WARN("VIOLATION: Turtle moved West but was not facing West");
    }
  } else if (y > last_pose.y) { //moved north
    if (o != SOUTH) {
      ROS_WARN("VIOLATION: Turtle moved North but was not facing North");
    }
  } else if (y < last_pose.y) { //moved south 
    if (o != NORTH) {
      ROS_WARN("VIOLATION: Turtle moved South but was not facing South");
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
}

void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
}
