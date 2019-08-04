#pragma once

#include "../ExpectedDataType.h"

namespace Interface
{

namespace ExpectedDataTypes
{
class GPSFrame : public Interface::ExpectedDataType
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



