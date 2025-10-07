
#include <iostream>
#include <vector>
#include "FileHandler.h"
#include "RecordManager.h"
#include "DisplaySearch.h"
using namespace std;

int main() {
    vector<Student> students = FileHandler::loadFromFile();
    int choice;
    do {
        cout << "\n===== Student Record Management System =====\n";
        cout << "1. Add New Student\n2. Update Student\n3. Delete Student\n";
        cout << "4. View All Students\n5. View Specific Student\n";
        cout << "6. Search by Name\n7. Search by Department\n";
        cout << "8. Sort by GPA\n9. Sort by Roll Number\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: RecordManager::addStudent(students); break;
            case 2: RecordManager::updateStudent(students); break;
            case 3: RecordManager::deleteStudent(students); break;
            case 4: DisplaySearch::displayAll(students); break;
            case 5: DisplaySearch::viewSpecific(students); break;
            case 6: DisplaySearch::searchByName(students); break;
            case 7: DisplaySearch::searchByDepartment(students); break;
            case 8: DisplaySearch::sortByGPA(students); break;
            case 9: DisplaySearch::sortByRoll(students); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n"; break;
        }
    } while (choice != 0);
    return 0;
}
