#pragma once

#include "../ExpectedDataType.h"

namespace STInterface
{

namespace ExpectedDataTypes
{
class GyroscopeFrame : public STInterface::ExpectedDataType
{
private:
public:
  GyroscopeFrame();
  virtual ~GyroscopeFrame();

  void deserialize(std::vector<uint8_t> iDataStream) override;
  void doTheProcessing() override;
};
}
}



