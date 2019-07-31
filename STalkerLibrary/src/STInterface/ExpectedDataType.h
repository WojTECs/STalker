#pragma once

#include<iostream>
#include<vector>

namespace STInterface
{

class ExpectedDataType
{

private:
protected:
  uint8_t mProtocolIndentificator;
  std::size_t mSTBinarySize;
public:

    uint8_t getProtocolIdentificator() const{ return mProtocolIndentificator;}
    std::size_t getSTBinarySize() const{ return mSTBinarySize;}

    virtual void deserialize(std::vector<uint8_t> iDataStream)=0;
    virtual void doTheProcessing()=0;

    virtual ~ExpectedDataType(){}
};

} //namespace STInterface
