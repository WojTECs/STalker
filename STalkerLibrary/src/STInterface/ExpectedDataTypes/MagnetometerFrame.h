#pragma once

#include "../ExpectedDataType.h"

namespace STInterface
{

namespace ExpectedDataTypes
{
class MagnetometerFrame : public STInterface::ExpectedDataType
{
private:
public:
  MagnetometerFrame();
  virtual ~MagnetometerFrame();

  void deserialize(std::vector<uint8_t> iDataStream) override;
  void doTheProcessing() override;
};
}
}



