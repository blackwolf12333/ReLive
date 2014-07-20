#ifndef DELAYEDVIDEOSURFACE_H
#define DELAYEDVIDEOSURFACE_H

#include <QObject>
#include <QAbstractVideoSurface>

class DelayedVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit DelayedVideoSurface(QObject *parent = 0);
    bool present(const QVideoFrame &frame);
signals:

public slots:

};

#endif // DELAYEDVIDEOSURFACE_H
