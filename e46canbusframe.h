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

        unsigned int decodeEngineRpm()    const;
        unsigned int decodeVehicleSpeed() const;
        uint8_t      decodeFuelLevel()    const;

        int decodeCoolantTempC() const;
        int decodeCoolantTempF() const;
        int decodeOilTempC()     const;
        int decodeOilTempF()     const;

        unsigned int decodeServiceLights() const;
};

#endif // E46CANBUSFRAME_H
