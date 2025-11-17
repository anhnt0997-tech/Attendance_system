#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Subject {
public:
    string subjectId;
    string subjectName;
    int creditNumber;
    string lecturerInCharge; // gv phụ trách
    vector<string> classList; // các classId thuc môn này
    Subject(string id = "SUB001", string name = "Subject", int credit = 3, string lec = "lecturer1")
        : subjectId(id), subjectName(name), creditNumber(credit), lecturerInCharge(lec) {
    }
    // Thêm lớp học
    void addClass(const string& classId)
    {
        if (find(classList.begin(), classList.end(), classId) == classList.end())
            classList.push_back(classId);
    }
    // Xem danh sách lớp học của môn
    void showClasses() const
    {
        cout << "Subject " << subjectId << ": " << subjectName << " (Number of credits: " << creditNumber << ", GV: " << lecturerInCharge << ")\n";
        cout << "Class lists:";
        for (const string& cid : classList)
            cout << " - " << cid << "\n";
    }
    void showInfo() const {
        cout << "SubjectId: " << subjectId << ", Name: " << subjectName << ", Credits: " << creditNumber << ", Lecturer: " << lecturerInCharge << endl;
    }
};

