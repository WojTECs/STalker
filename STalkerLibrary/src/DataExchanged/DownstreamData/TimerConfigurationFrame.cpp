#include "TimerConfigurationFrame.h"

#include <boost/exception/diagnostic_information.hpp>
#include <ros/console.h>


Interface::DownstreamData::TimerConfigurationFrame::TimerConfigurationFrame()
{
    potocolIndentificator = "TimerConfigurationFrame";
    stIdentifier = 0x03;
}

Interface::DownstreamData::TimerConfigurationFrame::~TimerConfigurationFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::TimerConfigurationFrame::serialize()
{
    std::vector<uint8_t> output(7);

    output[0] = stIdentifier;
    output[1] = timerID;
    output[2] = prescalerValue >> 8;
    output[3] = prescalerValue & 0xFF;
    output[4] = counterValue >> 8;
    output[5] = counterValue & 0xFF;
    output[6] = clockDivider;

    return output;
}

void Interface::DownstreamData::TimerConfigurationFrame::deserialize(const uint16_t *msgArray, uint16_t arraySize)
{
//    try
//    {
//        timerID = pt.get<int>("TimerConfigurationFrame.TimerID");
//        prescalerValue = pt.get<int>("TimerConfigurationFrame.PrescallerValue");
//        counterValue = pt.get<int>("TimerConfigurationFrame.CounterValue");
//        clockDivider = pt.get<int>("TimerConfigurationFrame.ClockDividerValue");
//    }
//    catch (const boost::exception& e)
//    {
//        std::string diag = diagnostic_information(e);
//        ROS_ERROR("Bad Timer frame received. Boost says: %s", diag.c_str());
//    }

    timerID = msgArray[0];
    prescalerValue = msgArray[1];
    counterValue = msgArray[2];
    clockDivider = msgArray[3];
}

void Interface::DownstreamData::TimerConfigurationFrame::doTheProcessing()
{

}


