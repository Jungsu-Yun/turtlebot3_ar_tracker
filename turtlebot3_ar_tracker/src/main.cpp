#include <ros/ros.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <ar_track_alvar_msgs/AlvarMarker.h>
#include <turtlebot3_ar_msgs/msg.h>
#include <stdio.h>
#include <std_msgs/String.h>

double lastback;
int backcount = 10;

double forward;
double left;
double up;
double distance;

double offset_x = 0;
double offset_y = 0;
double offset_z = 0;

ros::Publisher msg_pub;

void ar_marker_callback(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg)
{
    if(msg->markers.empty())
    {
        if(ros::Time::now().toSec() - lastback > 0.5 && backcount < 6)
        {
            forward = left = up = distance = 0;
            ROS_INFO("BACKING UP!");

            lastback = ros::Time::now().toSec();
            backcount ++;
        }
        return;
    }

    backcount = 0;

    ar_track_alvar_msgs::AlvarMarker marker = msg->markers.at(0);
    geometry_msgs::Pose pose;
    pose = marker.pose.pose;

    forward = pose.position.z - offset_z;
    left = -(pose.position.x - offset_x);
    up = -(pose.position.y - offset_y);
    distance = sqrt(forward*forward+left*left+up*up);

    turtlebot3_ar_msgs::msg msg_;
    msg_.foward = forward;
    msg_.left = left;
    msg_.distance = distance;
    msg_.up = up;

    msg_pub.publish(msg_);
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "turtlebot3_ar_tracker");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("ar_pose_marker", 1, ar_marker_callback);

    try
    {
        ros::spin();
    }
    catch(...)
    {
        ROS_ERROR("--- ERROR IN spin(), shutting down! ---");
        ros::shutdown();
    }

    return 0;
}