#pragma once

#include "../DownstreamDataType.h"

namespace Interface
{
namespace DownstreamData
{

class MainConfigurationFrame : public Interface::DownstreamDataType
{
private:
public:

  MainConfigurationFrame();
  virtual ~MainConfigurationFrame();

  std::vector<uint8_t> serialize();
void deserialize(boost::property_tree::ptree& pt);
void doTheProcessing();
};
}
}





