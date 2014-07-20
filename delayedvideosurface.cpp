#include "delayedvideosurface.h"

DelayedVideoSurface::DelayedVideoSurface(QObject *parent) :
    QAbstractVideoSurface(parent)
{
}

bool DelayedVideoSurface::present(const QVideoFrame &frame) {
    return false;
}
