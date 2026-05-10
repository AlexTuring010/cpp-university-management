#ifndef SEMESTER_H
#define SEMESTER_H

#include <Secretary.hpp>
#include <Course.hpp>
#include <Student.hpp>
#include <Professor.hpp>
#include <unordered_map>
#include <Season.hpp>

class Semester {
public:
    static int counter;
    Season season;

    int getNumOfCourses();
    int getNumOfOptionalCourses();
    int getNumOfMandatoryCourses();
    int getId() const;
    int getYear() const;
    Season getSeason() const;
    void printSemester();
    void printCourses();

    friend class Secretary;

private:
    int year;
    const int id;
    std::unordered_map<int, Course*> mandatoryCourses;
    std::unordered_map<int, Course*> optionalCourses;

    Semester() : season(Season::Type::SPRING), id(Semester::counter) {
        if(id % 2 == 0){
            season++;
        }
        year = (id - 1) / 2 + 1 ;
        Semester::counter++;
    }

    ~Semester(){
        Semester::counter--;
    }

    void addCourse(Course* course);
    void removeCourse(Course* course);
    void removeCourse(int course_id);
};

#endif