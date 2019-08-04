#pragma once

#include "../ExpectedDataType.h"

namespace Interface
{

namespace ExpectedDataTypes
{
class AccelerometerFrame : public Interface::ExpectedDataType
{
private:
public:
  AccelerometerFrame();
  virtual ~AccelerometerFrame();

  void deserialize(std::vector<uint8_t> iDataStream) override;
  void doTheProcessing() override;
};
}
}



