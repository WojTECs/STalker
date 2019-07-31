#pragma once

#include <memory>

namespace STInterface{

class DataToSend
{
private:
protected:
  uint8_t mProtocolIndentificator;

public:
    const std::shared_ptr<uint8_t> serialize();
    virtual ~DataToSend(){}
};

} //namespace STInterface
