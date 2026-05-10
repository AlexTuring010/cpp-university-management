#include <Professor.hpp>
#include <random>

int Professor::counter = 0;

void Professor::printCourses(){
    for(const auto& pair : courses){
        Course* course = pair.second;
        course->printCourse();
        std::cout << std::endl;
    }     
}

void Professor::printProfessor(){
    std::cout << "id: " << getEmployeeId() << " ";
    printPerson();
    std::cout << getFieldOfStudy() << " ";
}

// Constructors:

Professor::Professor(const std::string& fName, const std::string& lName, int age, Gender gender, const std::string& fieldOfStudy) : 
                    Person(fName, lName, age, gender), fieldOfStudy(fieldOfStudy), employeeId(Professor::counter) {
  Professor::counter++;  
}

Professor::Professor(const Person& person, const std::string& fieldOfStudy) :
                    Person(person), fieldOfStudy(fieldOfStudy), employeeId(Professor::counter) {
  Professor::counter++;      
}

Professor::Professor(Person&& person, std::string&& fieldOfStudy) :
                    Person(std::move(person)), fieldOfStudy(std::move(fieldOfStudy)), employeeId(Professor::counter) {
  Professor::counter++;  
}

Professor::Professor(const Person& person) : Person(person), employeeId(Professor::counter) {
    Professor::counter++;  
}

Professor::Professor(Person&& person) : Person(std::move(person)), employeeId(Professor::counter) {
  Professor::counter++;  
}

// For handling the unordered maps:

void Professor::addCourse(Course* course){
    courses[course->getId()] = course;
}

void Professor::removeCourse(Course* course){
    courses.erase(course->getId());
}

void Professor::removeCourse(int courseId){
    courses.erase(courseId);
}

int Professor::getNumOfCourses(){
   return courses.size();
}

int Professor::getNumOfCourses(int semesterId){
    int counter = 0;
    for (const auto& pair : courses) {
        if (pair.second->getSemester()->getId() == semesterId){
            counter++;
        }
    }
    return counter;
}

int Professor::getNumOfCourses(Semester* semester){
    return getNumOfCourses(semester->getId());
}

// Some getters:

int Professor::getEmployeeId() const {
    return employeeId;
}

std::string Professor::getFieldOfStudy() const {
    return fieldOfStudy;
}

// Some setters:
    
void Professor::setFieldOfStudy(const std::string& fldOfStudy){
    fieldOfStudy = fldOfStudy;
}

void Professor::setFieldOfStudy(std::string&& fldOfStudy){
    fieldOfStudy = std::move(fldOfStudy);
}

// Other:

int Professor::gradeStudentAnswer(Student* student, int course_id){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 100);
    int professor_answer = distribution(gen);
    int student_answer = student->test_answers[course_id];
    if(professor_answer > student_answer){
        return 100 - (professor_answer - student_answer);
    }
    return 100 - (student_answer - professor_answer); // Good luck to the student!
}