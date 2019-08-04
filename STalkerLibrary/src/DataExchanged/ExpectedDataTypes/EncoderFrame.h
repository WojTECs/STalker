#pragma once

#include "../ExpectedDataType.h"

namespace Interface
{

namespace ExpectedDataTypes
{
class EncoderFrame : public Interface::ExpectedDataType
{
private:
public:
  EncoderFrame();
  virtual ~EncoderFrame();

  void deserialize(std::vector<uint8_t> iDataStream) override;
  void doTheProcessing() override;
};
}
}



