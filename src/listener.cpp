/**
 * \brief This code listens to raven messages and stores them to a file when
 * the robot has an e-stop.
 *
 * \author Andy Lewis
 * \date 4/15/2018
 */

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "raven_2/raven_state.h"

int frequency 			= 1000; //Hz sampling frequency
double buffer_window 	= .05;  //seconds of buffer to keep prior to e-stop
char e_stop_flag 		= 0;    //global flag for dumping buffer and protecting buffer


/** Stores ravenstate data into buffer with optional down-frequency
 *
 */
void ravenstateCallback(const raven_2::raven_state& msg)
{
	static int msg_count;
	int period = 1000 / frequency;

	if (e_stop_flag == 1) return; //if in e-stop, don't touch the buffer

	//set logical bounds on period
	if (period < 1) period = 1;
	if (period > 1000) period = 1000;

	//increment count for another message received
	msg_count++;

	if (msg_count % period == 0){
		ROS_INFO("I heard raven_data %i", msg_count);
		msg_count = 0;
	}



}
/** Stores buffer of ravenstate data into file
 *
 */

int storeBuffer(){
	return 0;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "blackBoxListener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("ravenstate", 1000, ravenstateCallback);


  if (e_stop_flag == 1){
	  if (storeBuffer() < 0){
		  ROS_INFO("dumping didn't work");
	  }
  }

  ros::spin();

  return 0;
}
