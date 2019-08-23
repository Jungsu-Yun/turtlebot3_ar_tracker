#include "Subscriber.h"
#include <iostream>
#include <string>

double Offset_x;
double Offset_y;
double Offset_z;

using namespace std;

Subscriber::Subscriber(int argc, char** argv) : init_argc(argc), init_argv(argv)
{
    Offset_x = 0;
    Offset_y = 0;
    Offset_z = 0.5;

    this->offset_x = Offset_x;
    this->offset_y = Offset_y;
    this->offset_z = Offset_z;

    this->backcount = 10;
    ros::init(init_argc, init_argv, "calculator");
}

Subscriber::~Subscriber()
{
    if(ros::isStarted())
    {
        ros::shutdown();
        ros::waitForShutdown();
    }
    wait();
}

void Subscriber::ar_marker_callback(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr &msg)
{
    if(msg->markers.empty())
    {
        if(ros::Time::now().toSec() - this->lastback > 0.5 && backcount < 6)
        {
            message_pub(0, 0, 0, 0);
            ROS_INFO("BACKING UP!");

            lastback = ros::Time::now().toSec();
            backcount ++;
        }
        return;
    }

    backcount = 0;

    ar_track_alvar_msgs::AlvarMarker marker = msg->markers.at(0);
    pose = marker.pose.pose;

    double forward = pose.position.z - offset_z;
    double left = -(pose.position.x - offset_x);
    double up = -(pose.position.y - offset_y);
    double distance = sqrt(forward*forward+left*left+up*up);

    message_pub(forward, left, up, distance);
}

void Subscriber::message_pub(double forward, double left, double up, double distance)
{
    pub = nh.advertise<turtlebot3_ar_msgs::msg>("ar_marker_position", 100);
    turtlebot3_ar_msgs::msg msg_;
    msg_.foward = forward;
    msg_.left = left;
    msg_.up = up;
    msg_.distance = distance;

    pub.publish(msg_);
}