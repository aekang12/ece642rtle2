#include "monitor_interface.h"

// Keeps track of the last pose received
// moved is true if at least one pose has been received, false otherwise
static Pose end_pose; 
static ros::Time end_time; 
static Orientation end_o; 
static bool turtle_is_atend = false;

void poseInterrupt(ros::Time t, int x, int y, Orientation o) { 
  if (turtle_is_atend) {
    if (t == end_time) {
      end_o = o; 
    }
    if (x != end_pose.x || y != end_pose.y || o != end_o) {
      ROS_WARN("Turtle moved or turned after reaching goal!"); 
    }
  }
}

void tickInterrupt(ros::Time t) {
}

void visitInterrupt(ros::Time t, int visits) {
}

void bumpInterrupt(ros::Time t, int x1, int y1, int x2, int y2, bool bumped) {
}

void atEndInterrupt(ros::Time t, int x, int y, bool atEnd) {
  if (atEnd) {
    ROS_INFO("turtle is at end!");
    end_pose.x = x; 
    end_pose.y = y; 
    end_time = t; 
    turtle_is_atend = true;
  }
}
