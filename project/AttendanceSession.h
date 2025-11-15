#pragma once
#include <string>
using namespace std;
class AttendanceSession {
public:
    string sessionID;
    string date;      
    string classID;
    string lecturerID;
    AttendanceSession(string sid = "ses1", string d = "2025-01-01", string cid = "", string lid = "")
        : sessionID(sid), date(d), classID(cid), lecturerID(lid) {
    }
};

