#pragma once

#include "../ExpectedDataType.h"

namespace Interface
{

namespace ExpectedDataTypes
{
class MagnetometerFrame : public Interface::ExpectedDataType
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



