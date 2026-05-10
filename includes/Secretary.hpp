#ifndef SECRETARY_H
#define SECRETARY_H

#include <vector>
#include <string>
#include <unordered_map>
#include <Person.hpp>
#include <Professor.hpp>
#include <Student.hpp>
#include <Semester.hpp>
#include <Course.hpp>
#include <Season.hpp>
#include <Life.hpp>

class Secretary {
public:
    ~Secretary();

    int enrollStudent(Person person, int year);
    void removeStudent(int studentId);
    void updateStudent(int studentId, Person person, int year);
    
    int hireProfessor(Person person, const std::string& setFieldOfStudy);
    void fireProfessor(int employeeId);
    void updateProfessor(int empoyeeId, Person person, const std::string& setFieldOfStudy);

    int createNewSemester();     // returns semester id, first semester takes id 1, second takes id 2, etc
    void removeLastSemester();   // Also, first semester is spring, second is winter, third is spring, etc

    int createNewCourse(const std::string& name, int points, bool isOptional);
    void removeCourse(int id);
    void updateCourse(int id, const std::string& name, int points, bool isOptional);

    void addCourseToSemester(Season currentSeason, Semester* semester, Course* course);
    void removeCourseFromSemester(Semester* semester, Course* course);

    void assignProffessorToCourse(Course* course, Professor* professor);
    void removeProfessorFromCourse(Course* course, Professor* professor);

    void registerInCourse(Course* course, Student* student);
    void unregisterFromCourse(Course* course, Student* student);
    void clearStudentClasses();

    void doTheExams(Season currentSeason);

    void printWhoPassed(Season season, Course* course, const std::string& file_name);
    void printWhoPassed(Season currentSeason, Course* course);
    void printStatistics(Season season, Professor* professor);
    void printGrades(Student* student);

    bool canGraduate(Student* student);
    void printWhoCanGraduate();

    friend class Life;

private:
    std::unordered_map<int, Student*> students;
    std::unordered_map<int, Professor*> professors;
    std::unordered_map<int, Course*> courses;
    std::unordered_map<int, Student*> graduates;
    std::vector<Semester*> semesters;
    int mandatoryCourses = 0;
    int optionalCourses = 0;
    int mandatoryCoursesPoints = 0;
    int optionalCoursesPoints = 0;

    void doTheExams_helper(Course* course);

};

#endif