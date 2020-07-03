#include "User.h"
#include "Util.h"
#include "Common.h"
void printStudent(const vector<string>& studentIds, const vector<string>& names, const vector<int>& credits, const int& user) {
    cout << "---------------------------------------------------" << endl;
    cout << "학번: " << studentIds[user] << "    " << "이름: " << names[user] << "  수강가능학점: " << credits[user] << endl;
    cout << "---------------------------------------------------" << endl;
}
int runStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, int user) {
    while (1) {
        char runstudent_type;
        cout << "---------------------------------------------------" << endl;
        cout << "1. 수강신청" << endl;
        cout << "2. 수강현황" << endl;
        cout << "3. 수강철회" << endl;
        cout << "4. 비밀번호 변경" << endl;
        cout << "5. 로그아웃" << endl;
        cout << "0. 종료" << endl;
        cout << "---------------------------------------------------" << endl << ">>";

        cin >> runstudent_type;
        switch (runstudent_type) {
        case ('1'):
            applyLecture(studentIds, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
            break;
        case('2'):
            printStudent(studentIds, names, credits, user);
            printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
            cout << "계속하려면 아무키나 누르십시오...." << endl;
            cin.ignore();
            getchar();
            break;
        case('3'):
            disapplyLecture(studentIds, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
            break;
        case('4'):
            changePassword(passwords, user);
            break;
        case('5'):
            return -1;
            break;
        case('0'):
            return 1;
            break;
        default:
            cout << "잘못 입력하셨습니다." << endl;
            break;
        }
        continue;
    }
}

void applyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user) {
    printStudent(studentIds, names, credits, user);
    printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits);
    while (1) {
        bool apply_possible = true;                      //수강신청 가능 여부 결정 변수
        int cnt = 0;                                       //수강신청 불가 요인이 여러 개일 때 조건검사 순서에 따라 한가지 요인만 출력하게끔 하는 변수
        string applylecture_code;
        cout << "신청할 과목 코드(0: 뒤로가기)>>";
        cin >> applylecture_code;
        if (applylecture_code == "0") break;
        int index = -1;

        index = findLectureByCode(lectureCodes, applylecture_code);

        if (index == -1) {
            cout << "잘못입력하셨습니다." << endl;                                              //과목 코드가 아닌 다른 값을 입력한 경우
            cout << "계속하려면 아무 키나 누르십시오....";
            cin.ignore();
            getchar();
            continue;
        }
        if (limits[index] == 0) {
            cout << "수강인원이 꽉 찼습니다." << endl;                                          //1. 수강인원 충분여부
            apply_possible = false;
            continue;
        }
        if (cnt == 0) {
            if (credits[user] < lectureCredits[index]) {
                cout << "수강가능학점이 부족합니다." << endl;                                   //2. 수강학점 충분여부
                apply_possible = false;
                continue;
            }
        }
        if (cnt == 0) {
            for (unsigned int i = 0; i < appliedLectureCodes[user].size(); i++) {
                if (applylecture_code == appliedLectureCodes[user][i]) {                        //3. 과목코드 중복여부
                    cout << "이미 해당 과목을 신청했습니다." << endl;
                    apply_possible = false;
                    cnt++;
                    break;
                }
            }
        }
        if (cnt == 0) {
            string temp = lectureNames[index]; //index =3;
            if (appliedLectureCodes[user].size() > 0) {
                for (unsigned int i = 0; i < appliedLectureCodes[user].size(); i++) {           //4.과목명 중복여부
                    if (findLectureByCode(lectureCodes, appliedLectureCodes[user][i]) != -1) {
                        if (lectureNames[findLectureByCode(lectureCodes, appliedLectureCodes[user][i])] == temp) {
                            cout << "이미 동일명의 과목을 신청했습니다." << endl;
                            apply_possible = false;
                            cnt++;
                            break;
                        }
                    }
                }

            }
        }

        if (apply_possible == true) {
            cout << '[' << applylecture_code << ']' << lectureNames[index] << "(을)를 성공적으로 신청하였습니다." << endl;
            limits[index]--;                                             //수강가능인원 1명 감소
            credits[user] = credits[user] - lectureCredits[index];       //학생의 수강가능학점 증가
            appliedLectureCodes[user].push_back(lectureCodes[index]);    //학생의 신청과목 vector에 신청한 과목코드 추가           
        }
        cout << "계속하려면 아무 키나 누르십시오....";
        cin.ignore();
        getchar();
    }
}

void disapplyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user)
{
    printStudent(studentIds, names, credits, user);
    printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
    while (1) {
        string disapply_lecture;
        bool disapply_possible = false;         //수강철회 가능 여부 결정 변수
        cout << "철회할 과목 코드(0: 뒤로가기)>>" << endl;
        cin >> disapply_lecture;
        cin.clear();
        if (disapply_lecture == "0") break;
        int user_index = 0;
        int lecture_index = 0;
        for (unsigned int i = 0; i < appliedLectureCodes[user].size(); i++) {
            if (disapply_lecture == appliedLectureCodes[user][i]) {
                user_index = i;
                disapply_possible = true;
                lecture_index = findLectureByCode(lectureCodes, appliedLectureCodes[user][i]);
            }
        }
        if (!disapply_possible) {
            cout << "과목 코드가 올바르지 않습니다." << endl;
            cout << "계속하려면 아무키나 누르십시오...." << endl;
            cin.ignore();
            getchar();
            continue;
        }
        cout << "[" << appliedLectureCodes[user][user_index] << "] " << lectureNames[lecture_index] << "(을)를 철회하였습니다." << endl;
        limits[lecture_index]++;
        credits[user] = credits[user] + lectureCredits[lecture_index];                                              //학생의 수강가능학점 증가
        deleteElement(appliedLectureCodes[user], user_index);                                                       //수강신청목록 vector에서 disapply_lecture 제거 
        printStudent(studentIds, names, credits, user);
        printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
        cout << "계속하려면 아무 키나 누르십시오...." << endl;
        cin.ignore();
        getchar();
    }
}

void changePassword(vector<string>& passwords, const int& user) {
    while (1) {
        string password;
        cout << "---------------------------------------------------" << endl << ">>";
        cout << "본인 확인을 위해 비밀번호를 한 번 더 입력해주세요." << endl;
        cout << "비밀번호: ";
        cin >> password;
        if (password == passwords[user]) {
            cout << "---------------------------------------------------" << endl << ">>";
            cout << "새로 설정할 비밀번호를 입력하세요." << endl;
            cout << "비밀번호: ";
            cin >> password;
            cout << "변경되었습니다." << endl;
            passwords[user] = password;
            cout << "---------------------------------------------------" << endl << ">>";
        }
        else cout << "비밀번호가 일치하지 않습니다." << endl;
        cout << "계속하려면 아무 키나 누르십시오....(0: 뒤로가기)" << endl;
        cin.ignore();
        if (getchar() == '0') break;;
    }
}