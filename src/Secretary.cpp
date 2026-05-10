#include <Secretary.hpp>
#include <unordered_map>
#include <iostream>
#include <Utilities.hpp>
#include <fstream>
#include <ErrorSignals.hpp>

Secretary::~Secretary(){
    for (auto it = students.begin(); it != students.end() ; ){
        Student* student = it->second;
        it = std::next(it);
        delete student;
    }
    for (auto it = courses.begin(); it != courses.end() ; ){
        Course* course = it->second;
        it = std::next(it);
        delete course;
    }
    for (auto it = professors.begin(); it != professors.end() ; ){
        Professor* professor = it->second;
        it = std::next(it);
        delete professor;
    }
    std::size_t num = semesters.size();
    for (std::size_t i = 0; i < num; ++i) {
        removeLastSemester();
    }
}

int Secretary::enrollStudent(Person person, int year){
    Student* newStudent = new Student(person, year);
    students[newStudent->getStudentId()] = newStudent;
    return newStudent->getStudentId();
}

void Secretary::removeStudent(int studentId){
    Student* removedStudent = students[studentId];
    students.erase(studentId);
    for (const auto& pair : removedStudent->currentCourses) {
        Course* course = pair.second;
        course->removeCurrentStudent(removedStudent);
    }
    for (const auto& pair : removedStudent->passedCourses) {
        Course* course = pair.second;
        course->removePassedCStudent(removedStudent);
    }
    delete removedStudent;
}

void Secretary::updateStudent(int studentId, Person person, int year){
    Student* theStudent = students[studentId];
    // dont forget to check for exception here
    theStudent->setFullName(person.getFirstName(), person.getLastName());
    theStudent->setAge(person.getAge());
    theStudent->setGender(person.getGender());
    theStudent->year = year;
}
    
int Secretary::hireProfessor(Person person, const std::string& fieldOfStudy){
    Professor* newProfessor = new Professor(person, fieldOfStudy);
    professors[newProfessor->getEmployeeId()] = newProfessor;
    return newProfessor->getEmployeeId();
}

void Secretary::fireProfessor(int employeeId){
    Professor* removedProfessor = professors[employeeId];
    professors.erase(employeeId);
    for (const auto& pair : removedProfessor->courses) {
        Course* course = pair.second;
        course->removeProfessor(removedProfessor);
    }
    delete removedProfessor; 
}

void Secretary::updateProfessor(int employeeId, Person person, const std::string& fieldOfStudy){
    Professor* theProfessor = professors[employeeId];
    // dont forget to check for exception here
    theProfessor->setFullName(person.getFirstName(), person.getLastName());
    theProfessor->setAge(person.getAge());
    theProfessor->setGender(person.getGender());
    theProfessor->fieldOfStudy = fieldOfStudy; 
}

int Secretary::createNewSemester(){
    semesters.push_back(new Semester());
    Semester* lastSemester = semesters.back();
    return lastSemester->getId();
};

void Secretary::removeLastSemester(){
    Semester* lastSemester = semesters.back();
    semesters.pop_back();
    for (const auto& pair : lastSemester->optionalCourses) {
        pair.second->setSemester(nullptr);
    }
    for (const auto& pair : lastSemester->mandatoryCourses) {
        pair.second->setSemester(nullptr);
    }
    delete lastSemester;
}

int Secretary::createNewCourse(const std::string& name, int points, bool isOptional){
    Course* newCourse = new Course();
    courses[newCourse->getId()] = newCourse;
    newCourse->isOptional = isOptional;
    newCourse->points = points;
    newCourse->setName(name);
    newCourse->semester = nullptr;
    if(isOptional){
        optionalCourses += 1;
        optionalCoursesPoints += points;
    } else{
        mandatoryCourses += 1;
        mandatoryCoursesPoints += points;
    }
    return newCourse->getId();
}

