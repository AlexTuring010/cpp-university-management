// Person.hpp

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <Gender.hpp>
#include <iostream>

class Person{
public:
    // Our constructor:
    Person(const std::string& first_name, const std::string& last_name, int age, Gender gender);

    // Some getters:
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    int getAge() const;
    Gender getGender() const;

    // Some setters:
    void setFirstName(std::string& firstName);
    void setLastName(std::string& lastName);
    void setFullName(std::string& firstName, std::string& lastName);
    void setFullName(std::string& fullName);
    void setAge(int age1);
    void setGender(Gender gender1);

    // Function overload for setters taking an rvalue reference (for moving)
    void setFirstName(std::string&& firstName);
    void setLastName(std::string&& lastName);
    void setFullName(std::string&& firstName, std::string&& lastName);

    // For printing:
    void printPerson();

private:
    std::string first_name;
    std::string last_name;
    int age;
    Gender gender;
};


#endif