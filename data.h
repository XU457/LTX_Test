#ifndef DATA_H
#define DATA_H

#include <QTime>
#include <iostream>

class Data
{
public:

    // I would have used the standard c++ time datatpe but the qt one is much better
    QTime time;
    double latitude;
    double langitude;
    int course;
    int kts;
    int mph;
    int altitudeFeet;
    std::string reportingFaculty;

    Data();
    Data(QTime timeH, double lat, double lang, int courseH, int ktsH, int mphH, int altitudeF, std::string reportingF)
        : time(timeH), latitude(lat), langitude(lang), course(courseH), kts(ktsH), mph(mphH), altitudeFeet(altitudeF), reportingFaculty(reportingF) { }
    ~Data();
};

#endif // DATA_H