void Secretary::removeCourse(int id){
    Course* removedCourse = courses[id];
    courses.erase(id);
    if(removedCourse->semester != nullptr)
        removedCourse->semester->removeCourse(removedCourse);
    for (auto it = removedCourse->currentStudents.begin(); it != removedCourse->currentStudents.end() ; ){
        Student* student = it->second;
        it = std::next(it);
        student->removeCurrentCourse(removedCourse);
        student->allGrades.erase(id);
    }
   for (auto it = removedCourse->passedStudents.begin(); it != removedCourse->passedStudents.end() ; ){
        Student* student = it->second;
        it = std::next(it);
        student->removePassedCourse(removedCourse);
        student->allGrades.erase(id);
    }
    for(auto it = removedCourse->professors.begin(); it != removedCourse->professors.end() ; ){
        Professor* professor = it->second;
        professor->removeCourse(removedCourse);
    }
    if(removedCourse->isOptional){
        optionalCourses -= 1;
        optionalCoursesPoints -= removedCourse->getPoints();
    } else{
        mandatoryCourses -= 1;
        mandatoryCoursesPoints -= removedCourse->getPoints();
    }
    delete removedCourse;
}

void Secretary::updateCourse(int id, const std::string& name, int points, bool isOptional){
    Course* theCourse = courses[id];
    theCourse->setName(name);
    if(isOptional != theCourse->isOptional){
        if(isOptional){
            optionalCourses += 1;
            optionalCoursesPoints += points;
            mandatoryCourses -= 1;
            mandatoryCoursesPoints -= theCourse->points;
        } else{
            mandatoryCourses += 1;
            mandatoryCoursesPoints += points;
            optionalCourses -= 1;
            optionalCoursesPoints -= theCourse->points;
        }
    } else{
        if(isOptional){
            optionalCoursesPoints += points - theCourse->points;
        } else{
            mandatoryCoursesPoints += points - theCourse->points;
        }
    }
    theCourse->setPoints(points);
    theCourse->isOptional = isOptional;
}

void Secretary::addCourseToSemester(Season current_season, Semester* semester, Course* course){
    if(course->semester != nullptr){
        course->semester->removeCourse(course);
    }
    semester->addCourse(course);
    course->setSemester(semester);
    for (const auto& pair : course->currentStudents) {
        Student* student = pair.second;
        if(student->getYear() < semester->getYear() || current_season.toString() != semester->getSeason().toString()){
            student->removeCurrentCourse(course);
        }
    }
}

void Secretary::removeCourseFromSemester(Semester* semester, Course* course){
    if(course != nullptr && course->semester != nullptr){
        course->semester->removeCourse(course);
        course->setSemester(nullptr);
    }
    for (const auto& pair : course->currentStudents) {
        Student* student = pair.second;
        student->removeCurrentCourse(course);
    }
}

void Secretary::assignProffessorToCourse(Course* course, Professor* professor){
    professor->addCourse(course);
    course->addProfessor(professor);
}

void Secretary::removeProfessorFromCourse(Course* course, Professor* professor){
    professor->removeCourse(course);
    course->removeProfessor(professor);
}

void Secretary::registerInCourse(Course* course, Student* student){
    student->addCurrentCourse(course);
    course->addCurrentStudent(student);
}

void Secretary::unregisterFromCourse(Course* course, Student* student){
    student->removeCurrentCourse(course);
    course->removeCurrentStudent(student);
}

void Secretary::clearStudentClasses(){
   for (auto it = students.begin(); it != students.end(); ) {
        Student* student = it->second;
        auto courseIt = student->currentCourses.begin();
        while (courseIt != student->currentCourses.end()) {
            Course* course = courseIt->second;
            course->removeCurrentStudent(student);
            auto nextCourseIt = std::next(courseIt);
            student->removeCurrentCourse(course);
            courseIt = nextCourseIt;
        }
        auto nextIt = std::next(it);
        it = nextIt;
    }
}

 void Secretary::doTheExams_helper(Course* course){
    course->passedThisSeason = 0;
    for (const auto& pair : course->currentStudents) {
        Student* student = pair.second;
        student->do_test(course->getId());///////////
        int sum = 0;
        for (const auto& pair : course->professors) {
            Professor* professor = pair.second;
            sum += professor->gradeStudentAnswer(student, course->getId()); 
        }
        student->allGrades[course->getId()] = sum / course->getNumOfProfessors();
        if(student->allGrades[course->getId()] >= 50){
            course->passedThisSeason += 1;
            student->addPassedCourse(course);
            course->addPassedStudent(student);
        }
    }
}

