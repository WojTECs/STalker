#pragma once

#include "../DataToSend.h"

namespace Interface
{

namespace DatasToSend
{
class IMUFrame : public Interface::DataToSend
{
private:
public:
  IMUFrame();
  virtual ~IMUFrame();
};
}
}





