#include "monitor_interface.h"

// Keeps track of the last pose received
// moved is true if at least one pose has been received, false otherwise
static uint8_t pose = 0;
static uint8_t visit = 0;
static uint8_t bump = 0 ; 

void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
  pose = pose + 1;
}

void tickInterrupt(ros::Time t) {
  ROS_INFO("'Tick' was sent.");
  if (pose > 1 || visit > 1 || bump > 1) {
    ROS_WARN("VIOLATION: more than one call to pose, visit, or bump");
}
  pose = 0;
  visit = 0;
  bump = 0;
}

void visitInterrupt(ros::Time t, int visits) {
  visit = visit + 1;
}

void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {
  bump = bump + 1;
}

void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
}
