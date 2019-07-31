#pragma once

#include "../ExpectedDataType.h"

namespace STInterface
{

namespace ExpectedDataTypes
{
class GPSFrame : public STInterface::ExpectedDataType
{
private:
public:
  GPSFrame();
  virtual ~GPSFrame();

  void deserialize(std::vector<uint8_t> iDataStream) override;
  void doTheProcessing() override;
};
}
}



