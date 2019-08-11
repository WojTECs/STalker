#include "MainConfigurationFrame.h"

#include <boost/exception/diagnostic_information.hpp>

Interface::DownstreamData::MainConfigurationFrame::MainConfigurationFrame()
{
    mProtocolIndentificator = "MainConfigurationFrame";
}

Interface::DownstreamData::MainConfigurationFrame::~MainConfigurationFrame()
{
    //#TODO implement
}

std::vector<uint8_t> Interface::DownstreamData::MainConfigurationFrame::serialize()
{

}

void Interface::DownstreamData::MainConfigurationFrame::deserialize(boost::property_tree::ptree& pt)
{

}

void Interface::DownstreamData::MainConfigurationFrame::doTheProcessing()
{

}


