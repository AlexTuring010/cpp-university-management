#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <Semester.hpp>
#include <Professor.hpp>
#include <Student.hpp>
#include <memory>

class Course{
public:
    int getId() const;
    std::string getName() const;
    int getPoints() const;
    Semester* getSemester() const;
    std::unordered_map<int, Professor*> getProfessors();
    void printCourse();
    void printCurrentStudents();
    void printPassedStudents();
    void printProfessors();
    
    bool isOptional = false;

    friend class Secretary;

private:
    static int counter;
    int passedThisSeason = 0;
    const int id;
    std::string name;
    int points;
    Semester* semester;
    std::unordered_map<int, Professor*> professors;
    std::unordered_map<int, Student*> currentStudents;
    std::unordered_map<int, Student*> passedStudents;
    
    Course();

    std::unordered_map<int, Student*> getCurrentStudents();
    std::unordered_map<int, Student*> getPassedStudents();
    int getNumOfCurrentStudents();
    int getNumOfPassedStudents();
    int getNumOfProfessors();

    void addCurrentStudent(Student* student);
    void removeCurrentStudent(Student* student);
    void removeCurrentStudent(int studentId);

    void addPassedStudent(Student* student);
    void removePassedCStudent(Student* student);
    void removePassedStudent(int studentId);

    void addProfessor(Professor* professor);
    void removeProfessor(Professor* professor);
    void removeProfessor(int proffesorId);

    void setName(const std::string& course_name);
    void setPoints(int course_points);
    void setSemester(Semester* course_semester);
};

#endif