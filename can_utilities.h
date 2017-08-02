#ifndef CAN_UTILITIES_H
#define CAN_UTILITIES_H

#include <QCanBusDevice>
#include "e46canbusframe.h"
#include "canframeid.h"

namespace canUtils {

    enum canDeviceTypes {
        OBD2_DEVICE = 0,
        E46_DEVICE =  1
    };

    // FRAME FILTERS

    // Checks the validity of recieved CAN frames with the OBD2 protocol
    // and maps them to the approppriate UI element.
    void mapObd2Frames(QObject *object, QCanBusDevice *device);

    // Checks the validity of recieved CAN frames with the BMW E46 protocol
    // and maps them to the approppriate UI element.
    void mapE46Frames(QObject *object, QCanBusDevice *device);
}

#endif // CAN_UTILITIES_H
