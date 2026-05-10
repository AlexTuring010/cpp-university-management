#include <Person.hpp>
#include <sstream>
 
void Person::printPerson(){
    std::cout << getFullName() << " " << getAge() << " " << getGender().toString() << " ";
}

// The constructors:

Person::Person(const std::string& first_name, const std::string& last_name, int age, Gender gender):
            first_name(first_name), last_name(last_name), age(age), gender(gender) {}

// The getters:

std::string Person::getFirstName() const {
    return first_name;
}

std::string Person::getLastName() const {
    return last_name;
}

std::string Person::getFullName() const {
    return first_name + ' ' + last_name;
}

int Person::getAge() const {
    return age;
}

Gender Person::getGender() const {
    return gender;
}

// The setters:

void Person::setFirstName(std::string& firstName){
    first_name = firstName;
}

void Person::setLastName(std::string& lastName){
    last_name = lastName;
}

void Person::setFullName(std::string& firstName, std::string& lastName){
    first_name = firstName;
    last_name = lastName;
}

void Person::setFullName(std::string& fullName){
    std::istringstream iss(fullName);
    iss >> first_name >> last_name;
}

void Person::setFirstName(std::string&& firstName){
    first_name = std::move(firstName);
}

void Person::setLastName(std::string&& lastName){
    last_name = std::move(lastName);
}

void Person::setFullName(std::string&& firstName, std::string&& lastName){
    first_name = std::move(firstName);
    last_name = std::move(lastName);
}

void Person::setAge(int age1){
    age = age1;
}

void Person::setGender(Gender gender1){
    gender = gender1;
}