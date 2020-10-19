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

    uint16_t reg_psc_imu;
    uint16_t reg_arr_imu;
    uint8_t reg_clk_div_imu;
    uint32_t freq_imu;
    uint16_t data_psc;
    uint16_t data_arr;
    uint8_t  reg_clk_div_data_send;//hell knows what all of that means :> Good luck!
    uint32_t freq_data_send;
public:

    TimersFrame();
    virtual ~TimersFrame();

    void sendData(ROSInterface::ROSInterfaceClient& ROSClient) override;
    void deserialize(const uint8_t* iDataStream, const int iDataSize) override;
    std::string serialize() override;
    void doTheProcessing() override;
    std::unique_ptr<Interface::UpstreamDataType> getClone();

};
}
}


