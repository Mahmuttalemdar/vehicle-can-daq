#ifndef E46CANBUSFRAME_H
#define E46CANBUSFRAME_H

#include <QCanBusFrame>

class E46CanBusFrame : public QCanBusFrame
{
    public:
        E46CanBusFrame();
        E46CanBusFrame(QCanBusFrame frame);
        E46CanBusFrame(FrameType);
        E46CanBusFrame(quint32, const QByteArray&);

        uint_fast8_t decodeEngineRpm() const;
        uint_fast8_t decodeVehicleSpeed() const;
        uint_fast8_t decodeFuelLevel() const;

        int_fast8_t decodeCoolantTempC() const;
        int_fast8_t decodeCoolantTempF() const;
        int_fast8_t decodeOilTempC() const;
        int_fast8_t decodeOilTempF() const;

        unsigned short decodeServiceLights() const;
};

#endif // E46CANBUSFRAME_H
