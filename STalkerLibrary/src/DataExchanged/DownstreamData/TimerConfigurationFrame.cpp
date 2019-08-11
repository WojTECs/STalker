#include "TimerConfigurationFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>


Interface::DownstreamData::TimerConfigurationFrame::TimerConfigurationFrame()
{
    potocolIndentificator = "TimerConfigurationFrame";
}

Interface::DownstreamData::TimerConfigurationFrame::~TimerConfigurationFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::TimerConfigurationFrame::serialize()
{
    std::vector<uint8_t> output(5);

    output[0] = 0x06;//ID
    output[1] = timerID;
    output[2] = prescalerValue;
    output[3] = counterValue;
    output[4] = clockDivider;

    return output;
}

void Interface::DownstreamData::TimerConfigurationFrame::deserialize(boost::property_tree::ptree& pt)
{

    try
    {
        timerID = pt.get<int>("TimerConfigurationFrame.TimerID");
        prescalerValue = pt.get<int>("IMUFrame.PrescallerValue");
        counterValue = pt.get<int>("IMUFrame.CounterValue");
        clockDivider = pt.get<int>("IMUFrame.ClockDividerValue");
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        ROS_ERROR("Bad Timer frame received. Boost says: %s", diag.c_str());
    }
}

void Interface::DownstreamData::TimerConfigurationFrame::doTheProcessing()
{

}


