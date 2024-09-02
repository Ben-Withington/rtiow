#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

class Interval {
    public:
        double min;
        double max;

        Interval();
        Interval(double min, double max);

        double size() const;
        bool contains(double x) const;
        bool surrounds(double x) const;
        double clamp(double x) const;

        static const Interval empty;
        static const Interval universe;
};

#endif // INTERVAL_H