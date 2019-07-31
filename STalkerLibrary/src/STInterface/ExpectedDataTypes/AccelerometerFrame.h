#pragma once

#include "../ExpectedDataType.h"

namespace STInterface
{

namespace ExpectedDataTypes
{
class AccelerometerFrame : public STInterface::ExpectedDataType
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



