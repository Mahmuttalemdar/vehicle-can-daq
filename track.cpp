#include "track.h"

Track::Track(){
    track_name_ = "";
    state_ = "";
    city_ = "";
    postal_code_ = "";
    latitude_ = 0.0;
    longitude_ = 0.0;
    length_ = 0.0;
    turns_ = 0;
    track_found_ = false;
}

Track::Track(const std::string &trackName, const std::string &state, const std::string &city, const std::string &postalCode,
             const double &latitude, const double &longitude, const float &length, const unsigned short &turns) {
    track_name_ = trackName;
    state_ = state;
    city_ = city;
    postal_code_ = postalCode;
    latitude_ = latitude;
    longitude_ = longitude;
    length_ = length;
    turns_ = turns;
    track_found_ = true;
}

Track::Track(const QJsonObject &jsonObj)
{
    if(!jsonObj.isEmpty()) {
        track_name_ =   jsonObj["Track Name"].toString().toStdString();
        state_ =        jsonObj["State"].toString().toStdString();
        city_ =         jsonObj["City"].toString().toStdString();
        postal_code_ =  jsonObj["Postal Code"].toString().toStdString();
        latitude_ =     jsonObj["Latitude"].toDouble();
        longitude_ =    jsonObj["Longitude"].toDouble();
        length_ =       jsonObj["Length"].toDouble();
        turns_ =        jsonObj["Turns"].toInt();
        track_found_ = true;
    }
    else {
        track_name_ = "";
        state_ = "";
        city_ = "";
        postal_code_ = "";
        latitude_ = 0.0;
        longitude_ = 0.0;
        length_ = 0.0;
        turns_ = 0;
        track_found_ = false;
    }
}

std::string Track::getTrackName() const {
    return track_name_;
}

void Track::setTrackName(const std::string &trackName) {
    track_name_ = trackName;
}

std::string Track::getState() const {
    return state_;
}

void Track::setState(const std::string &state) {
    state_ = state;
}

std::string Track::getCity() const {
    return city_;
}

void Track::setCity(const std::string &city) {
    city_ = city;
}

std::string Track::getPostalCode() const {
    return postal_code_;
}

void Track::setPostalCode(const std::string &postalCode) {
    postal_code_ = postalCode;
}

double Track::getLatitude() const {
    return latitude_;
}

void Track::setLatitude(const double &latitude) {
    latitude_ = latitude;
}

double Track::getLongitude() const {
    return longitude_;
}

void Track::setLongitude(const double &longitude) {
    longitude_ = longitude;
}

float Track::getLength() const {
    return length_;
}

void Track::setLength(const float &length) {
    length_ = length;
}

unsigned short Track::getTurns() const {
    return turns_;
}

void Track::setTurns(const unsigned short &turns) {
    turns_ = turns;
}

bool Track::trackFound() const {
    return track_found_;
}

std::string Track::toString() const {
    return  track_name_ + "\n" +
            state_ + "\n" +
            city_ + "\n" +
            postal_code_ + "\n" +
            std::to_string(latitude_) + "\n" +
            std::to_string(longitude_) + "\n" +
            std::to_string(length_) + "\n" +
            std::to_string(turns_);
}
