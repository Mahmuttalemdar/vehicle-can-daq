import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Extras 1.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "ColorFormatter.js" as CF


Window {
    property int rpmValue
    property int speedValue
    property int fuelValue
    property int coolantValue
    property int oilValue

    // Test fields for connectivity and values.
    property string connStatus: "Not Connected"
    property int frames: 0
    property string canFilter: "No"

    id: root
    visible: true
    width: 800
    height: 480
    title: "Linear Cluster"
    color: "#000"

    Item {
        id: container
        x: 0
        y: 0
        width: 800
        height: Math.min(root.width, root.height)
        visible: true
        z: 0
        rotation: 0
        scale: 1
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent

        Gauge {
            id: tachGauge
            x: -17
            style: TachGaugeStyle {}
            width: 833
            height: 50
            anchors.topMargin: 0
            minimumValue: 0
            maximumValue: 9000
            tickmarkStepSize: 75
            value: rpmValue
            orientation: Qt.Horizontal
            anchors.top: parent.top
        }

        Text {
            id: txtRPM
            x: 702
            y: 78
            width: 98
            height: 46
            color: CF.getTachColor(tachGauge.value)
            text: Math.ceil(tachGauge.value) + '<font size="1"> RPM</font>'
            styleColor: "#000"
            style: Text.Normal
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
            font.pixelSize: 36
        }

/****************** FUEL GAUGE ******************/

        Gauge {
            id: fuelGauge
            x: 0
            y: 441
            width: 185
            style: FuelGaugeStyle {}
            height: 7
            anchors.verticalCenterOffset: 220
            minimumValue: 0
            maximumValue: 100
            tickmarkStepSize: 25
            value: fuelValue
            orientation: Qt.Horizontal
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            id: rectFuel
            x: fuelGauge.x + 13
            y: fuelGauge.y + 11
            width: Math.ceil(fuelGauge.width) / 4 - 25
            height: fuelGauge.height
            color: "#ff311a" // red
        }

        Image {
            id: imgFuel
            x: fuelGauge.x + (width / 2)
            y: fuelGauge.y - height - 4
            width: 28
            height: 25
            source: "../images/fuel_icon.png"
        }

        Text {
            id: txtFuel
            x: 115
            y: 424
            width: 76
            height: 32
            color: fuelGauge.value <= 20 ? "#ff0000" : "#fff"
            text: Math.ceil(fuelGauge.value) + '<font size="1">%</font>'
            style: Text.Normal
            verticalAlignment: Text.AlignTop
            styleColor: "#000000"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 28
        }

/****************** COOLANT TEMP GAUGE ******************/

        Gauge {
            id: coolantTempGauge
            x: 607
            y: 420
            width: 185
            style: CoolantTempGaugeStyle {}
            height: 7
            anchors.verticalCenterOffset: 153
            minimumValue: 50
            maximumValue: 140
            tickmarkStepSize: (maximumValue - minimumValue) / 4
            value: coolantValue
            orientation: Qt.Horizontal
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            id: rectCoolantTempLow
            x: coolantTempGauge.x + 13
            y: coolantTempGauge.y + 11
            width: Math.ceil(coolantTempGauge.width) / 4 - 25
            height: coolantTempGauge.height
            color: "#4286f4" // blue
        }

        Rectangle {
            id: rectCoolantTempHigh
            x: rectCoolantTempLow.x + coolantTempGauge.width - (width * 2) - 6
            y: rectCoolantTempLow.y
            width: Math.ceil(coolantTempGauge.width) / 4 - 25
            height: coolantTempGauge.height
            color: "#ff311a" // red
        }

        Image {
            id: imgCoolantTemp
            x: coolantTempGauge.x + (width / 2)
            y: coolantTempGauge.y - height - 4
            width: 28
            height: 28
            source: "../images/coolant_temp_icon.png"
        }

        Text {
            id: txtCoolantTemp
            x: 692
            y: 357
            width: 98
            height: 46
            color: CF.getCoolantTempColor(coolantTempGauge.value)
            text: Math.ceil(coolantValue) + '<font size="1">C</font>'
            horizontalAlignment: Text.AlignRight
            style: Text.Normal
            styleColor: "#000000"
            font.pixelSize: 28
            verticalAlignment: Text.AlignTop
        }

/****************** OIL TEMP GAUGE ******************/

        Gauge {
            id: oilTempGauge
            x: 605
            y: 200
            width: 185
            style: OilTempGaugeStyle {}
            height: 7
            anchors.verticalCenterOffset: 220
            minimumValue: 50
            maximumValue: 150
            tickmarkStepSize: (maximumValue - minimumValue) / 4
            value: oilValue
            orientation: Qt.Horizontal
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            id: rectOilTempLow
            x: oilTempGauge.x + 13
            y: oilTempGauge.y + 11
            width: Math.ceil(oilTempGauge.width) / 4 - 25
            height: oilTempGauge.height
            color: "#4286f4" // blue
        }

        Rectangle {
            id: rectOilTempHigh
            x: rectOilTempLow.x + oilTempGauge.width - (width * 2) - 6
            y: rectOilTempLow.y
            width: Math.ceil(oilTempGauge.width) / 4 - 25
            height: oilTempGauge.height
            color: "#ff311a" // red
        }

        Image {
            id: imgOilTemp
            x: oilTempGauge.x + (width / 2)
            y: oilTempGauge.y - height + 4
            width: 28
            height: 28
            source: "../images/oil_temp_icon.png"
        }

        Text {
            id: txtOilTemp
            x: 692
            y: 424
            width: 98
            height: 46
            color: CF.getCoolantTempColor(oilTempGauge.value)
            text: Math.ceil(oilValue) + '<font size="1">C</font>'
            horizontalAlignment: Text.AlignRight
            style: Text.Normal
            styleColor: "#000000"
            font.pixelSize: 28
            verticalAlignment: Text.AlignTop
        }

/****************** VEHICLE SPEED ******************/

        Text {
            id: txtSpeed
            x: 324
            y: 302
            width: 149
            height: 46
            color: "#fff"
            text: "<b>0</b>"
            font.family: "Arial"
            horizontalAlignment: Text.AlignRight
            style: Text.Normal
            styleColor: "#000000"
            font.pixelSize: 52
            verticalAlignment: Text.AlignTop
        }

        Text {
            id: txtMph
            x: 479
            y: 302
            width: 70
            height: 57
            color: "#ffffff"
            text: qsTr("MPH")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignBottom
            font.pixelSize: 22
        }

/****************** LAP TIMING ******************/

        Text {
            id: txtCurLap
            x: 264
            y: 223
            width: 285
            height: 58
            color: "#fff"
            text: "Current " + '<font size="4"> --:--.--</font>'
            z: 1
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 36
        }

        Text {
            id: txtBestLap
            x: 324
            y: 151
            width: 166
            height: 58
            color: "#ffffff"
            text: "Best <font size=\"4\"> --:--.--</font>"
            z: 1
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 24
            horizontalAlignment: Text.AlignLeft
        }

        Rectangle {
            id: rectangle1
            x: 247
            y: 221
            width: 345
            height: 66
            color: "#3e3e3e"
            radius: 7
            z: 0
        }

        Text {
            id: txtCanFilter
            x: 650
            y: 186
            width: 142
            height: 23
            text: qsTr("Filtering: " + canFilter)
            color: (canFilter == "No") ? "red" : "green"
            font.pixelSize: 12
        }

        Text {
            id: txtConnStatus
            x: 650
            y: 157
            width: 142
            height: 23
            text: qsTr("CAN bus: " + connStatus)
            color: (connStatus == "Not Connected") ? "red" : "green"
            font.pixelSize: 12
        }

        Text {
            id: txtFrames
            x: 650
            y: 215
            width: 142
            height: 23
            text: qsTr("Frames: " + frames)
            color: (frames == 0) ? "red" : "green"
            font.pixelSize: 12
        }

/****************** GUI ELEMENTS ******************/

        ComboBox {
            id: cboTracks
            objectName: "cboTracks"
            x: 8
            y: 365
            width: 200
            height: 30
            style: ComboBoxStyle {
                textColor: "#000000"
                background: Rectangle {
                    color: "#000000"
                    border.width: 1
                    border.color: "#ffffff"
                    antialiasing: true
                }
                label: Label {
                    text: "Select Track..."
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                    color: "#ffffff"
                }
            }
        }

        Text {
            id: txtSelectedTrack
            x: 8
            y: 336
            width: 142
            height: 23
            color: "#ffffff"
            text: cboTracks.currentText
            font.pixelSize: 12
        }
    }
}
