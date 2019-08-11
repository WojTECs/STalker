#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData
{

class TimerConfigurationFrame : public Interface::DownstreamDataType
{
private:

    int timerID;
    int prescalerValue;
    int counterValue;
    int clockDivider;

public:

//#TODO add consts
    //#TODO check empty //# in case i forgot to write todo
  TimerConfigurationFrame();
  virtual ~TimerConfigurationFrame();

  std::vector<uint8_t> serialize();
   void deserialize(boost::property_tree::ptree& pt);
   void doTheProcessing();
};
}
}




