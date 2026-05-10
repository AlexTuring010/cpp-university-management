#include <Semester.hpp>
#include <iostream> 
#include <Utilities.hpp>

int Semester::counter = 1;

void Semester::printCourses(){
    for(const auto& pair : mandatoryCourses){
        Course* course = pair.second;
        course->printCourse();
        std::cout << std::endl;
    }
    for(const auto& pair : optionalCourses){
        Course* course = pair.second;
        course->printCourse();
        std::cout << std::endl;
    }
}

void Semester::printSemester(){
    std::cout << "id: " << getId() << " Season: " << getSeason().toString() << " year: " << getYear() << " optional courses: " << getNumOfOptionalCourses() << " mandatory courses: " << getNumOfMandatoryCourses() << " ";
}

// For handling the unordered maps:

void Semester::addCourse(Course* course){
    if(course->isOptional){
        optionalCourses[course->getId()] = course;
    } else{
        mandatoryCourses[course->getId()] = course;
    }
}

void Semester::removeCourse(Course* course){
    if(isInMap(optionalCourses, course->getId())){
      optionalCourses.erase(course->getId());
    } else if(isInMap(mandatoryCourses, course->getId())){
        mandatoryCourses.erase(course->getId());
    }
}

void Semester::removeCourse(int course_id){
    if(isInMap(optionalCourses, course_id)){
      optionalCourses.erase(course_id);
    } else if(isInMap(mandatoryCourses, course_id)){
        mandatoryCourses.erase(course_id);
    }
}

int Semester::getNumOfCourses(){
    return getNumOfOptionalCourses() + getNumOfMandatoryCourses();
}

int Semester::getNumOfOptionalCourses(){
    return optionalCourses.size();
}

int Semester::getNumOfMandatoryCourses(){
    return mandatoryCourses.size();
}

// Some getters:

int Semester::getId() const {
    return id;
}

int Semester::getYear() const {
    return year;
}

Season Semester::getSeason() const {
    return season;
}