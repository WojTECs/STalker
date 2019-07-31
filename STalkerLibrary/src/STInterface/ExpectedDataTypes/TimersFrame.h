
#pragma once

#include "../ExpectedDataType.h"

namespace STInterface
{

namespace ExpectedDataTypes
{
class TimersFrame : public STInterface::ExpectedDataType
{
private:
public:
  TimersFrame();
  virtual ~TimersFrame();

  void deserialize(std::vector<uint8_t> iDataStream) override;
  void doTheProcessing() override;
};
}
}


