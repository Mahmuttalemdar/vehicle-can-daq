#include "e46canbusframe.h"
#include "canframeid.h"

E46CanBusFrame::E46CanBusFrame()
{

}

E46CanBusFrame::E46CanBusFrame(QCanBusFrame frame)
:
    QCanBusFrame(frame)
{}

E46CanBusFrame::E46CanBusFrame(FrameType type = DataFrame)
:
    QCanBusFrame(type)
{}

E46CanBusFrame::E46CanBusFrame(quint32 identifier, const QByteArray &data)
:
    QCanBusFrame(identifier, data)
{}

unsigned int E46CanBusFrame::decodeEngineRpm() const
{
//    Unit: RPM
//    CAN Id: 0x316 (790)
//    Conversion: ((byte3 * 256) + byte2) / 6.4

    unsigned int rpm = 0;

    if(frameId() == E46_ENGINE_RPM)
    {
        const QByteArray &PAYLOAD = this->payload();
        const uint8_t    BYTE2    = static_cast<uint8_t>(PAYLOAD[2]);
        const uint8_t    BYTE3    = static_cast<uint8_t>(PAYLOAD[3]);

        rpm = ((BYTE3 << 8) ^ BYTE2) / 6.4;
    }

    return rpm;
}

unsigned int E46CanBusFrame::decodeVehicleSpeed() const
{
//    Unit: MPH
//    CAN Id: 0x153 (339)
//    Conversion: ((byte3 * 256) + byte2) * 0.0776714;

//    if(frameId() != E46_VEHICLE_SPEED)
//        return 0;

//    unsigned int speed;
//    const QByteArray &payload = this->payload();

//    speed = payload[2];

//    return speed;

    return 0;
}

uint8_t E46CanBusFrame::decodeFuelLevel() const
{
//    Unit: Liters -> Percent (%)
//    CAN Id: 0x613 (1555)
//    Conversion: byte2
//    Note: byte2 is fuel level. Full being hex 39. Fuel light comes on at hex 8.

    const float FUEL_CAPACITY = 57.0;

    uint8_t fuelLevel = 0;

    if(frameId() == E46_FUEL_LEVEL)
    {
        const QByteArray &PAYLOAD = this->payload();
        const uint8_t    BYTE2    = static_cast<uint8_t>(PAYLOAD[2]);

        fuelLevel = (BYTE2 / FUEL_CAPACITY) * 100;
    }

    return fuelLevel;
}

int E46CanBusFrame::decodeCoolantTempC() const
{
//    Unit: C
//    CAN Id: 0x329 (809)
//    Conversion: (byte1 * 0.75) - 48.373

    int temp = 0;

    if(frameId() == E46_COOLANT_TEMP)
    {
        const QByteArray &PAYLOAD = this->payload();
        const uint8_t    BYTE1    = static_cast<uint8_t>(PAYLOAD[1]);

        temp = (BYTE1 * 0.75) - 48.373;
    }

    return temp;
}

int E46CanBusFrame::decodeCoolantTempF() const
{
//    Unit: C
//    CAN Id: 0x329 (809)
//    Conversion: (decodeCoolantTempC * 1.8) + 32

    return decodeCoolantTempC() * 1.8 + 32;
}

int E46CanBusFrame::decodeOilTempC() const
{
//    Unit: C
//    CAN Id: 0x545 (1349)
//    Conversion: byte4 - 48.373

    int temp = 0;

    if(frameId() == E46_OIL_TEMP)
    {
        const QByteArray &PAYLOAD = this->payload();
        const uint8_t    BYTE4    = static_cast<uint8_t>(PAYLOAD[4]);

        temp = BYTE4 - 48.373;
    }

    return temp;
}

int E46CanBusFrame::decodeOilTempF() const
{
    /*
    Unit: C
    CAN Id: 0x545 (1349)
    Conversion: (decodeOilTempC * 1.8) + 32
    */

    return decodeOilTempC() * 1.8 + 32;
}
