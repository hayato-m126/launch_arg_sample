// Copyright 2014 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "launch_arg_sample/listener_component.hpp"

#include <string>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "std_msgs/msg/string.hpp"

namespace launch_arg_sample
{
// Create a Listener class that subclasses the generic rclcpp::Node base class.
// The main function below will instantiate the class as a ROS node.
class Listener : public rclcpp::Node
{
public:
  LAUCH_ARG_SAMPLE_LISTENER_COMPONENT_PUBLIC
  explicit Listener(const rclcpp::NodeOptions & options) : Node("listener", options)
  {
    this->declare_parameter("compare_str", "test");
    this->get_parameter("compare_str", compare_str_);
    sub_ = create_subscription<std_msgs::msg::String>(
      "chatter", 1, std::bind(&Listener::chatterCallback, this, std::placeholders::_1));
  }

  void chatterCallback(const std_msgs::msg::String::SharedPtr msg)
  {
    if (msg->data.find(compare_str_) == 0) {
      RCLCPP_INFO_STREAM(get_logger(), msg->data << " starts with " << compare_str_);
    } else {
      RCLCPP_WARN_STREAM(get_logger(), msg->data << " does not start with " << compare_str_);
    }
  }

private:
  std::string compare_str_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

}  // namespace launch_arg_sample

RCLCPP_COMPONENTS_REGISTER_NODE(launch_arg_sample::Listener)
