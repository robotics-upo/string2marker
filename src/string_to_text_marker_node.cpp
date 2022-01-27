#include <ros/ros.h>
#include <std_msgs/String.h>
#include <visualization_msgs/Marker.h>

visualization_msgs::Marker marker;
ros::Publisher marker_pub;
void stringCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO_ONCE("[string2marker] Received first input string: %s", msg->data.c_str());
    marker.text = msg->data;
    marker_pub.publish(marker);
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, ros::this_node::getName());
    ros::NodeHandle n;
    ros::NodeHandle n_private("~");
    ros::Subscriber sub = n.subscribe("input_string", 1000, stringCallback);
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Read params
    double marker_size = n_private.param("marker_size", 1.0);
    double marker_pos_x = n_private.param("marker_pos_x", 0.0);
    double marker_pos_y = n_private.param("marker_pos_y", 0.0);
    double marker_pos_z = n_private.param("marker_pos_z", 0.0);
    double marker_color_r = n_private.param("marker_color_r", 0.0);
    double marker_color_g = n_private.param("marker_color_g", 1.0);
    double marker_color_b = n_private.param("marker_color_b", 0.0);
    double marker_color_a = n_private.param("marker_color_a", 1.0);

    // Pre-define marker
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "string2marker";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    marker.text = "Unknown";
    marker.action = visualization_msgs::Marker::MODIFY;

    marker.pose.position.x = marker_pos_x;
    marker.pose.position.y = marker_pos_y;
    marker.pose.position.z = marker_pos_z;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = marker_size;
    marker.scale.y = marker_size;
    marker.scale.z = marker_size;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = marker_color_r;
    marker.color.g = marker_color_g;
    marker.color.b = marker_color_b;
    marker.color.a = marker_color_a;

    marker.lifetime = ros::Duration();

    ROS_INFO("Ready to publish the incoming text from input_string topic as text markers...");

    ros::spin();
}