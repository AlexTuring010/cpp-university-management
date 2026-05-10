// gender.h

#ifndef GENDER_H
#define GENDER_H

#include <string>

struct Gender {
    enum class Type {
        Male,
        Female,
        Other
    };

    // Data members
    Type type;

    Gender();

    Gender(Type genderType);

    Gender(const std::string& gender_string);

    std::string toString() const;

};

#endif // GENDER_H
