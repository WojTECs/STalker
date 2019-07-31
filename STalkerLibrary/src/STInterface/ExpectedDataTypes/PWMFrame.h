#pragma once

#include "../ExpectedDataType.h"

namespace STInterface
{

namespace ExpectedDataTypes
{
class PWMFrame : public STInterface::ExpectedDataType
{
private:
public:
  PWMFrame();
  virtual ~PWMFrame();

  void deserialize(std::vector<uint8_t> iDataStream) override;
  void doTheProcessing() override;
};
}
}


