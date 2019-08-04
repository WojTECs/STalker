
#pragma once

#include "../ExpectedDataType.h"

namespace Interface
{

namespace ExpectedDataTypes
{
class TimersFrame : public Interface::ExpectedDataType
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


