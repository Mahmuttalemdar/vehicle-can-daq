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

uint_fast8_t E46CanBusFrame::decodeEngineRpm() const
{
    /*
    Unit: RPM
    CAN Id: 0x316 (790)
    Conversion: ((bit4 * 256) + bit3) / 6.4
    */

    if(frameId() != E46_ENGINE_RPM)
        return 0;

    uint_fast8_t bit3, bit4, rpm;
    const QByteArray &payload = this->payload();

    bit3 = payload[2];
    bit4 = payload[3];
    rpm = ((bit4 << 8) ^ bit3) / 6.4;

    return rpm;
}

uint_fast8_t E46CanBusFrame::decodeVehicleSpeed() const
{
    /*
    Unit: MPH
    CAN Id: 0x153 (339)
    Conversion: ((bit3 * 256) + bit2) * 0.0776714;
    */

    if(frameId() != E46_VEHICLE_SPEED)
        return 0;

    uint_fast8_t speed;
    const QByteArray &payload = this->payload();

    speed = payload[2];

    return speed;
}

uint_fast8_t E46CanBusFrame::decodeFuelLevel() const
{
    /*
    Unit: Liters -> Percent (%)
    CAN Id: 0x613 (1555)
    Conversion: bit3
    Note: bit3 is fuel level. Full being hex 39. Fuel light comes on at hex 8.
    */

    if(frameId() != E46_FUEL_LEVEL)
        return 0;

    uint_fast8_t bit3, fuelLevel;
    const float fuelCapacity = 57.0; //62.83784;
    const QByteArray &payload = this->payload();

    bit3 = payload[2];
    fuelLevel = (bit3 / fuelCapacity) * 100;

    return fuelLevel;
}

int_fast8_t E46CanBusFrame::decodeCoolantTempC() const
{
    /*
    Unit: C
    CAN Id: 0x329 (809)
    Conversion: (bit2 * 0.75) - 48.373
    */

    if(frameId() != E46_COOLANT_TEMP)
        return 0;

    int_fast8_t bit2, temp;
    const QByteArray &payload = this->payload();

    bit2 = payload[1];
    temp = (bit2 * 0.75) - 48.373;

    return temp;
}

int_fast8_t E46CanBusFrame::decodeCoolantTempF() const
{
    /*
    Unit: C
    CAN Id: 0x329 (809)
    Conversion: (decodeCoolantTempC * 1.8) + 32
    */

    return decodeCoolantTempC() * 1.8 + 32;
}

int_fast8_t E46CanBusFrame::decodeOilTempC() const
{
    /*
    Unit: C
    CAN Id: 0x545 (1349)
    Conversion: bit5 - 48.373
    */

    if(frameId() != E46_OIL_TEMP)
        return 0;

    int_fast8_t bit5, temp;
    const QByteArray &payload = this->payload();

    bit5 = payload[4];
    temp = bit5 - 48.373;

    return temp;
}

int_fast8_t E46CanBusFrame::decodeOilTempF() const
{
    /*
    Unit: C
    CAN Id: 0x545 (1349)
    Conversion: (decodeOilTempC * 1.8) + 32
    */

    return decodeOilTempC() * 1.8 + 32;
}
