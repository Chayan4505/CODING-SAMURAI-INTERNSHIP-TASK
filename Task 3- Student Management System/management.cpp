#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    int roll;
    string name;
    float marks;
};

vector<Student> students;

void loadData() {
    students.clear();
    ifstream in("students.txt");
    Student s;
    while (in >> s.roll) {
        in.ignore();
        getline(in, s.name);
        in >> s.marks;
        students.push_back(s);
    }
    in.close();
}

void saveData() {
    ofstream out("students.txt");
    for (auto s : students) {
        out << s.roll << endl;
        out << s.name << endl;
        out << s.marks << endl;
    }
    out.close();
}

void addStudent() {
    Student s;
    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Marks: ";
    cin >> s.marks;
    students.push_back(s);
    saveData();
    cout << "Student added.\n";
}

void displayAll() {
    for (auto s : students) {
        cout << "Roll: " << s.roll << ", Name: " << s.name << ", Marks: " << s.marks << endl;
    }
}

void searchStudent() {
    int r;
    cout << "Enter roll number to search: ";
    cin >> r;
    for (auto s : students) {
        if (s.roll == r) {
            cout << "Found: Name: " << s.name << ", Marks: " << s.marks << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

void updateStudent() {
    int r;
    cout << "Enter roll number to update: ";
    cin >> r;
    for (auto &s : students) {
        if (s.roll == r) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, s.name);
            cout << "Enter new marks: ";
            cin >> s.marks;
            saveData();
            cout << "Student updated.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void deleteStudent() {
    int r;
    cout << "Enter roll number to delete: ";
    cin >> r;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->roll == r) {
            students.erase(it);
            saveData();
            cout << "Student deleted.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

int main() {
    loadData();
    int choice;
    while (true) {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n2. View All Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
    }

    return 0;
}
