#include <Gender.hpp>

Gender::Gender() : type(Type::Other) {}

Gender::Gender(Type genderType) : type(genderType) {}

Gender::Gender(const std::string& gender_string){
    if(gender_string == "male"){
        type = Gender::Type::Male;
    } else if(gender_string == "female"){
        type = Gender::Type::Female;
    } else{
        type = Gender::Type::Other;
    }
}

std::string Gender::toString() const {
    switch (type) {
        case Type::Male:
            return "Male";
        case Type::Female:
            return "Female";
        case Type::Other:
        default:
            return "Other";
    }
}