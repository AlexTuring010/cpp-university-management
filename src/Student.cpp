#include <Student.hpp>
#include <random>

int Student::counter = 0;

void Student::printCurrentCourses(){
    for(const auto& pair : currentCourses){
        Course* course = pair.second;
        course->printCourse();
        std::cout << std::endl;
    }    
}

void Student::printPassedCourses(){
    for(const auto& pair : passedCourses){
        Course* course = pair.second;
        course->printCourse();
        std::cout << std::endl;
    }    
}

void Student::printStudent(){
    std::cout << "id: " << getStudentId() << " ";
    printPerson();
    std::cout << getYear() << " years in uni ";
}

// Constructors:

Student::Student(const std::string& fName, const std::string& lName, int age, Gender gender, int year) : 
            Person(fName, lName, age, gender), year(year), studentId(Student::counter) {
    Student::counter++;
}

Student::Student(const Person& person, int year) :
            Person(person), year(year), studentId(Student::counter) {
    Student::counter++;
}

Student::Student(Person&& person, int year) :
            Person(std::move(person)), year(year), studentId(Student::counter){
    Student::counter++;
}


// Handling the unordered maps:

void Student::addCurrentCourse(Course* course){
    currentCourses[course->getId()] = course;
}

void Student::removeCurrentCourse(Course* course){
    currentCourses.erase(course->getId());
}

void Student::removeCurrentCourse(int courseId){
    currentCourses.erase(courseId);
}

int Student::getNumOfCurrentCourses(){
    return currentCourses.size();
}

void Student::addPassedCourse(Course* course){
    passedCourses[course->getId()] = course;
}

void Student::removePassedCourse(Course* course){
    passedCourses.erase(course->getId());
}

void Student::removePassedCourse(int courseId){
    passedCourses.erase(courseId);
}

int Student::getNumOfPassedCourses(){
    return passedCourses.size();
}

int Student::getNumOfPassedCourses(int semesterId){
    int counter = 0;
    for (const auto& pair : passedCourses) {
        if (pair.second->getSemester()->getId() == semesterId){
            counter++;
        }
    }
    return counter;    
}

int Student::getNumOfPassedCourses(Semester* semester){
    return getNumOfPassedCourses(semester->getId());
}

// Some getters:

int Student::getStudentId() const {
    return studentId;
}
    
int Student::getYear() const {
    return year;
}

// Some setters:

void Student::setYear(int student_year){
    year = student_year;
}

// Other:

void Student::do_test(int course_id){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 100);
    test_answers[course_id] = distribution(gen);
}