#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <unordered_map>
#include <Person.hpp>

// Had to do some forward declaration to fix a compiler issue. Basically, to make setGrade 
// friend of student the student class required the definition of the function to be above it.
class Course;
class Student;
class Semester;

class Professor : public Person {
public:
    static int counter;
    int getNumOfCourses();
    int getNumOfCourses(int semesterId);
    int getNumOfCourses(Semester*);
    int getEmployeeId() const;
    std::string getFieldOfStudy() const;
    void printProfessor();
    void printCourses();

    int gradeStudentAnswer(Student* student, int course_id);

    friend class Secretary;

private:
    std::string fieldOfStudy;
    const int employeeId;
    std::unordered_map<int, Course*> courses;

    Professor(const std::string& fName, const std::string& lName, int age, Gender gender, const std::string& fieldOfStudy);
    Professor(const Person& person, const std::string& fieldOfStudy);
    Professor(Person&& person, std::string&& fieldOfStudy);
    Professor(const Person& person);
    Professor(Person&& person);

    void addCourse(Course* course);
    void removeCourse(Course* course);
    void removeCourse(int courseId);

    void setFieldOfStudy(const std::string& fldOfStudy);
    void setFieldOfStudy(std::string&& fldOfStudy);

};

#include "Student.hpp"
#include <Course.hpp>
#include <Semester.hpp>

#endif