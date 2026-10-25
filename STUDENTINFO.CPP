#include <iostream>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <limits>

using namespace std;
using namespace std::chrono;

// Structure to store student information
struct Student
{
    int id;
    char name[50];
    float cgpa;
};

// Function to display student information
void displayStudents(const Student* students, int n)
{
    cout << "\n========================================\n";
    cout << "         STUDENT INFORMATION\n";
    cout << "========================================\n";

    for (int i = 0; i < n; i++)
    {
        cout << "\nStudent " << i + 1 << endl;
        cout << "ID    : " << students[i].id << endl;
        cout << "Name  : " << students[i].name << endl;
        cout << "CGPA  : " << students[i].cgpa << endl;
    }

    cout << "\n========================================\n";
}

int main()
{
    Student* students = nullptr;
    int n;

    auto start = high_resolution_clock::now();

    // Input number of students
    cout << "========================================\n";
    cout << "       STUDENT INFORMATION SYSTEM\n";
    cout << "========================================\n";

    cout << "\nEnter Number of Students: ";
    cin >> n;

    // Validate number of students
    if (cin.fail() || n <= 0)
    {
        cout << "\nInvalid number of students!" << endl;
        return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Dynamic memory allocation using realloc()
    for (int i = 0; i < n; i++)
    {
        Student* temp = (Student*)realloc(
            students,
            (i + 1) * sizeof(Student)
        );

        // Check memory allocation
        if (temp == nullptr)
        {
            cout << "\nMemory allocation failed!" << endl;
            free(students);
            return 1;
        }

        students = temp;

        cout << "\n----------------------------------------\n";
        cout << "Enter Details for Student " << i + 1 << endl;
        cout << "----------------------------------------\n";

        // Input ID
        cout << "Enter ID: ";
        cin >> students[i].id;

        // Input name
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Name: ";
        cin.getline(students[i].name, 50);

        // Input CGPA
        cout << "Enter CGPA: ";
        cin >> students[i].cgpa;

        // Validate CGPA
        if (students[i].cgpa < 0 || students[i].cgpa > 10)
        {
            cout << "Invalid CGPA! Please enter CGPA between 0 and 10.\n";
            i--;
            continue;
        }
    }

    // Display all student information
    displayStudents(students, n);

    auto end = high_resolution_clock::now();

    // Calculate execution time
    auto duration = duration_cast<microseconds>(end - start);

    cout << "\nExecution Time: "
         << duration.count()
         << " microseconds" << endl;

    // Release dynamically allocated memory
    free(students);
    students = nullptr;

    cout << "\nProgram executed successfully! 😊" << endl;

    return 0;
}
