#pragma once

#include "../ExpectedDataType.h"

namespace Interface
{

namespace ExpectedDataTypes
{
class GyroscopeFrame : public Interface::ExpectedDataType
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



