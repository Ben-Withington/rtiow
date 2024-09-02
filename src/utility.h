#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <numbers>

namespace utility {
    inline double degToRad(double degrees) {
        return degrees * std::numbers::pi / 180.0;
    }

    inline double randomDouble() {
        static std::uniform_real_distribution<double> dist{0.0, 1.0};
        static std::mt19937 gen{};
        return dist(gen);
    }

    inline double randomDouble(double min, double max) {
        return min + (max-min) * randomDouble();
    }
}

#endif // RANDOM_H