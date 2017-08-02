#include <QGuiApplication>
#include <QCursor>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QJsonArray>
#include <QCanBus>
#include <QCanBusDevice>
#include <QGeoPositionInfoSource>   // <-- Geo Positioning
#include "canframeid.h"
#include "e46canbusframe.h"
#include "can_utilities.h"
#include "track.h"
#include <iostream>

namespace {
    // Globals.
    QObject *object;
    QCanBusDevice *device;
    canUtils::canDeviceTypes canDeviceType = canUtils::E46_DEVICE;
}

// Reads JSON string from file into a document object.
QJsonDocument readJson(const QString &filePath);

// Creates Qt JSON object from document object.
QJsonObject toJsonObject(const QJsonDocument &jsonDoc, const QString &trackName);

// Sets the filters to the CAN bus device.
QCanBusDevice::Filter setCanFilter(const unsigned short &id);

// Selects the appropriate frame mapping function for the CAN bus device in use.
void selectFrameMap();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    // Hide mouse curser.
    QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));

    // Load gauge UI.
    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    object = component.create();

/***************************** Lap Timing and Geolocation functionality *****************************/

    // Read JSON document from file path.
    QJsonDocument jsonDoc = readJson(QCoreApplication::applicationDirPath() + QDir::separator() + "tracks.json");

    // Populate track list for combobox selection in GUI.
    QObject *comboBoxTracks = object->findChild<QObject*>("cboTracks");

    if (comboBoxTracks)
    {
        QStringList list = jsonDoc.object().keys();
        comboBoxTracks->setProperty("model", list);
        comboBoxTracks->setProperty("currentIndex", -1);
    }

    QString selectedTrack = comboBoxTracks->property("currentText").toString();

    // Create C++ JSON Object with item specified from the document.
    QJsonObject jsonObj = toJsonObject(jsonDoc, selectedTrack);

    // Create Track object containing all relevant racetrack information.
    Track track(jsonObj);

    if(track.trackFound()) {
        std::cout << "Track Found" << std::endl;
        std::cout << track.toString() << std::endl;
    }
    else {
        std::cout << "Track NOT Found" << std::endl;
        std::cout << track.toString() << std::endl;
    }

    /*QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(0);
    if(source)
        source->minimumUpdateInterval();

    QGeoPositionInfo gpi = source->lastKnownPosition();
    QGeoCoordinate gc = gpi.coordinate();

    std::cout << gc.toString().toStdString() << std::endl;
    std::cout << source->availableSources();*/

/************************************** CAN Bus functionality ***************************************/

    if(QCanBus::instance()->plugins().contains("socketcan"))
    {
        // Create CAN bus device and connect to can0 via SocketCAN plugin.
        device = QCanBus::instance()->createDevice("socketcan", "can0");

        device->connectDevice();

        // Set filters for needed data frames from the CAN bus device.
        if(device->state() == QCanBusDevice::ConnectedState)
        {
            object->setProperty("connStatus", "Connected");

            // Apply filters to CAN Bus device.
            QList<QCanBusDevice::Filter> filterList;

            filterList.append(setCanFilter(E46_ENGINE_RPM));
            //filterList.append(setCanFilter(E46_VEHICLE_SPEED));
            filterList.append(setCanFilter(E46_FUEL_LEVEL));
            filterList.append(setCanFilter(E46_COOLANT_TEMP));
            filterList.append(setCanFilter(E46_OIL_TEMP));

            device->setConfigurationParameter(QCanBusDevice::RawFilterKey, QVariant::fromValue(filterList));

            // Connect framesRecieved signal to slot function for reading frames.
            QObject::connect(device, &QCanBusDevice::framesReceived, selectFrameMap);
        }
    }

    return app.exec();
}


QJsonDocument readJson(const QString &filePath) {
    // Read JSON file to QString object.
    QJsonDocument jsonDoc;
    QString contents;
    QFile file(filePath);
    if(file.exists()) {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        contents = file.readAll();
        file.close();
    }
    else {
        jsonDoc = QJsonDocument();
        return jsonDoc;
    }

    // Create JSON document from QString.
    jsonDoc = QJsonDocument::fromJson(contents.toUtf8());

    return jsonDoc;
}

QJsonObject toJsonObject(const QJsonDocument &jsonDoc, const QString &trackName) {

    // Create JSON object from specified item (name of track).
    QJsonObject jsonObj;

    if(!jsonDoc.isEmpty())
        jsonObj = jsonDoc.object();
    else {
        jsonObj = QJsonObject();

        return jsonObj;
    }

    if(jsonObj.contains(trackName)) {
        jsonObj = jsonObj.value(trackName).toObject();
    }
    else {
        jsonObj = QJsonObject();
    }

    return jsonObj;
}

QCanBusDevice::Filter setCanFilter(const unsigned short &id)
{
    QCanBusDevice::Filter filter;

    filter.frameId = id;
    filter.frameIdMask = 0x7FFu; // Compare against all 11-bits of frame id.
    filter.format = QCanBusDevice::Filter::MatchBaseFormat;
    filter.type = QCanBusFrame::DataFrame;

    return filter;
}

void selectFrameMap()
{
    switch(canDeviceType)
    {
        case canUtils::OBD2_DEVICE:
            canUtils::mapObd2Frames(object, device);
            break;
        case canUtils::E46_DEVICE:
            canUtils::mapE46Frames(object, device);
            break;
    }
}
