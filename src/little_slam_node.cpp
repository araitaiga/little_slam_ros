#include "ros/ros.h"

#include "little_slam_ros/slam_launcher.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "little_slam_ros");
    ros::NodeHandle nh;
    SlamLauncher sl;

    ros::spin();
    return 0;
}