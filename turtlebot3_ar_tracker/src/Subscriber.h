#ifndef TURTLEBOT3_AR_TRACKER_SUBSCRIBER_H
#define TURTLEBOT3_AR_TRACKER_SUBSCRIBER_H

#include <ros/ros.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <ar_track_alvar_msgs/AlvarMarker.h>
#include <turtlebot3_ar_msgs/msg.h>
#include <stdio.h>
#include <std_msgs/String.h>


class Subscriber
{
private:

    double lastback;
    int backcount;

    double forward;
    double left;
    double up;
    double distance;

    double offset_x;
    double offset_y;
    double offset_z;

    int init_argc;
    char** init_argv;

    geometry_msgs::Pose pose;
    ros::NodeHandle nh;
    ros::Publisher pub;

public:
    Subscriber(int argc, char** argv);
    ~Subscriber();
    void ar_marker_callback(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg);
    void message_pub(double forward, double left, double up, double distance);
};


#endif //TURTLEBOT3_AR_TRACKER_SUBSCRIBER_H
