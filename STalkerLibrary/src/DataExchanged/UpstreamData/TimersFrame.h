#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../UpstreamDataType.h"

namespace Interface
{

namespace UpstreamData
{
class TimersFrame : public Interface::UpstreamDataType
{
private:

    int16_t reg_psc_imu;
    int16_t reg_arr_imu;
    int32_t freq_imu;
    int16_t data_psc;
    int16_t data_arr;
    int8_t  reg_clk_div_data_send;//hell knows what all of that means :> Good luck!
    int32_t freq_data_send;
public:

    TimersFrame();
    virtual ~TimersFrame();

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;
    void deserialize(const char* iDataStream, const int iDataSize) override;
    std::string serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}


