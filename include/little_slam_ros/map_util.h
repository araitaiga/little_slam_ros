#ifndef MAP_UTIL_
#define MAP_UTIL_

#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/OccupancyGrid.h>

class MapUtil
{

public:
    class Point
    {
        double x;
        double y;
    };

    MapUtil();

    int getMapSizeX();
    int getMapSizeY();

private:
};

#endif