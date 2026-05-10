#ifndef LIFE_H
#define LIFE_H

#include <Season.hpp>
#include <iostream>

class Secretary;

class Life {

public:
    Season currentSeason;
    Secretary* DIT_Secretary;

    Life();

    ~Life();

    void service_player_commands(); // This run in a loop, listening to player commands like a terminal

    //void importFromFile(const std::string& fileName);
    void createStudent();
    void createProfessor();
    void createCourse();
    void createSemester();
    void updateStudent(int studentId);
    void updateProfessor(int professorId);
    void updateCourse(int courseId);
    void deleteSemester();
    void deleteStudent(int studentId);
    void deleteProfessor(int professorId);
    void deleteCourse(int courseId);
    void listStudents();
    void listProfessors();
    void listCourses();
    void listSemesters();
    void registerStudent(int studentId, int courseId);
    void assignProfessor(int professorId, int courseId);
    void setCourseSemester(int courseId, int semesterId);
    void removeStudent(int studentId, int courseId);
    void removeProfessor(int professorId, int courseId);
    void removeCourseSemester(int studentId, int courseId);
    void end_season();
    void begin_next_season();
    void listGraduates();
    void printProfessorStatistics(int professorId);
    void printStudentGrades(int studentId);
    void printResultsOfCourse(int courseIde);
    void printResultsOfCourseInFile(int courseId, const std::string& fileName);
    void printCoursesOfSemester(int semesterId);
    void printCurrentCoursesOfStudent(int studentId);
    void printCurrentStudentsOfCourse(int courseId);
    void printPassedCoursesOfStudent(int studentId);
    void printCoursesOfProfessor(int professorId);
    void printPassedStudentsOfCourse(int courseId);
    void printProfessorsOfCourse(int courseId);
    void importFromFile(std::string fileName);
    void help();
    
private:
    bool hasEnded = false;
    void importCourses(std::ifstream& file);
    void importProfessors(std::ifstream&file);
    void importSemesters(std::ifstream& file);
    void importStudents(std::ifstream& file);
};

#include <Secretary.hpp>

#endif
