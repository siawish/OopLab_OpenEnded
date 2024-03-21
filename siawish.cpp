
// Teacher class
class Teacher {
private:
    int teacherID;
    string name;
    string email;
    vector<Course*> coursesTaught;

public:
    // Constructor
    Teacher(int id, const string& n, const string& e) : teacherID(id), name(n), email(e) {}

    // Getter methods
    int getTeacherID() const { return teacherID; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    // Methods
    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses() const;

    // File handling methods
    void saveToFile() const;
    void loadFromFile();
};


// Teacher methods
void Teacher::assignCourse(Course* course) {
    coursesTaught.push_back(course);
    cout << "Course " << course->getCourseCode() << " assigned to teacher " << name << "." << endl;
}

void Teacher::removeCourse(Course* course) {
    auto it = find(coursesTaught.begin(), coursesTaught.end(), course);
    if (it != coursesTaught.end()) {
        coursesTaught.erase(it);
        cout << "Course " << course->getCourseCode() << " removed from teacher " << name << "." << endl;
    }
    else {
        cout << "Course " << course->getCourseCode() << " is not assigned to teacher " << name << "." << endl;
    }
}

void Teacher::viewCourses() const {
    cout << "Courses taught by teacher " << name << ":" << endl;
    for (const auto& course : coursesTaught) {
        cout << course->getCourseCode() << " - " << course->getCourseName() << endl;
    }
}

void Teacher::saveToFile() const {
    ofstream outFile(to_string(teacherID) + "_teacher.txt");
    if (outFile.is_open()) {
        outFile << "Teacher ID: " << teacherID << endl;
        outFile << "Name: " << name << endl;
        outFile << "Email: " << email << endl;
        outFile << "Courses Taught:" << endl;
        for (const auto& course : coursesTaught) {
            outFile << course->getCourseCode() << " - " << course->getCourseName() << endl;
        }
        outFile.close();
        cout << "Teacher data saved to file." << endl;
    }
    else {
        cout << "Unable to save teacher data to file." << endl;
    }
}

void Teacher::loadFromFile() {
    ifstream inFile(to_string(teacherID) + "_teacher.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string key, value;
            ss >> key >> value;
            if (key == "Teacher" && value == "ID:") {
                ss >> teacherID;
            }
            else if (key == "Name:") {
                getline(ss, name);
                name = name.substr(1);
            }
            else if (key == "Email:") {
                ss >> email;
            }
            else if (key == "Courses" && value == "Taught:") {
                while (getline(inFile, line)) {
                    stringstream course_ss(line);
                    string courseCode, courseName;
                    course_ss >> courseCode >> courseName;
                    Course* course = new Course(courseCode, courseName, 0); // Capacity not known from file
                    coursesTaught.push_back(course);
                }
            }
        }
        inFile.close();
        cout << "Teacher data loaded from file." << endl;
    }
    else {
        cout << "Unable to load teacher data from file." << endl;
    }
}

int main() {
    vector<Student> students;
    vector<Course> courses;
    vector<Teacher> teachers;

    char choice;

    do {
        cout << "\nChoose an option:\n";
        cout << "1. Add Student\n";
        cout << "2. Add Course\n";
        cout << "3. Add Teacher\n";
        cout << "4. Display Info\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
        case '1': {
            string name, email;
            cout << "\nEnter student name: ";
            cin >> name;
            cout << "Enter student email: ";
            cin >> email;
            students.push_back(Student(studentCounter++, name, email));
            break;
        }
        case '2': {
            string code, name;
            int capacity;
            cout << "\nEnter course code: ";
            cin >> code;
            cout << "Enter course name: ";
            cin >> name;
            cout << "Enter max capacity: ";
            cin >> capacity;
            courses.push_back(Course(code, name, capacity));
            break;
        }
        case '3': {
            string name, email;
            cout << "\nEnter teacher name: ";
            cin >> name;
            cout << "Enter teacher email: ";
            cin >> email;
            teachers.push_back(Teacher(teachers.size() + 1, name, email));
            break;
        }
        case '4':
            // Displaying Information
            cout << "\nStudent Information:\n";
            for (const auto& student : students) {
                cout << "Student ID: " << student.getStudentID() << endl;
                cout << "Name: " << student.getName() << endl;
                cout << "Email: " << student.getEmail() << endl;
                student.viewCourses();
                cout << endl;
            }

            // Display course information
            cout << "\nCourse Information:\n";
            for (const auto& course : courses) {
                cout << "Course Code: " << course.getCourseCode() << endl;
                cout << "Course Name: " << course.getCourseName() << endl;
                course.viewStudents();
                cout << endl;
            }

            // Display teacher information
            cout << "\nTeacher Information:\n";
            for (const auto& teacher : teachers) {
                cout << "Teacher ID: " << teacher.getTeacherID() << endl;
                cout << "Name: " << teacher.getName() << endl;
                cout << "Email: " << teacher.getEmail() << endl;
                teacher.viewCourses();
                cout << endl;
            }
            break;
        case '5':
            cout << "Exiting the program.\n";
            return 0; // Exit the program
        default:
            cout << "Invalid choice. Please enter again.\n";
            break;
        }

    } while (true);



    // Save data to files
    for (auto& student : students) {
        student.saveToFile();
    }
    for (auto& course : courses) {
        course.saveToFile();
    }
    for (auto& teacher : teachers) {
        teacher.saveToFile();
    }
    cout << "Data saved to files." << endl;

    // Load data from files
    for (auto& student : students) {
        student.loadFromFile();
    }
    for (auto& course : courses) {
        course.loadFromFile();
    }
    for (auto& teacher : teachers) {
        teacher.loadFromFile();
    }
    cout << "Data loaded from files." << endl;

    // Display student information
    cout << "\nStudent Information:\n";
    for (const auto& student : students) {
        cout << "Student ID: " << student.getStudentID() << endl;
        cout << "Name: " << student.getName() << endl;
        cout << "Email: " << student.getEmail() << endl;
        student.viewCourses();
        cout << endl;
    }

    // Display course information
    cout << "\nCourse Information:\n";
    for (const auto& course : courses) {
        cout << "Course Code: " << course.getCourseCode() << endl;
        cout << "Course Name: " << course.getCourseName() << endl;
        course.viewStudents();
        cout << endl;
    }

    // Display teacher information
    cout << "\nTeacher Information:\n";
    for (const auto& teacher : teachers) {
        cout << "Teacher ID: " << teacher.getTeacherID() << endl;
        cout << "Name: " << teacher.getName() << endl;
        cout << "Email: " << teacher.getEmail() << endl;
        teacher.viewCourses();
        cout << endl;
    }

    return 0;
}