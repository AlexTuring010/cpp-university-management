#include <Course.hpp>

int Course::counter = 0;

void Course::printProfessors(){
    for(const auto& pair : professors){
        Professor* professor = pair.second;
        professor->printProfessor();
        std::cout << std::endl;
    }
}

void Course::printCurrentStudents(){
     for(const auto& pair : currentStudents){
        Student* student = pair.second;
        student->printStudent();
        std::cout << std::endl;
    }       
}

void Course::printPassedStudents(){
     for(const auto& pair : passedStudents){
        Student* student = pair.second;
        student->printStudent();
        std::cout << std::endl;
    }       
}

void Course::printCourse(){
    std::cout << "id: " << getId() << " name: " << getName() << " points: " << getPoints() <<  " ";
    if(isOptional){
        std::cout << "optional ";
    } else{
        std::cout << "mandatory ";
    }
}

// The constructor:

Course::Course() : id(Course::counter){
    Course::counter++;
}

// Some setters:

void Course::setName(const std::string& course_name){
    name = course_name;
}

void Course::setPoints(int course_points){
    points = course_points;
}
 
void Course::setSemester(Semester* course_semester){
    semester = course_semester;
}

// Some getters:

int Course::getId() const {
    return id;
}    

std::string Course::getName() const {
    return name;
}

int Course::getPoints() const {
    return points;
}

Semester* Course::getSemester() const {
    return semester;
}

// For the unordered_map:

std::unordered_map<int, Student*> Course::getCurrentStudents(){
    return currentStudents;
}

std::unordered_map<int, Student*> Course::getPassedStudents(){
    return passedStudents;
}

int Course::getNumOfCurrentStudents(){
    return currentStudents.size();
}

int Course::getNumOfPassedStudents(){
    return passedStudents.size();
}

void Course::addCurrentStudent(Student* student){
    currentStudents[student->getStudentId()] = student;
}

void Course::removeCurrentStudent(Student* student){
    currentStudents.erase(student->getStudentId());
}

void Course::removeCurrentStudent(int studentId){
    currentStudents.erase(studentId);
}

void Course::addPassedStudent(Student* student){
    passedStudents[student->getStudentId()] = student;
}

void Course::removePassedCStudent(Student* student){
    passedStudents.erase(student->getStudentId());
}

void Course::removePassedStudent(int studentId){
    passedStudents.erase(studentId);
}

void Course::addProfessor(Professor* professor){
    professors[professor->getEmployeeId()] = professor;
}

void Course::removeProfessor(Professor* professor){
    professors.erase(professor->getEmployeeId());
}

void Course::removeProfessor(int professorId){
    professors.erase(professorId);
}

int Course::getNumOfProfessors(){
    return professors.size();
}

std::unordered_map<int, Professor*> Course::getProfessors(){
    return professors;
}