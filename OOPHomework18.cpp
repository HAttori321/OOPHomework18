#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class CourseManagementSystem
{
public:
    void loadFromFile(const string& filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening file" << endl;
            return;
        }
        string course, student;
        int grade;
        while (file >> course >> student >> grade)
        {
            addStudentToCourse(course, student, grade);
        }
    }
    void addStudentToCourse(const string& course, const string& student, int grade)
    {
        courses[course].emplace(student, grade);
        studentGrades[student][course] = grade;
        uniqueStudents.insert(student);
    }
    void updateStudentGrade(const string& course, const string& student, int grade)
    {
        if (studentGrades.find(student) != studentGrades.end() && studentGrades[student].find(course) != studentGrades[student].end())
        {
            studentGrades[student][course] = grade;
            courses[course][student] = grade;
        }
    }
    void removeStudentFromCourse(const string& course, const string& student)
    {
        if (courses.find(course) != courses.end() && courses[course].find(student) != courses[course].end())
        {
            courses[course].erase(student);
            studentGrades[student].erase(course);
            if (studentGrades[student].empty())
            {
                uniqueStudents.erase(student);
                studentGrades.erase(student);
            }
        }
    }
    void printCourses() const {
        for (const auto& course : courses)
        {
            cout << "Course: " << course.first << endl;
            for (const auto& student : course.second)
            {
                cout << "  Student: " << student.first << ", Grade: " << student.second << endl;
            }
        }
    }
    void printUniqueStudents() const
    {
        cout << "Unique students:" << endl;
        for (const auto& student : uniqueStudents)
        {
            cout << "  " << student << endl;
        }
    }
    void printStudentsByGrades() const
    {
        multimap<int, string> sortedStudents;
        for (const auto& student : studentGrades)
        {
            for (const auto& course : student.second)
            {
                sortedStudents.insert(make_pair(course.second, student.first));
            }
        }
        cout << "Students by grades:" << endl;
        for (auto it = sortedStudents.rbegin(); it != sortedStudents.rend(); ++it)
        {
            cout << "  Student: " << it->second << ", Grade: " << it->first << endl;
        }
    }
private:
    map<string, map<string, int>> courses;
    map<string, map<string, int>> studentGrades;
    set<string> uniqueStudents;
};
int main() 
{
    CourseManagementSystem cms;
    cms.loadFromFile("data.txt");
    cms.addStudentToCourse("course1", "student4", 92);
    cms.updateStudentGrade("course1", "student1", 95);
    cms.removeStudentFromCourse("course2", "student1");
    cms.printCourses();
    cms.printUniqueStudents();
    cms.printStudentsByGrades();
}