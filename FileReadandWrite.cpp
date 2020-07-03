#include "FileReadandWrite.h"
void readStudentFile(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
    string id, pw, name, lecturecode; //아이디, 비밀번호, 이름 ,수강 신청한 과목
    int Credits_available; //수강가능학점
    int enrol_count; //수강신청과목수
    ifstream fin;
    fin.open("students.txt");
    while (1) {
        fin >> id >> pw >> name >> Credits_available >> enrol_count;
        if (!fin)break;
        studentIds.push_back(id);
        passwords.push_back(pw);
        names.push_back(name);
        credits.push_back(Credits_available);
        vector<string>lecture;
        for (int i = 0; i < enrol_count; i++)
        {
            fin >> lecturecode;
            lecture.push_back(lecturecode);
        }
        appliedLectureCodes.push_back(lecture);
    }

    fin.close();
}

void readLectureFile(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
    ifstream fin;
    string lecturecode, lecturename;
    int lecturecredit, limit;
    fin.open("lectures.txt");
    while (1) {
        fin >> lecturecode >> lecturename >> lecturecredit >> limit;
        if (!fin)break;
        lectureCodes.push_back(lecturecode);
        lectureNames.push_back(lecturename);
        lectureCredits.push_back(lecturecredit);
        limits.push_back(limit);
    }
    fin.close();
}

void writeStudentFile(const vector<string>& studentIds, const vector<string>& passwords, const vector<string>& names, const vector<int>& credits, const vector<vector<string>>& appliedLectureCodes) {
    ofstream fout;
    fout.open("students.txt");
    for (unsigned int i = 0; i < studentIds.size(); i++) {
        string id = studentIds[i];
        string pw = passwords[i];
        string name = names[i];
        int Credits_available = credits[i];
        int enrol_count = appliedLectureCodes[i].size();
        fout << studentIds[i] << '\t' << passwords[i] << '\t' << names[i] << '\t' << credits[i] << '\t' << appliedLectureCodes[i].size() << '\t';
        if (appliedLectureCodes[i].size() > 0) {
            for (unsigned int j = 0; j < appliedLectureCodes[i].size(); j++) {
                fout << appliedLectureCodes[i][j] << '\t';
            }
            fout << endl;
        }
        else  fout << endl;

    }
    fout.close();
}

void writeLectureFile(const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits) {
    ofstream fout;
    fout.open("lectures.txt");
    for (unsigned int i = 0; i < lectureCodes.size(); i++) {
        fout << lectureCodes[i] << '\t' << lectureNames[i] << '\t' << lectureCredits[i] << '\t' << limits[i] << endl;
    }
    fout.close();
}