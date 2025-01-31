#include <iostream>
#include <vector>
#include <string>

// Base class
class Person {
protected:
    std::string name;
    int age;

public:
    Person(const std::string& name, int age) : name(name), age(age) {}
    virtual void display() const {
        std::cout << "Name: " << name << ", Age: " << age << "\n";
    }
    virtual ~Person() = default;
};

// Derived class - Student
class Student : public Person {
private:
    int studentID;

public:
    Student(const std::string& name, int age, int studentID)
        : Person(name, age), studentID(studentID) {
    }
    void display() const override {
        Person::display();
        std::cout << "Student ID: " << studentID << "\n";
    }
};

// Derived class - Teacher
class Teacher : public Person {
private:
    std::string subject;

public:
    Teacher(const std::string& name, int age, const std::string& subject)
        : Person(name, age), subject(subject) {
    }
    void display() const override {
        Person::display();
        std::cout << "Subject: " << subject << "\n";
    }
};

// Aggregation - Course
class Course {
private:
    std::string courseName;
    std::vector<Student*> students;

public:
    Course(const std::string& courseName) : courseName(courseName) {}
    void addStudent(Student* student) {
        students.push_back(student);
    }
    void display() const {
        std::cout << "Course: " << courseName << "\n";
        std::cout << "Enrolled Students:\n";
        for (const auto& student : students) {
            student->display();
        }
    }
};

// Composition - Department
class Department {
private:
    std::string departmentName;
    std::vector<Course> courses;

public:
    Department(const std::string& name) : departmentName(name) {}
    void addCourse(const Course& course) {
        courses.push_back(course);
    }
    void display() const {
        std::cout << "Department: " << departmentName << "\n";
        for (const auto& course : courses) {
            course.display();
        }
    }
};

// University - Composition example
class University {
private:
    std::string universityName;
    std::vector<Department> departments;

public:
    University(const std::string& name) : universityName(name) {}
    void addDepartment(const Department& department) {
        departments.push_back(department);
    }
    void display() const {
        std::cout << "University: " << universityName << "\n";
        for (const auto& department : departments) {
            department.display();
        }
    }
};

// Dependency - ReportCard
class ReportCard {
private:
    Student* student;
    std::vector<std::string> grades;

public:
    ReportCard(Student* student) : student(student) {}
    void addGrade(const std::string& grade) {
        grades.push_back(grade);
    }
    void display() const {
        std::cout << "Report Card for:\n";
        student->display();
        std::cout << "Grades:\n";
        for (const auto& grade : grades) {
            std::cout << "- " << grade << "\n";
        }
    }
};

// Main Function
int main() {
    // Create instances
    University uni("Lipetsk State Tech University");

    Department csDept("Institus of Computer Science");
    Department mathDept("Automation of control systems");

    Course cs101("AS 23-2");
    Course math101("II");

    Student s1("Ivan", 20, 104386834);
    Student s2("Egor", 21, 5239594603);

    cs101.addStudent(&s1);
    math101.addStudent(&s2);

    csDept.addCourse(cs101);
    mathDept.addCourse(math101);

    uni.addDepartment(csDept);
    uni.addDepartment(mathDept);

    Teacher t1("Vedishev V.V", 40, "Programming");

    ReportCard rc(&s1);
    rc.addGrade("100/100");
    rc.addGrade("100/100");

    // Display hierarchy
    uni.display();
    std::cout << "\n";
    t1.display();
    std::cout << "\n";
    rc.display();

    return 0;
}
