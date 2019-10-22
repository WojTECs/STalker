#pragma once

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{
class EncoderFrame : public Interface::UpstreamDataType
{
private:

    int leftSideSpinCount;
    int rightSideSpinCount;

public:

    EncoderFrame();
    virtual ~EncoderFrame();

    void deserialize(std::vector<uint8_t> iDataStream) override;
    boost::property_tree::ptree serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}



