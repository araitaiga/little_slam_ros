#include "little_slam_ros/slam_launcher.h"

#define MAP_IDX(sx, i, j) ((sx) * (j) + (i))

SlamLauncher::SlamLauncher() : got_initial_map_(false)
{
    ROS_INFO_STREAM("Create SlamLauncher.");

    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");

    map_pub_ = nh.advertise<nav_msgs::OccupancyGrid>("map", 10);

    scan_sub_ = nh.subscribe("scan", 100000, &SlamLauncher::scanCallback, this);

    pnh.param("map_frame_id", map_frame_id_, std::string("map"));

    double tmp;
    pnh.param("map_update_interval", tmp, 2.0);
    map_update_interval_.fromSec(tmp);

    pnh.param("map_res", map_res_, 0.05);

    pnh.param("map_xmin", map_xmin_, -100.0);
    pnh.param("map_ymin", map_ymin_, -100.0);
    pnh.param("map_xmax", map_xmax_, 100.0);
    pnh.param("map_ymax", map_ymax_, 100.0);
}

void SlamLauncher::scanCallback(const sensor_msgs::LaserScan &scan)
{
    static ros::Time last_map_update(0.0);
    ROS_DEBUG_STREAM("Recieved new scan.");

    sf_.processScan(scan);

    if (!got_initial_map_ || (scan.header.stamp - last_map_update) > map_update_interval_)
    {
        updateMap(scan);
        last_map_update = scan.header.stamp;
        ROS_INFO_STREAM("Updated the map");
    }
}

void SlamLauncher::updateMap(const sensor_msgs::LaserScan &scan)
{

    if (!got_initial_map_)
    {
        map_.info.resolution = map_res_;
        map_.info.origin.position.x = 0.0;
        map_.info.origin.position.y = 0.0;
        map_.info.origin.position.z = 0.0;
        map_.info.origin.orientation.x = 0.0;
        map_.info.origin.orientation.y = 0.0;
        map_.info.origin.orientation.z = 0.0;
        map_.info.origin.orientation.w = 1.0;
    }
    else
    {
        // debug
        map_.info.resolution = map_res_;
        map_.info.origin.position.x = 0.0;
        map_.info.origin.position.y = 0.0;
        map_.info.origin.position.z = 0.0;
        map_.info.origin.orientation.x = 0.0;
        map_.info.origin.orientation.y = 0.0;
        map_.info.origin.orientation.z = 0.0;
        map_.info.origin.orientation.w = 1.0;
    }

    if (map_.info.width != (unsigned int)map_util_.getMapSizeX() || map_.info.height != (unsigned int)map_util_.getMapSizeY())
    {
        map_.info.width = map_util_.getMapSizeX();
        map_.info.height = map_util_.getMapSizeY();
        map_.info.origin.position.x = map_xmin_;
        map_.info.origin.position.y = map_ymin_;
        map_.data.resize(map_.info.width * map_.info.height);
    }

    for (int x = 0; x < map_util_.getMapSizeX(); x++)
    {
        for (int y = 0; y < map_util_.getMapSizeY(); y++)
        {
            map_.data[MAP_IDX(map_.info.width, x, y)] = 100;
        }
    }

    map_.header.stamp = ros::Time::now();
    map_.header.frame_id = map_frame_id_;

    got_initial_map_ = true;

    map_pub_.publish(map_);
}