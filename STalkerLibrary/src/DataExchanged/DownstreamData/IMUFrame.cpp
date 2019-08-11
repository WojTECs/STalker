#include "IMUFrame.h"

#include <boost/exception/diagnostic_information.hpp>

//#TODO sort includes
Interface::DownstreamData::IMUFrame::IMUFrame()
{
    mProtocolIndentificator = "IMUFrame";
}

Interface::DownstreamData::IMUFrame::~IMUFrame()
{

}

std::vector<uint8_t> Interface::DownstreamData::IMUFrame::serialize()
{
    std::vector<uint8_t> output(3);


    output[0] = 0x08;//ID
    output[1] = registryAddress;
    output[2] = registryValue;

    return output;
}

void Interface::DownstreamData::IMUFrame::deserialize(boost::property_tree::ptree& pt)
{
    try
    {
        registryAddress = pt.get<int>("IMUFrame.RegistryAddress");
        registryValue = pt.get<int>("IMUFrame.RegistryValue");
    }
    catch (const boost::exception& e)
    {
        std::string diag = diagnostic_information(e);
        //#TODO bad frame

    }

}

void Interface::DownstreamData::IMUFrame::doTheProcessing()
{

}


