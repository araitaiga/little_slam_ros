#ifndef SLAM_LAUNCHER_
#define SLAM_LAUNCHER_

#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/OccupancyGrid.h>

#include "little_slam_ros/slam_frontend.h"
#include "little_slam_ros/map_util.h"

class Point
{
    double x;
    double y;
};

class SlamLauncher
{

public:
    SlamLauncher();


private:
    ros::Subscriber scan_sub_;

    std::string map_frame_id_;
    bool got_initial_map_;
    double map_res_;

    ros::Duration map_update_interval_;
    

    SlamFrontend sf_;
    nav_msgs::OccupancyGrid map_;
    ros::Publisher map_pub_;

    MapUtil map_util_;

    double map_xmin_, map_ymin_;
    double map_xmax_, map_ymax_;

    

    void scanCallback(const sensor_msgs::LaserScan &scan);

    void updateMap(const sensor_msgs::LaserScan &scan);

};

#endif