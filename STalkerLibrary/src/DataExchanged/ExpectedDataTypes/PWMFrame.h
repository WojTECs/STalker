#pragma once

#include "../ExpectedDataType.h"

namespace Interface
{

namespace ExpectedDataTypes
{
class PWMFrame : public Interface::ExpectedDataType
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


