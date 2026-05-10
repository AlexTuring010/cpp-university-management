// Student.hpp

#ifndef STUDENT_H
#define STUDENT_H

#include <Professor.hpp>
#include <Person.hpp>
#include <Semester.hpp>
#include <Course.hpp>

class Professor;

class Student : public Person {
public:
    static int counter;
    int getStudentId() const;
    int getYear() const;
    void printStudent();
    void printCurrentCourses();
    void printPassedCourses();

    void do_test(int course_id);

    friend int Professor::gradeStudentAnswer(Student* student, int course_id);

    friend class Secretary;

private:
    int year;
    const int studentId;
    std::unordered_map<int, int> test_answers;
    std::unordered_map<int, int> allGrades;
    std::unordered_map<int, Course*> currentCourses;
    std::unordered_map<int, Course*> passedCourses;

    Student(const std::string& fName, const std::string& lName, int age, Gender gender, int year);
    Student(const Person& person, int year);
    Student(Person&& person, int year);

    void addCurrentCourse(Course* course);
    void removeCurrentCourse(Course* course);
    void removeCurrentCourse(int courseId);
    int getNumOfCurrentCourses();

    void addPassedCourse(Course* course);
    void removePassedCourse(Course* course);
    void removePassedCourse(int courseId);
    int getNumOfPassedCourses();
    int getNumOfPassedCourses(int semesterId);
    int getNumOfPassedCourses(Semester*);

    void setYear(int student_year);
};

#endif