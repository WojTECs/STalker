#pragma once

#include "../UpstreamDataType.h"
namespace Interface
{

namespace UpstreamData
{
class PWMFrame : public Interface::UpstreamDataType
{
private:
    bool movementDirection;
    int leftSidePWM;
    int rightSidePWM;

public:
  PWMFrame();
  virtual ~PWMFrame();

  void deserialize(std::vector<uint8_t> iDataStream) override;
  boost::property_tree::ptree serialize() override;
  void doTheProcessing() override;
};
}
}


