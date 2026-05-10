#include <Life.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <Utilities.hpp>
#include <ErrorSignals.hpp>
#include <limits> 
#include <cstdlib>

// ANSI escape codes for text color
#define ANSI_RESET "\033[0m"
#define ANSI_LIGHT_GREEN "\033[1;92m"
#define ANSI_LIGHT_BLUE "\033[36m"
#define ANSI_LIGHT_RED "\033[1;91m" 
#define ANSI_LIGHT_GRAY "\033[37m"
#define ANSI_CORAL "\033[38;5;216m"

Life::Life() : currentSeason(Season::Type::SPRING){
    DIT_Secretary = new Secretary();
    std::cout << ANSI_LIGHT_BLUE << std::endl << "Life has started to exist, and the students are ready to start learning!" << ANSI_RESET << std::endl;
}

Life::~Life(){
    delete DIT_Secretary;
    std::cout << ANSI_LIGHT_BLUE << std::endl << "Life has ceased to exist, I hope the students did well." << ANSI_RESET << std::endl << std::endl;
}

void Life::service_player_commands(){
    while (true) {
        try{
            std::string userInput;

            // Read a line from the terminal
            std::cout << std::endl << ANSI_CORAL << "Enter a command: " << ANSI_RESET;
            std::getline(std::cin, userInput);

            // Parse the line into words
            std::istringstream iss(userInput);
            std::string command, parameter0 = " ", parameter1 = " ", parameter2 = " ", parameter3 = " ", parameter4 = " ", parameter5 = " ", parameter6 = " ";
            int numberParameter1 = -1, numberParameter2 = -1;
            
            iss >> command;
            
            if (command == "exit"){
                std::cout << ANSI_LIGHT_GRAY << std::endl << "Exiting..." << ANSI_RESET << std::endl;
                return;
            } else if(command == "clear"){
                system("clear");
                continue;  
            } else if(command == "help"){
                help();
                continue;
            }

            if (command == "next"){
                iss >> parameter1;
                if(parameter1 == "season"){
                    begin_next_season();    
                    continue;
                }
            } else if(command == "end"){
                if(hasEnded == true){
                    throw HAS_ENDED;
                }
                iss >> parameter1;
                if(parameter1 == "season"){
                    end_season();
                    continue;
                }
            }

            if (command == "import"){
                iss >> parameter0;
                importFromFile(parameter0);
                continue;
            }

            if (command == "create"){
                if(hasEnded == true){
                    throw HAS_ENDED;
                }
                iss >> parameter1;
                if(parameter1 == "student"){
                    createStudent();
                    continue;
                } else if(parameter1 == "professor"){
                    createProfessor();
                    continue;
                } else if(parameter1 == "course"){
                    createCourse();
                    continue;
                } else if(parameter1 == "semester"){
                    createSemester();
                    continue;
                }
            } else if (command == "update"){
                if(hasEnded == true){
                    throw HAS_ENDED;
                }
                iss >> parameter1;
                iss >> numberParameter1;
                if(parameter1 == "student"){
                    updateStudent(numberParameter1);
                    continue;
                } else if(parameter1 == "professor"){
                    updateProfessor(numberParameter1);
                    continue;
                } else if(parameter1 == "course"){
                    updateCourse(numberParameter1);
                    continue;
                }
            } else if (command == "delete"){
                if(hasEnded == true){
                    throw HAS_ENDED;
                }
                iss >> parameter1;
                if(parameter1 == "semester"){
                    deleteSemester();
                    continue;
                }
                iss >> numberParameter1;
                if(parameter1 == "student"){
                    deleteStudent(numberParameter1);
                    continue;
                } else if(parameter1 == "professor"){
                    deleteProfessor(numberParameter1);
                    continue;
                } else if(parameter1 == "course"){
                    deleteCourse(numberParameter1);
                    continue;
                }
            }

            if(command == "print"){
                iss >> parameter1;
                if (parameter1 == "current"){
                    iss >> parameter2;
                    if (parameter2 == "courses"){
                        iss >> parameter3;
                        if(parameter3 == "of"){
                            iss >> parameter4;
                            if(parameter4 == "student"){
                                iss >> numberParameter1;
                                printCurrentCoursesOfStudent(numberParameter1);
                                continue;
                            }
                        }
                    } else if(parameter2 == "students"){
                        iss >> parameter3;
                        if(parameter3 == "of"){
                            iss >> parameter4;
                            if(parameter4 == "course"){
                                iss >> numberParameter1;
                                printCurrentStudentsOfCourse(numberParameter1);
                                continue;
                            }
                        }
                    }
                } else if(parameter1 == "passed"){
                    iss >> parameter2;
                    if(parameter2 == "courses"){
                        iss >> parameter3;
                        if(parameter3 == "of"){
                            iss >> parameter4;
                            if(parameter4 == "student"){
                                iss >> numberParameter1;
                                printPassedCoursesOfStudent(numberParameter1);
                                continue;
                            }
                        }
                    } else if(parameter2 == "students"){
                        iss >> parameter3;
                        if(parameter3 == "of"){
                            iss >> parameter4;
                            if(parameter4 == "course"){
                                iss >> numberParameter1;
                                printPassedStudentsOfCourse(numberParameter1);
                                continue;
                            }
                        }
                    }
                } else if(parameter1 == "students"){
                    if(iss >> parameter2)
                        throw UNKNOWN_COMMAND;
                    listStudents();
                    continue;
                } else if(parameter1 == "professors"){
                    if(iss >> parameter2){
                        if(parameter2 == "of"){
                            iss >> parameter3;
                            if(parameter3 == "course"){
                                iss >> numberParameter1;
                                printProfessorsOfCourse(numberParameter1);
                                continue;
                            }
                        }
                    }
                    listProfessors();
                    continue;
                } else if(parameter1 == "courses"){
                    if(iss >> parameter2){
                        if(parameter2 == "of"){
                            iss >> parameter3;
                            if(parameter3 == "semester"){
                                iss >> numberParameter1;
                                printCoursesOfSemester(numberParameter1);
                                continue;
                            } else if (parameter3 == "professor"){
                                iss >> numberParameter1;
                                printCoursesOfProfessor(numberParameter1);
                                continue;
                            }
                        }
                    }
                    listCourses();
                    continue;
                } else if(parameter1 == "semesters"){
                    listSemesters();
                    continue;
                } else if(parameter1 == "graduates"){
                    listGraduates();
                    continue;
                } else if(parameter1 == "professor"){
                    iss >> numberParameter1;
                    iss >> parameter2;
                    if(parameter2 == "statistics"){
                        printProfessorStatistics(numberParameter1);
                        continue;
                    }
                } else if(parameter1 == "student"){
                    iss >> numberParameter1;
                    iss >> parameter2;
                    if(parameter2 == "grades"){
                        printStudentGrades(numberParameter1);
                        continue;
                    }
                } else if(parameter1 == "exam"){
                    iss >> parameter2;
                    if(parameter2 == "results"){
                        iss >> parameter3;
                        if(parameter3 == "of"){
                            iss >> parameter4;
                            if(parameter4 == "course"){
                                iss >> numberParameter1;
                                if(!(iss >> parameter5)){
                                    printResultsOfCourse(numberParameter1);
                                    continue;
                                }
                                if(parameter5 == "in"){
                                    // print exam results of course course_id in file_name
                                    iss >> parameter6;
                                    printResultsOfCourseInFile(numberParameter1, parameter6);
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
            if(command == "add"){
                if(hasEnded == true){
                    throw HAS_ENDED;
                }
                iss >> parameter0;
                if(parameter0 == "student"){
                    // insert student student_id to course course_id
                    iss >> numberParameter1;
                    iss >> parameter1;
                    if(parameter1 == "to"){
                        iss >> parameter2;
                        if(parameter2 == "course"){
                            iss >> numberParameter2;
                            registerStudent(numberParameter1, numberParameter2);
                            continue;
                        }
                    }
                } else if (parameter0 == "professor"){
                    // insert professor professor_id to course course_id
                    iss >> numberParameter1;
                    iss >> parameter1;
                    if(parameter1 == "to"){
                        iss >> parameter2;
                        if(parameter2 == "course"){
                            iss >> numberParameter2;
                            assignProfessor(numberParameter1, numberParameter2);
                            continue;
                        }
                    }
                } else if (parameter0 == "course"){
                    // insert courrse course_id to semester semester_id
                    iss >> numberParameter1;
                    iss >> parameter1;
                    if(parameter1 == "to"){
                        iss >> parameter2;
                        if(parameter2 == "semester"){
                            iss >> numberParameter2;
                            setCourseSemester(numberParameter1, numberParameter2);
                            continue;
                        }
                    }
                }
            } else if(command == "remove"){
                if(hasEnded == true){
                    throw HAS_ENDED;
                }
                iss >> parameter0;
                if(parameter0 == "student"){
                    // extract student student_id from course course_id
                    iss >> numberParameter1;
                    iss >> parameter1;
                    if(parameter1 == "from"){
                        iss >> parameter2;
                        if(parameter2 == "course"){
                            iss >> numberParameter2;
                            removeStudent(numberParameter1, numberParameter2);
                            continue;
                        }
                    }
                } else if (parameter0 == "professor"){
                    // extract professor professor_id from course course_id
                    iss >> numberParameter1;
                    iss >> parameter1;
                    if(parameter1 == "from"){
                        iss >> parameter2;
                        if(parameter2 == "course"){
                            iss >> numberParameter2;
                            removeProfessor(numberParameter1, numberParameter2);
                            continue;
                        }
                    }
                } else if (parameter0 == "course"){
                    // extract courrse course_id from semester semester_id
                    iss >> numberParameter1;
                    iss >> parameter1;
                    if(parameter1 == "from"){
                        iss >> parameter2;
                        if(parameter2 == "semester"){
                            iss >> numberParameter2;
                            removeCourseSemester(numberParameter1, numberParameter2);
                            continue;
                        }
                    }
                }           
            }

            throw   UNKNOWN_COMMAND;
        
        } catch(Error_signal err){
            std::cout << std::endl << ANSI_LIGHT_RED;
            switch (err) 
            {
            case INCORRECT_ID:
                std::cout << "ERROR: use of id that does not exist." << std::endl;
                break;
            case NO_SEMESTERS:
                std::cout << "ERROR: tried to remove a semester but there are already zero semesters." << std::endl;
                break;
            case INCORRECT_GENDER:
                std::cout << "ERROR: incorrect input for gender, should be male, female or other." << std::endl;
                break;
            case INCORRECT_YES_NO_ANSWER:
                std::cout << "ERROR: incorrect input for yes or no question, should be yes or no, input is case sensitive!" << std::endl;
                break;
            case CANT_REGISTER_TO_COURSE:
                std::cout << "ERROR: student cannot register to specified course, course needs to be in semester of current season and not greater year than then student." << std::endl;
                break;
            case UNKNOWN_COMMAND:
                std::cout << "ERROR: unknown command, type help for a list of available commands." << std::endl;
                break;
            case COURSE_HAS_NO_SEMESTER:
                std::cout << "ERROR: tried to register a student to a course that has not been assigned to a semester." << std::endl;
                break;
            case COURSE_NOT_IN_SEMESTER:
                std::cout << "ERROR: the course was not in that semester" << std::endl;
                break;
            case OPEN_FILE_ERROR:
                std::cout << "ERROR: there was a problem while trying to open the file" << std::endl;
                break;
            case COURSE_NOT_IN_CURRENT_SEASON:
                std::cout << "ERROR: course was not in current season" << std::endl;
                break;
            case HAS_ENDED:
                std::cout << "ERROR: season has ended, you cannot make changes, start new season by writing next season or print results of current season." << std::endl;
                break;
            case STRING_INSTEAD_OF_INTEGER:
                std::cout << "ERROR: expected integer as input but recieved something else" << std::endl;
                break;
            default:
                std::cout << "ERROR: something caused an error, not sure what." << std::endl;
                break;
            }
            std::cout << ANSI_RESET;
        }
    }
}

void Life::createStudent(){
    std::string FirstName, LastName, gender_string;
    int Age, year;
    std::cout << std::endl << ANSI_LIGHT_GRAY << "Student First Name: " << ANSI_RESET; std::cin >> FirstName;
    std::cout << ANSI_LIGHT_GRAY << "Student Last Name: " << ANSI_RESET; std::cin >> LastName;
    std::cout << ANSI_LIGHT_GRAY << "Student Age: " << ANSI_RESET;
    if(!(std::cin >> Age)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw STRING_INSTEAD_OF_INTEGER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Student Gender (male, female or other): " << ANSI_RESET; std::cin >> gender_string;
    if(gender_string != "male" && gender_string != "female" && gender_string != "other"){
        std::cin.ignore(); // Consume the newline character left in the stream
        throw INCORRECT_GENDER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Student year in university: " << ANSI_RESET;
    if(!(std::cin >> year)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw STRING_INSTEAD_OF_INTEGER;
    }
    Gender gender(gender_string);
    Person person(FirstName, LastName, Age, gender);
    int id = DIT_Secretary->enrollStudent(person, year);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Student was created. He was assigned the student id " << id << std::endl << ANSI_RESET;
    std::cin.ignore(); // Consume the newline character left in the stream
}

void Life::createProfessor(){
    std::string FirstName, LastName, gender_string, fieldOfStudy;
    int Age;
    std::cout << ANSI_LIGHT_GRAY << std::endl <<  "Professor First Name: "  << ANSI_RESET; std::cin >> FirstName;
    std::cout << ANSI_LIGHT_GRAY << "Professor Last Name: "  << ANSI_RESET; std::cin >> LastName;
    std::cout << ANSI_LIGHT_GRAY << "Professor Age: "  << ANSI_RESET; 
    if(!(std::cin >> Age)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw STRING_INSTEAD_OF_INTEGER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Professor Gender (male, female or other): "  << ANSI_RESET; std::cin >> gender_string;
    std::cin.ignore(); // Consume the newline character left in the stream
    if(gender_string != "male" && gender_string != "female" && gender_string != "other"){
        throw INCORRECT_GENDER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Professor field of study: "  << ANSI_RESET; 
    std::getline(std::cin, fieldOfStudy);
    Gender gender(gender_string);
    Person person(FirstName, LastName, Age, gender);
    int id = DIT_Secretary->hireProfessor(person, fieldOfStudy);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Professor was created. He was assigned the employee id " << id << ANSI_RESET << std::endl;
}

void Life::createCourse(){
    std::string name, isOptional_string;
    int points;
    std::cout << ANSI_LIGHT_GRAY << std::endl << "Course Name: " << ANSI_RESET;
    std::getline(std::cin, name);
    std::cout << ANSI_LIGHT_GRAY<< "Course points: " << ANSI_RESET; 
    if (!(std::cin >> points)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw STRING_INSTEAD_OF_INTEGER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Is course optional? (yes or no): " << ANSI_RESET, std::cin >> isOptional_string;
    if(isOptional_string != "yes" && isOptional_string != "no"){
        std::cin.ignore(); // Consume the newline character left in the stream
        throw INCORRECT_YES_NO_ANSWER;
    }
    bool isOptional = false;
    if(isOptional_string == "yes")
        isOptional = true;
    int id = DIT_Secretary->createNewCourse(name, points, isOptional);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Course was created. It was assigned the course id " << id << ANSI_RESET << std::endl;
    std::cin.ignore(); // Consume the newline character left in the stream
}
    
void Life::createSemester(){
    int id = DIT_Secretary->createNewSemester();
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Semester " << id << " was created!" << ANSI_RESET << std::endl;
}
    
void Life::updateStudent(int studentId){
    if(!isInMap(DIT_Secretary->students, studentId)){
        throw INCORRECT_ID;
    }
    std::string FirstName, LastName, gender_string;
    int Age, year;
    std::cout << ANSI_LIGHT_GRAY << std::endl << "Student First Name: " << ANSI_RESET; std::cin >> FirstName;
    std::cout << ANSI_LIGHT_GRAY << "Student Last Name: " << ANSI_RESET; std::cin >> LastName;
    std::cout << ANSI_LIGHT_GRAY << "Student Age: " << ANSI_RESET; 
    if(!(std::cin >> Age)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw STRING_INSTEAD_OF_INTEGER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Student Gender (male, female or other): " << ANSI_RESET; std::cin >> gender_string;
    if(gender_string != "male" && gender_string != "female" && gender_string != "other"){
        std::cin.ignore(); // Consume the newline character left in the stream
        throw INCORRECT_GENDER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Student year in university: " << ANSI_RESET;
    if(!(std::cin >> year)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw STRING_INSTEAD_OF_INTEGER;
    }
    Gender gender(gender_string);
    Person person(FirstName, LastName, Age, gender);
    DIT_Secretary->updateStudent(studentId, person, year);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "The student has been updated!" << ANSI_RESET << std::endl;
    std::cin.ignore(); // Consume the newline character left in the stream
}

void Life::updateProfessor(int professorId){
    if(!isInMap(DIT_Secretary->professors, professorId)){  
        throw INCORRECT_ID;
    }
    std::string FirstName, LastName, gender_string, fieldOfStudy;
    int Age;
    std::cout << ANSI_LIGHT_GRAY << std::endl << "Professor First Name: " << ANSI_RESET; std::cin >> FirstName;
    std::cout << ANSI_LIGHT_GRAY << "Professor Last Name: " << ANSI_RESET; std::cin >> LastName;
    std::cout << ANSI_LIGHT_GRAY << "Professor Age: " << ANSI_RESET; 
    if(!(std::cin >> Age)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw STRING_INSTEAD_OF_INTEGER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Professor Gender (male, female or other): " << ANSI_RESET; std::cin >> gender_string;
    std::cin.ignore(); // Consume the newline character left in the stream
    if(gender_string != "male" && gender_string != "female" && gender_string != "other"){
        throw INCORRECT_GENDER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Professor field of study: " << ANSI_RESET;
    std::getline(std::cin, fieldOfStudy);
    Gender gender(gender_string);
    Person person(FirstName, LastName, Age, gender);
    DIT_Secretary->updateProfessor(professorId, person, fieldOfStudy);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "The professor has been updated!" << ANSI_RESET << std::endl;
}
    
void Life::updateCourse(int courseId){
    if(!isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    std::string name, isOptional_string;
    int points;
    std::cout << ANSI_LIGHT_GRAY << std::endl << "Course Name: " << ANSI_RESET;
    std::getline(std::cin, name);
    std::cout << ANSI_LIGHT_GRAY << "Course points: " << ANSI_RESET;
    if (!(std::cin >> points)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw STRING_INSTEAD_OF_INTEGER;
    }
    std::cout << ANSI_LIGHT_GRAY << "Is course optional? (yes or no): " << ANSI_RESET, std::cin >> isOptional_string;
    if(isOptional_string != "yes" && isOptional_string != "no"){
        throw INCORRECT_YES_NO_ANSWER;
    }
    bool isOptional = false;
    if(isOptional_string == "yes")
        isOptional = true;
    DIT_Secretary->updateCourse(courseId, name, points, isOptional);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "The course has been updated!" << ANSI_RESET << std::endl;
    std::cin.ignore(); // Consume the newline character left in the stream
}

void Life::deleteSemester(){
    if(DIT_Secretary->semesters.size() == 0){
        throw NO_SEMESTERS;
    }
    DIT_Secretary->removeLastSemester();
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Last semester has been deleted." << ANSI_RESET << std::endl;
}

void Life::deleteStudent(int studentId){
    if(!isInMap(DIT_Secretary->students, studentId)){
        throw INCORRECT_ID;
    }
    DIT_Secretary->removeStudent(studentId);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "The student has been deleted!" << ANSI_RESET << std::endl;
}

void Life::deleteProfessor(int professorId){
    if(!isInMap(DIT_Secretary->professors, professorId)){
        throw INCORRECT_ID;
    }
    DIT_Secretary->fireProfessor(professorId);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "The professor has been fired!" << ANSI_RESET << std::endl;
}

void Life::deleteCourse(int courseId){
    if(!isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    DIT_Secretary->removeCourse(courseId);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "The course has been deleted!" << ANSI_RESET << std::endl;
}

void Life::listStudents(){
    std::cout << std::endl;
    for (const auto& pair : DIT_Secretary->students) {
        Student* student = pair.second;
        student->printStudent();
        std::cout << std::endl;
    }
}

void Life::listProfessors(){
    std::cout << std::endl;
    for (const auto& pair : DIT_Secretary->professors) {
        Professor* professor = pair.second;
        professor->printProfessor();
        std::cout << std::endl;
    }
}

void Life::listCourses(){
    std::cout << std::endl;
    for (const auto& pair : DIT_Secretary->courses) {
        Course* course = pair.second;
        course->printCourse();
        std::cout << std::endl;
    }
}

void Life::listSemesters(){
    std::cout << std::endl;
    for (std::size_t i = 0; i < DIT_Secretary->semesters.size(); ++i) {
        Semester* semester = DIT_Secretary->semesters[i];
        semester->printSemester();
        std::cout << std::endl;
    }
}

void Life::registerStudent(int studentId, int courseId){
    if(!isInMap(DIT_Secretary->students, studentId) || !isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    Student* student = DIT_Secretary->students[studentId];
    Course* course = DIT_Secretary->courses[courseId];
    if(course->getSemester() == nullptr){
        throw COURSE_HAS_NO_SEMESTER; 
    }
    if(course->getSemester()->getSeason().toString() != currentSeason.toString() || course->getSemester()->getYear() > student->getYear()){
        throw CANT_REGISTER_TO_COURSE;
    }
    DIT_Secretary->registerInCourse(course, student);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Student " << student->getFullName() << " registered to course " << course->getName() << ". " << ANSI_RESET << std::endl;
}

void Life::assignProfessor(int professorId, int courseId){
    if(!isInMap(DIT_Secretary->professors, professorId) || !isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    Professor* professor = DIT_Secretary->professors[professorId];
    Course* course = DIT_Secretary->courses[courseId];
    DIT_Secretary->assignProffessorToCourse(course, professor);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Professor " << professor->getFullName() << " assigned to course " << course->getName() << ". " << ANSI_RESET << std::endl;
}
    
void Life::setCourseSemester(int courseId, int semesterId){
    if((std::vector<Semester*>::size_type)semesterId > DIT_Secretary->semesters.size() || semesterId == 0 || !isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    Course* course = DIT_Secretary->courses[courseId];
    Semester* semester = DIT_Secretary->semesters[semesterId - 1];
    DIT_Secretary->addCourseToSemester(currentSeason, semester, course);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Course " << course->getName() << " added to semester " << semester->getId() << ". " << ANSI_RESET << std::endl;
}

void Life::removeStudent(int studentId, int courseId){
    if(!isInMap(DIT_Secretary->students, studentId) || !isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    Student* student = DIT_Secretary->students[studentId];
    Course* course = DIT_Secretary->courses[courseId];
    DIT_Secretary->unregisterFromCourse(course, student);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Student " << student->getFullName() << " unregistered from course " << course->getName() << ". " << ANSI_RESET << std::endl;
}
    
void Life::removeProfessor(int professorId, int courseId){
    if(!isInMap(DIT_Secretary->professors, professorId) || !isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    Professor* professor = DIT_Secretary->professors[professorId];
    Course* course = DIT_Secretary->courses[courseId];
    DIT_Secretary->removeProfessorFromCourse(course, professor);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Professor " << professor->getFullName() << " removed from course " << course->getName() << ". " << ANSI_RESET << std::endl;
}
    
void Life::removeCourseSemester(int courseId, int semesterId){
    if(!isInMap(DIT_Secretary->courses, courseId) || (std::vector<Semester*>::size_type)semesterId > DIT_Secretary->semesters.size() || semesterId == 0){
        throw INCORRECT_ID;
    }
    Course* course = DIT_Secretary->courses[courseId];
    Semester* semester = DIT_Secretary->semesters[semesterId];
    if(course->getSemester() != semester){
        throw COURSE_NOT_IN_SEMESTER;
    }
    DIT_Secretary->removeCourseFromSemester(semester, course);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "Course " << course->getName() << " removed from semester " << semester->getId() << ". " << ANSI_RESET << std::endl;
}
    
void Life::end_season(){
    DIT_Secretary->doTheExams(currentSeason);
    std::cout << std::endl << ANSI_LIGHT_BLUE << "All students have written the exams and their grades have been published." << ANSI_RESET << std::endl;
    std::cout << ANSI_LIGHT_GRAY <<  "Feel free ree to check out the results before starting the next season!" << ANSI_RESET << std::endl;
    hasEnded = true;
}

void Life::begin_next_season(){
    std::cout << std::endl << ANSI_LIGHT_BLUE << "Next season has just started. It now is " << currentSeason.toString() << "." << ANSI_RESET << std::endl;
    std::cout << ANSI_LIGHT_GRAY << "Please help the students choose their new courses. Feel free to make changes to the school too if you want." << ANSI_RESET << std::endl;
    DIT_Secretary->clearStudentClasses();
    currentSeason++;
    hasEnded = false;
}

void Life::listGraduates(){
    std::cout << std::endl << ANSI_LIGHT_BLUE << "Printing all students who meet the criteria for graduating: " << ANSI_RESET << std::endl;
    std::cout << ANSI_LIGHT_GRAY << "Note: They can graduate with the current courses system, if you make changes to courses they may no longer be able to graduate." << ANSI_RESET << std::endl << std::endl;
    DIT_Secretary->printWhoCanGraduate();
}

void Life::printProfessorStatistics(int professorId){
    if(!isInMap(DIT_Secretary->professors, professorId)){
        throw INCORRECT_ID;
    }
    Professor* professor = DIT_Secretary->professors[professorId];
    std::cout << std::endl << ANSI_LIGHT_GRAY << "Printing some statistics of current season about professor " << professor->getFullName() << ": " << ANSI_RESET << std::endl;
    DIT_Secretary->printStatistics(currentSeason, professor);
}

void Life::printStudentGrades(int studentId){
    if(!isInMap(DIT_Secretary->students, studentId)){
        throw INCORRECT_ID;
    }
    Student* student = DIT_Secretary->students[studentId];
    std::cout << std::endl << ANSI_LIGHT_GRAY << "Printing grades of all courses taken by student " << student->getFullName() << ": " << std::endl << ANSI_RESET;
    DIT_Secretary->printGrades(student);
}

void Life::printResultsOfCourse(int courseId){
    if(!isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    Course* course = DIT_Secretary->courses[courseId];
    if(course->getSemester() == nullptr || course->getSemester()->getSeason().toString() != currentSeason.toString()){
        throw COURSE_NOT_IN_CURRENT_SEASON;
    }
    std::cout << std::endl << ANSI_LIGHT_GRAY << "Printing the results of course " << course->getName() << "." << ANSI_RESET << std::endl;
    DIT_Secretary->printWhoPassed(currentSeason, course);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "The results were printed in the file." << ANSI_RESET << std::endl;    
}

void Life::printResultsOfCourseInFile(int courseId, const std::string& fileName){
    if(!isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    Course* course = DIT_Secretary->courses[courseId];
    if(course->getSemester() == nullptr || course->getSemester()->getSeason().toString() != currentSeason.toString()){
        throw COURSE_NOT_IN_CURRENT_SEASON;
    }
    std::cout << std::endl << ANSI_LIGHT_GRAY << "Printing the results of course " << course->getName() << " in file " << fileName << "." << ANSI_RESET << std::endl;
    DIT_Secretary->printWhoPassed(currentSeason, course, fileName);
    std::cout << std::endl << ANSI_LIGHT_GREEN << "The results were printed in the file." << ANSI_RESET << std::endl;
}

void Life::printCoursesOfSemester(int semesterId){
    if((std::vector<Semester*>::size_type)semesterId > DIT_Secretary->semesters.size() || semesterId == 0){
        throw INCORRECT_ID;
    }
    std::cout << std::endl;
    Semester* semester = DIT_Secretary->semesters[semesterId - 1];
    semester->printCourses();
}

void Life::printCurrentCoursesOfStudent(int studentId){
    if(!isInMap(DIT_Secretary->students, studentId)){
        throw INCORRECT_ID;
    }
    std::cout << std::endl;
    Student* student = DIT_Secretary->students[studentId];
    student->printCurrentCourses();
}

void Life::printCurrentStudentsOfCourse(int courseId){
    if(!isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    std::cout << std::endl;
    Course* course = DIT_Secretary->courses[courseId];
    course->printCurrentStudents();
}

void Life::printPassedCoursesOfStudent(int studentId){
    if(!isInMap(DIT_Secretary->students, studentId)){
        throw INCORRECT_ID;
    }
    std::cout << std::endl;
    Student* student = DIT_Secretary->students[studentId];
    student->printPassedCourses();
}

void Life::printCoursesOfProfessor(int professorId){
    if(!isInMap(DIT_Secretary->professors, professorId)){
        throw INCORRECT_ID;
    }
    std::cout << std::endl;
    Professor* professor = DIT_Secretary->professors[professorId];
    professor->printCourses();
}

void Life::printPassedStudentsOfCourse(int courseId){
    if(!isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    std::cout << std::endl;
    Course* course = DIT_Secretary->courses[courseId]; 
    course->printPassedStudents();   
}

void Life::printProfessorsOfCourse(int courseId){
    if(!isInMap(DIT_Secretary->courses, courseId)){
        throw INCORRECT_ID;
    }
    std::cout << std::endl;
    Course* course = DIT_Secretary->courses[courseId]; 
    course->printProfessors();   
}

void Life::importCourses(std::ifstream& file) {
    std::string line;    
    std::string courseName;
    int points;
    std::string type;

    std::cout << ANSI_LIGHT_GREEN;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
       if(!(iss >> courseName >> points >> type)){
        continue;
       }
        bool isOptional = false;
        if(type == "isOptional"){
            isOptional = true;
        }
        int id = DIT_Secretary->createNewCourse(courseName, points, isOptional);
        std::cout << std::endl << "Course " << courseName << " was added and assigned the id " << id << ".";
    }
    std::cout << ANSI_RESET << std::endl;
}

void Life::importProfessors(std::ifstream& file) {
    std::string line; 
    std::string last_name, first_name, gender_string, fieldOfStudy;
    int age;

    std::cout << ANSI_LIGHT_GREEN;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if(!(iss >> first_name >> last_name >> age >> gender_string)){
            continue;
        }
        std::getline(iss, fieldOfStudy);
        Gender gender(gender_string);
        int id = DIT_Secretary->hireProfessor(Person(first_name, last_name, age, gender), fieldOfStudy);
        std::cout << std::endl << "Professor " << first_name << " " << last_name << " was added and assigned the id " << id << ".";
    }
    std::cout << ANSI_RESET << std::endl;
}

void Life::importSemesters(std::ifstream& file) {
    std::string line; 
    int numberOfSemesters;
    std::cout << ANSI_LIGHT_GREEN;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        if(!(iss >> numberOfSemesters)){
            return;
        }
        for(int i = 1; i <= numberOfSemesters; i++){
            int id = DIT_Secretary->createNewSemester();
            std::cout << std::endl << "Created semester " << id << ".";
        }
    } else{
        std::cout << "ERROR" << std::endl;
    }
    std::cout << ANSI_RESET << std::endl;
}

void Life::importStudents(std::ifstream& file) {
    std::string line; 
    std::string last_name, first_name, gender_string;
    int age, year;
    std::cout << ANSI_LIGHT_GREEN;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if(!(iss >> first_name >> last_name >> age >> gender_string >> year)){
            continue;
        }
        Gender gender(gender_string);
        int id = DIT_Secretary->enrollStudent(Person(first_name, last_name, age, gender), year);
        std::cout << std::endl << "Student " << first_name << " " << last_name << " was enrolled into the university and assigned the id " << id << ".";
    }
    std::cout << ANSI_RESET << std::endl;
}

void Life::importFromFile(std::string fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        throw OPEN_FILE_ERROR;
    }

    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    std::string keyword;

    iss >> keyword;

    if (keyword == "courses") {
        importCourses(file);
    } else if (keyword == "professors") {
        importProfessors(file);
    } else if (keyword == "semesters") {
        importSemesters(file);
    } else if (keyword == "students") {
        importStudents(file);
    }
    // Add more conditions for other keywords as needed

    file.close();
}

void Life::help(){
    std::cout << std::endl;    
    std::cout << ANSI_LIGHT_BLUE << " help" << "                                                 - " << ANSI_LIGHT_GRAY << "prints a list of all available commands." << std::endl;    
    std::cout << ANSI_LIGHT_BLUE << " clear" << "                                                - " << ANSI_LIGHT_GRAY << "clears the terminal" << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " exit" << "                                                 - " << ANSI_LIGHT_GRAY << "exits the program" << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " end season" << "                                           - " << ANSI_LIGHT_GRAY << "ends season, students take exams and professors grade them" << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " next season" << "                                          - " << ANSI_LIGHT_GRAY << "starts next season, students are unregistered from all courses." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " import file_name" << "                                     - " << ANSI_LIGHT_GRAY << "imports data from a file." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " create student" << "                                       - " << ANSI_LIGHT_GRAY << "creates a student." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " create professor" << "                                     - " << ANSI_LIGHT_GRAY << "creates a professsor." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " create course" << "                                        - " << ANSI_LIGHT_GRAY << "creates a course." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " create semester" << "                                      - " << ANSI_LIGHT_GRAY << "creates a new semester." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " update student id" << "                                    - " << ANSI_LIGHT_GRAY << "updates info of student who has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " update professor id" << "                                  - " << ANSI_LIGHT_GRAY << "updates info of course that has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " update course id" << "                                     - " << ANSI_LIGHT_GRAY << "updates info of professor who has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " delete student id" << "                                    - " << ANSI_LIGHT_GRAY << "deletes student of specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " delete professor id" << "                                  - " << ANSI_LIGHT_GRAY << "deletes professor of specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " delete course id" << "                                     - " << ANSI_LIGHT_GRAY << "deletes course of specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " delete semester" << "                                      - " << ANSI_LIGHT_GRAY << "deletes last semester" << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print current courses of student id" << "                  - " << ANSI_LIGHT_GRAY << "prints current courses of student who has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print current students of course id" << "                  - " << ANSI_LIGHT_GRAY << "prints current students of course that has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print passed courses of student id" << "                   - " << ANSI_LIGHT_GRAY << "prints passed courses of student who has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print passed students of course id" << "                   - " << ANSI_LIGHT_GRAY << "prints passed students of course that has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print students" << "                                       - " << ANSI_LIGHT_GRAY << "prints all students." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print professors" << "                                     - " << ANSI_LIGHT_GRAY << "prints all professors." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print professors of course id" << "                        - " << ANSI_LIGHT_GRAY << "prints professors of course that has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print courses" << "                                        - " << ANSI_LIGHT_GRAY << "prints all courses." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print courses of semester id" << "                         - " << ANSI_LIGHT_GRAY << "prints courses of semester that has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print courses of professor id" << "                        - " << ANSI_LIGHT_GRAY << "prints courses of professor who has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print semesters" << "                                      - " << ANSI_LIGHT_GRAY << "prints all semesters." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print graduates" << "                                      - " << ANSI_LIGHT_GRAY << "prints all people who meet the criteria for graduating" << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print professor id statistics" << "                        - " << ANSI_LIGHT_GRAY << "prints statistics of professor who has specified id for the last season." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print student id grades" << "                              - " << ANSI_LIGHT_GRAY << "prints grades of student who has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print exam results of course id" << "                      - " << ANSI_LIGHT_GRAY << "prints exam results of course that has specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " print exam results of course id in file_name" << "         - " << ANSI_LIGHT_GRAY << "prints results results of course that has specified id in a file." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " add student student_id to course course_id" << "           - " << ANSI_LIGHT_GRAY << "adds student of specified id to course of specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " add professor professor_id to course course_id" << "       - " << ANSI_LIGHT_GRAY << "adds professor of specified id to course of specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " add course course_id to semester semester_id" << "         - " << ANSI_LIGHT_GRAY << "adds course of specified id to semester of specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " remove student student_id from course course_id" << "      - " << ANSI_LIGHT_GRAY << "removes studnet of specified id from course of specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " remove professor professor_id from course course_id" << "  - " << ANSI_LIGHT_GRAY << "removes professor of specified id from course of specified id." << std::endl;
    std::cout << ANSI_LIGHT_BLUE << " remove course course_id from semester semester_id" << "    - " << ANSI_LIGHT_GRAY  << "removes course of specified id from semester of specified id." << std::endl;
}