#pragma once

#include "../src/STInterface/STInterfaceClientUDP.h"
#include "../src/ROSInterface/ROSInterfaceClient.h"

#include "../src/DataExchanged/DownstreamData/IMUFrame.h"
#include "../src/DataExchanged/DownstreamData/MainConfigurationFrame.h"
#include "../src/DataExchanged/DownstreamData/MovementOrderTurnPropulsionFrame.h"
#include "../src/DataExchanged/DownstreamData/MovementOrderLeftRightFrame.h"
#include "../src/DataExchanged/DownstreamData/TimerConfigurationFrame.h"

#include "../src/DataExchanged/UpstreamDataType.h"
#include "../src/DataExchanged/UpstreamData/AccelerometerFrame.h"
#include "../src/DataExchanged/UpstreamData/ContinentalLIDARDistanceFrame.h"
#include "../src/DataExchanged/UpstreamData/ContinentalLIDARReflectionFrame.h"
#include "../src/DataExchanged/UpstreamData/ContinentalLIDARSpeedFrame.h"
#include "../src/DataExchanged/UpstreamData/EncoderFrame.h"
#include "../src/DataExchanged/UpstreamData/GPSFrame.h"
#include "../src/DataExchanged/UpstreamData/GyroscopeFrame.h"
#include "../src/DataExchanged/UpstreamData/LidarFrame.h"
#include "../src/DataExchanged/UpstreamData/MagnetometerFrame.h"
#include "../src/DataExchanged/UpstreamData/MovementInformationTurnPropulsionFrame.h"
#include "../src/DataExchanged/UpstreamData/MovementInformationLeftRightFrame.h"
#include "../src/DataExchanged/UpstreamData/PackageStatisticsFrame.h"
#include "../src/DataExchanged/UpstreamData/RFIDFrame.h"
#include "../src/DataExchanged/UpstreamData/ServiceTimeFrame.h"
#include "../src/DataExchanged/UpstreamData/TimersFrame.h"
#include "../src/DataExchanged/UpstreamData/TimeSyncFrame.h"
