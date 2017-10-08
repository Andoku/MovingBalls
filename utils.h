#ifndef UTILS_H
#define UTILS_H

#include <QPointF>
#include <math.h>

inline int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

inline qreal distance(QPointF p1, QPointF p2)
{
    return sqrt(pow(p2.rx() - p1.rx(), 2) + pow(p2.ry() - p1.ry(), 2));
}

#endif // UTILS_H
