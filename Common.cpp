#include "Common.h"
#include "Util.h"

void printLectures(const vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits, const int& user) {

    cout << "---------------------------------------------------" << endl;
    cout << "과목코드\t강의명\t     학점    수강가능인원" << endl;
    cout << "---------------------------------------------------" << endl;
    if (user == -100) {
        for (unsigned int i = 0; i < lectureCodes.size(); i++)
            cout << lectureCodes[i] << " " << lectureNames[i] << "    " << lectureCredits[i] << "       " << limits[i] << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else {

        for (unsigned int i = 0; i < appliedLectureCodes[user].size(); i++) {
            int index = findLectureByCode(lectureCodes, appliedLectureCodes[user][i]);
            cout << appliedLectureCodes[user][i] << " " << lectureNames[index] << "    " << lectureCredits[index] << "       " << limits[index] << endl;
        }
        cout << "---------------------------------------------------" << endl;
    }
}