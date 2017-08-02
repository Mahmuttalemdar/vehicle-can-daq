#ifndef TRACK_H
#define TRACK_H

#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>

class Track
{
public:
    Track();
    Track(const QJsonObject&);
    Track(const std::string&, const std::string&, const std::string&, const std::string&,
          const double&, const double&, const float&, const unsigned short&);
    std::string getTrackName() const;
    std::string getState() const;
    std::string getCity() const;
    std::string getPostalCode() const;
    double getLatitude() const;
    double getLongitude() const;
    float getLength() const;
    unsigned short getTurns() const;
    void setTrackName(const std::string&);
    void setState(const std::string&);
    void setCity(const std::string&);
    void setPostalCode(const std::string&);
    void setLatitude(const double&);
    void setLongitude(const double&);
    void setLength(const float&);
    void setTurns(const unsigned short&);
    bool trackFound() const;
    std::string toString() const;
private:
    std::string track_name_;
    std::string state_;
    std::string city_;
    std::string postal_code_;
    double latitude_;
    double longitude_;
    float length_;
    unsigned short turns_;
    bool track_found_;
};

#endif // TRACK_H
