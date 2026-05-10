#ifndef SEASON_H
#define SEASON_H

#include <string>

class Season {
public:
    enum class Type {
        SPRING,
        WINTER
    };

    Season(Type initialSeason) : currentSeason(initialSeason) {}

    std::string toString() const {
        switch (currentSeason) {
            case Type::SPRING:
                return "Spring";
            case Type::WINTER:
                return "Winter";
            default:
                return "Unknown";
        }
    }

    Season& operator++(int) {
        switch (currentSeason) {
            case Type::SPRING:
                currentSeason = Type::WINTER;
                break;
            case Type::WINTER:
                currentSeason = Type::SPRING;
                break;
            default:
                break;
        }
        return *this;
    }

    bool operator==(const Season& other) const {
        return currentSeason == other.currentSeason;
    }

private:
    Type currentSeason;
};

#endif // SEASON_H