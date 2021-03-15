#ifndef SLAM_FRONTEND_
#define SLAM_FRONTEND_

#include "ros/ros.h"

#include <sensor_msgs/LaserScan.h>

#include "little_slam_ros/scan_matcher.h"

class SlamFrontend
{
public:
    SlamFrontend();

    void processScan(const sensor_msgs::LaserScan &scan);


    ScanMatcher *scan_matcher_;


private:

};

#endif