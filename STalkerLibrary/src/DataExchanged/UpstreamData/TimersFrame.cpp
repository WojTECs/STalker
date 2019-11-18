#include "TimersFrame.h"

Interface::UpstreamData::TimersFrame::TimersFrame()
{
    protocolIndentificator = uint8_t{0x03};
    datasetBinarySize = 0;//Unknown yet therefore can't be implemented
    rosTopic = "TimersFrame";
}

Interface::UpstreamData::TimersFrame::~TimersFrame()
{

}

void Interface::UpstreamData::TimersFrame::deserialize(const char *iDataStream, const int iDataSize)
{

}

std::string Interface::UpstreamData::TimersFrame::serialize()
{

}

void Interface::UpstreamData::TimersFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::TimersFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::TimersFrame>timersFrame(new Interface::UpstreamData::TimersFrame);

    timersFrame->protocolIndentificator = protocolIndentificator;
    timersFrame->datasetBinarySize = datasetBinarySize;
    timersFrame->rosTopic = rosTopic;

    return std::move(timersFrame);
}

