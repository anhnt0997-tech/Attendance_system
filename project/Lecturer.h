#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Class.h"
#include "AttendanceRecord.h"
using namespace std;


class Student;

class Lecturer {
public:
    string lecturerId;
    string fullName;
    string email;
    string phoneNumber;
    string password;

    Lecturer(string lid = "lecturer", string fn = "Lecturer", string em = "lecturer@mail.com", string pn = "0999888777", string pw = "123")
        : lecturerId(lid), fullName(fn), email(em), phoneNumber(pn), password(pw) {
    }

    // Xem danh sách lớp mình phụ trách
    void viewMyClasses(const vector<ClassRoom>& classesDB, const vector<Lecturer>& allLecturers, const vector<Student>& allStudents) const {
        cout << "\n=== My Class ===\n";
        bool hasClasses = false;

        for (int i = 0; i < classesDB.size(); i++) {
            bool mine = false;
            // Kiểm tra xem giảng viên này có phụ trách lớp không
            for (int j = 0; j < classesDB[i].lecturers.size(); j++) {
                if (classesDB[i].lecturers[j] == lecturerId) {
                    mine = true;
                    break;
                }
            }

            if (mine) {
                cout << "\nNumber class " << (hasClasses ? i + 1 : 1) << ":\n";
                classesDB[i].display(allLecturers, allStudents);
                hasClasses = true;
            }
        }

        if (!hasClasses) {
            cout << "Not class!\n";
        }
        else {
            cout << "Lecturer manage: " << classesDB.size() << " class\n";
        }
    }

    // điểm danh cho sinh viên trong lớp mình phụ trách thông qua index
    void markAttendanceByIndex(vector<AttendanceRecord>& attendanceDB, vector<ClassRoom>& classesDB) const
    {
        // chọn lớp cần điểm danh
        vector<int> IndexOfStudent;
        for (int i = 0; i < classesDB.size(); i++)
        {
            for (int j = 0; j < classesDB[i].lecturers.size(); j++)
            {
                if (classesDB[i].lecturers[j] == lecturerId)
                {
                    IndexOfStudent.push_back((int)i);
                    break;
                }
            }
        }
        if (IndexOfStudent.size() == 0)
        {
            cout << "You have no classes.\n";
            return;
        }
        cout << "Select class: \n";
        for (int k = 0; k < IndexOfStudent.size(); k++)
        {
            cout << (k + 1) << ") " << classesDB[IndexOfStudent[k]].classId << " - " << classesDB[IndexOfStudent[k]].className << endl;
        }
        int choice;
        cin >> choice;
        if (choice < 1 || choice >(int)IndexOfStudent.size())
        {
            cout << "Invalid choice.\n";
            return;
        }
        ClassRoom& selected = classesDB[IndexOfStudent[choice - 1]];
        if (selected.students.size() == 0)
        {
            cout << "Class has no students.\n";
            return;
        }
        cout << "Students: \n";
        for (int i = 0; i < selected.students.size(); i++)
        {
            cout << (i + 1) << ") " << selected.students[i] << endl;
        }
        cout << "Select student index: ";
        int sidx;
        cin >> sidx;
        if (sidx < 1 || sidx >(int)selected.students.size())
        {
            cout << "Invalid index.\n";
            return;
        }
        cout << "Status (Present/Late/Absent): ";
        string st;
        cin >> st;
        string recId = "rec" + to_string((int)attendanceDB.size() + 1);
        attendanceDB.push_back(AttendanceRecord(recId, selected.students[sidx - 1], selected.classId, st));
        cout << "Marked!\n";
    }

    // Xem bảng điểm danh
    void viewAttendance(const vector<AttendanceRecord>& attendanceDB) const
    {
        cout << "\nAttendance records:\n";
        for (int i = 0; i < attendanceDB.size(); i++)
        {
            cout << attendanceDB[i].studentId << ", Class: " << attendanceDB[i].classId << ", Status: " << attendanceDB[i].status << endl;
        }
    }
};

