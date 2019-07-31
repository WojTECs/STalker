#pragma once

#include "../ExpectedDataType.h"

namespace STInterface
{

namespace ExpectedDataTypes
{
class EncoderFrame : public STInterface::ExpectedDataType
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