#define ANSI_RESET "\033[0m"
#define ANSI_LIGHT_RED "\033[1;91m" 

void Secretary::doTheExams(Season season){
    for (std::size_t i = 0; i < semesters.size(); ++i) {
        Semester* semester = semesters[i];
        if(semester->season == season){
            for (const auto& pair : semester->mandatoryCourses) {
                Course* course = pair.second;
                if(course->professors.size() == 0){
                    std::cout << ANSI_LIGHT_RED << "Couldn't do exams for class " << course->name << " because it was not assigned any professors." << std::endl << ANSI_RESET;
                    continue;
                }
                doTheExams_helper(course);
            }
            for (const auto& pair : semester->optionalCourses) {
                Course* course = pair.second;
                if(course->professors.size() == 0){
                    std::cout << ANSI_LIGHT_RED << "Couldn't do exams for class " << course->name << " because it was not assigned any professors." << std::endl << ANSI_RESET;
                    continue;
                }
                doTheExams_helper(course);
            }
        }
    }
}

void Secretary::printWhoPassed(Season currentSeason, Course* course){
    for (const auto& pair : course->currentStudents) {
        Student* student = pair.second;
        std::string result;
        if (student->allGrades[course->getId()] >= 50) {
            result = "passed";
        } else {
            result = "failed";
        }
        std::cout << "Student " << student->getFullName() << " got " << student->allGrades[course->getId()] << "/100" << " and so they " << result << "!" << std::endl;
    }
}

void Secretary::printWhoPassed(Season season, Course* course, const std::string& file_name) {
    std::ofstream output_file(file_name);

    if (!output_file.is_open()) {
        throw OPEN_FILE_ERROR;
        return;
    }

    for (const auto& pair : course->currentStudents) {
        Student* student = pair.second;
        std::string result;
        if (student->allGrades[course->getId()] >= 50) {
            result = "passed";
        } else {
            result = "failed";
        }
        output_file << "Student " << student->getFullName() << " got " << student->allGrades[course->getId()] << "/100" << " and so they " << result << "!" << std::endl;
    }

    output_file.close();
}

void Secretary::printStatistics(Season season, Professor* professor){
    int numOfStudents = 0;
    int passedStudents = 0;
    for (const auto& pair : professor->courses){
        Course* course = pair.second;
        Semester* semester = course->semester;
        if(!(semester->season == season)){
            continue;
        }
        passedStudents += course->passedThisSeason;
        numOfStudents += course->getNumOfCurrentStudents();
    }
    int failedStudents = numOfStudents - passedStudents;
    std::cout << failedStudents << " students failed." << std::endl << passedStudents << " student passed." << std::endl;
}

void Secretary::printGrades(Student* student){
    for (const auto& pair : student->allGrades){
        Course* course = courses[pair.first];
        int grade = pair.second;
        std::cout << "Course " << course->getName() << " : " << grade << "/100 " << std::endl;
    }
}

bool Secretary::canGraduate(Student* student){
    // The reason I have to do all those calculations every time instead of having some list
    // of graduates or something is because criteria for graduating can be changed if the user
    // adds new mandatory classes or makes other changes. So, soemone could be able to graduate
    // at one point, but then a new mandatory class is added and he no longer can graduate.
   int passedMandatoryClasses = 0;
   int points = 0;
   for (const auto& pair : student->passedCourses){
       Course* course = pair.second;
       if(!course->isOptional){
           passedMandatoryClasses += 1;
       }
       points += course->getPoints();
   }
   if(passedMandatoryClasses < mandatoryCourses){
       return false;
   }
   if(points < mandatoryCoursesPoints + (1/30) * optionalCoursesPoints){
       return false;
   }
   return true;
}

void Secretary::printWhoCanGraduate(){
    for (const auto& pair : students){
        Student* student = pair.second;
        if(canGraduate(student)){
            std::cout << student->getFullName() << std::endl;
        }
    }
}