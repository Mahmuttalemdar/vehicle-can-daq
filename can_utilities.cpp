#include "can_utilities.h"
#include <QQmlComponent>
#include <QQmlApplicationEngine>

namespace canUtils {

    void mapObd2Frames(QObject *object, QCanBusDevice *device)
    {
        // Read frames.
        while(device->framesAvailable() > 0)
        {
            object->setProperty("canFilter", "Yes");
            object->setProperty("frames", device->framesAvailable());

            // TODO: Create obd2 frame class.
//            Obd2CanBusFrame canFrame(device->readFrame());

//            if(canFrame.isValid())
//            {
//                switch(canFrame.frameId())
//                {
//                    case OBD2_ENGINE_RPM:
//                        object->setProperty("rpmValue", canFrame.decodeEngineRpm());
//                        break;
//                    case OBD2_VEHICLE_SPEED:
//                        object->setProperty("speedValue", canFrame.decodeVehicleSpeed());
//                        break;
//                    case OBD2_FUEL_LEVEL:
//                        object->setProperty("fuelValue", canFrame.decodeFuelLevel());
//                        break;
//                    case OBD2_COOLANT_TEMP:
//                        object->setProperty("coolantValue", canFrame.decodeCoolantTempC());
//                        break;
//                    case OBD2_OIL_TEMP:
//                        object->setProperty("oilValue", canFrame.decodeOilTempC());
//                        break;
//                    default:
//                        break;
//                }
//            }
        }
    }

    void mapE46Frames(QObject *object, QCanBusDevice *device)
    {
        // Read frames.
        while(device->framesAvailable() > 0)
        {
            object->setProperty("canFilter", "Yes");
            object->setProperty("frames", device->framesAvailable());

            E46CanBusFrame canFrame(device->readFrame());

            if(canFrame.isValid())
            {
                switch(canFrame.frameId())
                {
                    case E46_ENGINE_RPM:
                        object->setProperty("rpmValue", canFrame.decodeEngineRpm());
                        break;
                    /*case VEHICLE_SPEED:
                        object->setProperty("speedValue", canFrame.decodeVehicleSpeed());
                        break;*/
                    case E46_FUEL_LEVEL:
                        object->setProperty("fuelValue", canFrame.decodeFuelLevel());
                        break;
                    case E46_COOLANT_TEMP:
                        object->setProperty("coolantValue", canFrame.decodeCoolantTempC());
                        break;
                    case E46_OIL_TEMP:
                        object->setProperty("oilValue", canFrame.decodeOilTempC());
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
