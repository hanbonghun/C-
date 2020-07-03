#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include "Admin.h"
#include "Common.h"
#include "FileReadandWrite.h"
#include "Login.h"
#include "User.h"
#include "Util.h"
using namespace std;


int main() {
    int user = -1; //user index
    int status = -1;

    // Student Info
    vector<string> studentIds;
    vector<string> passwords;
    vector<string> names;
    vector<int> credits;
    vector<vector<string>> appliedLectureCodes;

    // Lecture Info
    vector<string> lectureCodes;
    vector<string> lectureNames;
    vector<int> lectureCredits;
    vector<int> limits;

    // Read from files
    readStudentFile(studentIds, passwords, names, credits, appliedLectureCodes);
    readLectureFile(lectureCodes, lectureNames, lectureCredits, limits);

    // Login phase
    while (status == -1) {
        user = login(studentIds, passwords);

        if (user == -999) { // Login fail
            exit(-999);
        }
        else if (user == -1) { // Exit command
            exit(-1);
        }
        else if (user == -100) { // Admin login success
            status = runAdmin(studentIds, passwords, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits);
        }
        else { // Student login success
            status = runStudent(studentIds, passwords, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
        }
    }
    writeStudentFile(studentIds, passwords, names, credits, appliedLectureCodes);
    writeLectureFile(lectureCodes, lectureNames, lectureCredits, limits);
    return 0;
}
