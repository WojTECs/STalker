#include "UpstreamDataType.h"

void Interface::UpstreamDataType::sendData(ROSInterface::ROSInterfaceClient &ROSClient)
{
    ROSClient.test(2);
}
