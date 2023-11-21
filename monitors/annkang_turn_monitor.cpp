#include "monitor_interface.h"

// Keeps track of the last pose received
// moved is true if at least one pose has been received, false otherwise
static Pose last_pose;
static bool moved = false;
static Orientation last_orientation; 

// Flag that doesn't print pose updates if the turtle has moved 0 steps
static const bool suppress_double_visits = true;

/*
 * Returns absolute value of x
 * WARNING: unsafe for edge-case values
 */
inline int abs(int x) {
  return x < 0 ? -1*x : x;
}

/*
 * Whenever the turtle moves, compare the current location
 * to the previous location and throw an invariant violation
 * if the locations differ by more than 1 in Manhattan Distance.
 */
void poseInterrupt(ros::Time t, int x, int y, Orientation o) {
  // Print pose info
  ROS_INFO("[[%ld ns]] 'Pose' was sent. Data: o = %d", t.toNSec(), o);

  // Check that the turtle has moved before and that the Manhattan
  // distance between the positions does not exceed 1
  uint8_t distance = abs(last_orientation-o);
  if (distance > 1) {
    if (distance == 3 && last_orientation != 3) {
	if (distance == 3 && last_orientation != 0) { 
    ROS_WARN("VIOLATION: Difference between last orientation %d and current orientation %d is more than 90 degrees!", last_orientation, o);
        }
    }
  }

  // store last Pose in memory
  last_orientation = o;

  // Update this flag the first time the turtle moves
  if (!moved) {
    moved = true;
  }
}

/*
 * Empty interrupt handlers beyond this point
 */

void tickInterrupt(ros::Time t) {
}

void visitInterrupt(ros::Time t, int visits) {
}

void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {
}

void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
}
