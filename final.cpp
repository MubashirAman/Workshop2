#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

struct Student {
    string name;
    int rollNo;
    string department;
    float gpa;
    string contact;
};

vector<Student> students;

// ===== File Handling =====
void saveToFile() {
    ofstream file("students.txt");
    for (auto &s : students) {
        file << s.name << "," << s.rollNo << "," << s.department << ","
             << s.gpa << "," << s.contact << "\n";
    }
    file.close();
}

void loadFromFile() {
    students.clear();
    ifstream file("students.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Student s;
        getline(ss, s.name, ',');
        ss >> s.rollNo;
        ss.ignore();
        getline(ss, s.department, ',');
        ss >> s.gpa;
        ss.ignore();
        getline(ss, s.contact, ',');
        students.push_back(s);
    }
    file.close();
}

// ===== Add, Update, Delete =====
void addStudent() {
    Student s;
    cout << "Enter Name: "; getline(cin >> ws, s.name);
    cout << "Enter Roll Number: "; cin >> s.rollNo;
    cout << "Enter Department: "; cin >> s.department;
    cout << "Enter GPA: "; cin >> s.gpa;
    cout << "Enter Contact: "; cin >> s.contact;

    for (auto &st : students) {
        if (st.rollNo == s.rollNo) {
            cout << "Error: Roll number already exists.\n";
            return;
        }
    }

    students.push_back(s);
    saveToFile();
    cout << "Student added successfully.\n";
}

void updateStudent() {
    int roll;
    cout << "Enter Roll Number to Update: ";
    cin >> roll;

    for (auto &s : students) {
        if (s.rollNo == roll) {
            cout << "Enter new GPA: ";
            cin >> s.gpa;
            cout << "Enter new Contact: ";
            cin >> s.contact;
            saveToFile();
            cout << "Record updated.\n";
            return;
        }
    }
    cout << "Record not found.\n";
}

void deleteStudent() {
    int roll;
    cout << "Enter Roll Number to Delete: ";
    cin >> roll;

    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].rollNo == roll) {
            students.erase(students.begin() + i);
            saveToFile();
            cout << "Record deleted.\n";
            return;
        }
    }
    cout << "Record not found.\n";
}

// ===== Display, Search, Sort =====
void displayAll() {
    if (students.empty()) {
        cout << "No records found.\n";
        return;
    }

    cout << left << setw(15) << "Name" << setw(10) << "Roll No"
         << setw(15) << "Dept" << setw(10) << "GPA"
         << setw(15) << "Contact" << endl;

    for (auto &s : students)
        cout << setw(15) << s.name << setw(10) << s.rollNo
             << setw(15) << s.department << setw(10) << s.gpa
             << setw(15) << s.contact << endl;
}

void searchByName(string name) {
    bool found = false;
    for (auto &s : students) {
        if (s.name == name) {
            cout << "Found: " << s.name << " | Roll: " << s.rollNo
                 << " | Dept: " << s.department << " | GPA: " << s.gpa
                 << " | Contact: " << s.contact << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No record found with that name.\n";
}

void sortByGPA() {
    sort(students.begin(), students.end(),
         [](Student a, Student b) { return a.gpa > b.gpa; });
    cout << "Records sorted by GPA.\n";
}

// ===== Interface =====
void menu() {
    int choice;
    loadFromFile();
    do {
        cout << "\n===== Student Record Management Menu =====\n";
        cout << "1. Add Student\n2. Update Student\n3. Delete Student\n";
        cout << "4. Display All Students\n5. Search by Name\n6. Sort by GPA\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: displayAll(); break;
            case 5: {
                string name;
                cout << "Enter name: ";
                getline(cin, name);
                searchByName(name);
                break;
            }
            case 6: sortByGPA(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

// ===== Main Function =====
int main() {
    cout << "===== Student Record Management System =====\n";
    menu();
    return 0;
}
