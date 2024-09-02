#include "interval.h"

const double infinity = std::numeric_limits<double>::infinity();

const Interval Interval::empty    = { infinity, -infinity };
const Interval Interval::universe = { -infinity, infinity };

Interval::Interval() 
    : min{infinity}, max{-infinity} {}

Interval::Interval(double min, double max)
    : min{min}, max{max} {}

double Interval::size() const{
    return max - min;
}

bool Interval::contains(double x) const {
    return min <= x && x <= max;
}

bool Interval::surrounds(double x) const {
    return min < x && x < max;
}
