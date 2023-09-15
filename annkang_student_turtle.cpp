/* 
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME: Ann Kang
 * ANDREW ID: annkang
 * LAST UPDATE:
 *
 * This file is an algorithm to solve the ece642rtle maze
 * using the left-hand rule. The code is intentionaly left obfuscated.
 *
 */

#include "student.h"

// Ignore this line until project 5
turtleMove studentTurtleStep(bool bumped) {return MOVE;}

// OK TO MODIFY BELOW THIS LINE

#define TIMEOUT 40    // bigger number slows down simulation so you can see what's happening
float w, cs;
		 
// this procedure takes the current turtle position and orientation and returns
// true=submit changes, false=do not submit changes
// Ground rule -- you are only allowed to call the helper functions "bumped(..)" and "atend(..)",
// and NO other turtle methods or maze methods (no peeking at the maze!)
bool studentMoveTurtle(QPointF& pos_, int& nw_or) {
    //ROS_INFO("Turtle update Called  w=%f", w);
    bool bp = false;

    if (atend(pos_.x(), pos_.y())) {
	return false;
    }

    if(w == 0) {
	if (nw_or==0) {
	    bp = bumped(pos_.x(),pos_.y(),pos_.x(),pos_.y()+1);
	} else if (nw_or == 1) {
	    bp = bumped(pos_.x(),pos_.y(),pos_.x()+1,pos_.y());
	} else if (nw_or == 2) {
	    bp = bumped(pos_.x()+1,pos_.y(),pos_.x()+1,pos_.y()+1);
	} else {
	    bp = bumped(pos_.x(),pos_.y()+1,pos_.x()+1,pos_.y()+1);
	}
	
	if (cs == 2) {
	    nw_or = (nw_or+3) % 4;
	    cs = 1;
	} else if (bp) {
	    nw_or = (nw_or + 1) % 4; 
	    cs = 0;
	} else {
	    cs = 2;
     if (nw_or == 1) pos_.setY(pos_.y() - 1); 
     if (nw_or == 2) pos_.setX(pos_.x() + 1);
     if (nw_or == 3) pos_.setY(pos_.y() + 1);
     if (nw_or == 0) pos_.setX(pos_.x() - 1);
	}	
	 //ROS_INFO("Orientation=%f  STATE=%f", nw_or, cs);
	w = TIMEOUT;
	return true;
    } else {
	w -= 1;
 }
 return false;
}
