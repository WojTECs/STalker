#include "GPSFrame.h"

#include <ros/console.h>

Interface::UpstreamData::GPSFrame::GPSFrame()
{
    protocolIndentificator = uint8_t{0x08};
    datasetBinarySize = 44;
    rosTopic = "GPSFrame";
}

void Interface::UpstreamData::GPSFrame::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{

    std_msgs::Float64MultiArray array;
    array.data.push_back(countOfSatelites);
    array.data.push_back(hdop.value);
    array.data.push_back(latitude.value);
    array.data.push_back(longitude.value);
    array.data.push_back(altitude.value);
    array.data.push_back(speed.value);
    array.data.push_back(infoAge);
    array.data.push_back(day);
    array.data.push_back(month);
    array.data.push_back(year);
    array.data.push_back(hour);
    array.data.push_back(minute);
    array.data.push_back(second);
    array.data.push_back(course.value);

    ROSClient.publishFloat64Array(array, rosTopic+"Extended");

    sensor_msgs::NavSatFix navSat;

    navSat.latitude = latitude.value;
    navSat.longitude = longitude.value;
    navSat.altitude = altitude.value;

     ROSClient.publishNavSatFix(navSat, rosTopic);

}

Interface::UpstreamData::GPSFrame::~GPSFrame()
{

}

void Interface::UpstreamData::GPSFrame::deserialize(const char *iDataStream, const int iDataSize)
{
    if(iDataSize % datasetBinarySize != 0)
    {
        ROS_ERROR("Bad GPS frame received. Length is mismatched.");
        return;
    }
    countOfSatelites = iDataStream[0];

    hdop.encoded[3] = iDataStream[1];
    hdop.encoded[2] = iDataStream[2];
    hdop.encoded[1] = iDataStream[3];
    hdop.encoded[0] = iDataStream[4];

    latitude.encoded[7] = iDataStream[5];
    latitude.encoded[6] = iDataStream[6];
    latitude.encoded[5] = iDataStream[7];
    latitude.encoded[4] = iDataStream[8];

    latitude.encoded[3] = iDataStream[9];
    latitude.encoded[2] = iDataStream[10];
    latitude.encoded[1] = iDataStream[11];
    latitude.encoded[0] = iDataStream[12];

    longitude.encoded[7] = iDataStream[13];
    longitude.encoded[6] = iDataStream[14];
    longitude.encoded[5] = iDataStream[15];
    longitude.encoded[4] = iDataStream[16];

    longitude.encoded[3] = iDataStream[17];
    longitude.encoded[2] = iDataStream[18];
    longitude.encoded[1] = iDataStream[19];
    longitude.encoded[0] = iDataStream[20];

    infoAge = (iDataStream[21]<<24) | (iDataStream[22]<<16) | (iDataStream[23]<<8) | (iDataStream[24] & 0xFF);
    day = iDataStream[25];
    month = iDataStream[26];
    year = (iDataStream[27]<<8) | (iDataStream[28] & 0xFF);

    hour = iDataStream[29];
    minute = iDataStream[30];
    second = iDataStream[31];

    altitude.encoded[3] = iDataStream[32];
    altitude.encoded[2] = iDataStream[33];
    altitude.encoded[1] = iDataStream[34];
    altitude.encoded[0] = iDataStream[35];

    course.encoded[3] = iDataStream[36];
    course.encoded[2] = iDataStream[37];
    course.encoded[1] = iDataStream[38];
    course.encoded[0] = iDataStream[39];

    speed.encoded[3] = iDataStream[40];
    speed.encoded[2] = iDataStream[41];
    speed.encoded[1] = iDataStream[42];
    speed.encoded[0] = iDataStream[43];

}

std::string Interface::UpstreamData::GPSFrame::serialize()
{
    boost::property_tree::ptree output;
    boost::property_tree::ptree GPSData;

    GPSData.put("countOfSatelites", countOfSatelites);
    GPSData.put("hdop", hdop.value);
    GPSData.put("latitude", latitude.value);
    GPSData.put("longitude", longitude.value);
    GPSData.put("infoAge", infoAge);
    GPSData.put("day",day);
    GPSData.put("month",month);
    GPSData.put("year",year);
    GPSData.put("hour",hour);
    GPSData.put("minute",minute);
    GPSData.put("second",second);
    GPSData.put("altitude",altitude.value);
    GPSData.put("course",course.value);
    GPSData.put("speed",speed.value);


    output.add_child("GPSFrame", GPSData);

    std::ostringstream pTreeToStringCatalizator;
    boost::property_tree::json_parser::write_json(pTreeToStringCatalizator, output);
    return pTreeToStringCatalizator.str();

}

void Interface::UpstreamData::GPSFrame::doTheProcessing()
{

}

std::unique_ptr<Interface::UpstreamDataType> Interface::UpstreamData::GPSFrame::getClone()
{
    std::unique_ptr<Interface::UpstreamData::GPSFrame>gpsFrame(new Interface::UpstreamData::GPSFrame);

    gpsFrame->protocolIndentificator = protocolIndentificator;
    gpsFrame->datasetBinarySize = datasetBinarySize;
    gpsFrame->rosTopic = rosTopic;

    return std::move(gpsFrame);

}
