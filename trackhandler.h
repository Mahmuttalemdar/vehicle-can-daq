#ifndef TRACKHANDLER_H
#define TRACKHANDLER_H

#include <QObject>

class TrackHandler : public QObject{
   Q_OBJECT
public:
    explicit TrackHandler (QObject* parent = 0) :
        QObject(parent)
    {

    }

    Q_INVOKABLE int test()
    {
        return 1;
    }
};
#endif // TRACKHANDLER_H
