#include "Admin.h"
#include "Util.h"
#include "Common.h"

void addStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
    while (1) {
        string studentid, password, name;
        bool dup_check = false;       //학번 중복판단 변수
        cout << "---------------------------------------------------" << endl;
        cout << "학번 ";
        cin >> studentid;
        cout << "비밀번호 ";
        cin >> password;
        cout << "학생 이름: ";
        cin >> name;
        cout << "---------------------------------------------------" << endl;
        if (findStudentById(studentIds, studentid) != -1) dup_check = true;
        if (dup_check == true) {
            cout << "이미 존재하는 학번입니다." << endl << "계속하려면 아무 키나 누르십시오....(0 :뒤로가기)" << endl;
            cin.ignore();
            if (getchar() == '0')break;
        }
        else {
            studentIds.push_back(studentid);
            passwords.push_back(password);
            names.push_back(name);
            credits.push_back(18);
            vector<string> temp;
            appliedLectureCodes.push_back(temp);
            cout << "성공적으로 등록되었습니다." << endl << "계속하려면 아무 키나 누르십시오....(0 :뒤로가기)" << endl;
            cin.ignore();
            if (getchar() == '0') break;
        }
    }
}

void addLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
    while (1) {
        string lecturecode, lecturename;
        int lecturecredit, limit;
        bool dup_check = false;        //강의명 중복 검사 변수
        cout << "---------------------------------------------------" << endl;
        cout << "과목코드: ";
        cin >> lecturecode;
        cout << "과목명: ";
        cin >> lecturename;
        cout << "학점: ";
        while (!(cin >> lecturecredit)) {
            cout << "정수를 입력해주세요" << endl;
            cin.clear();
            cin.ignore();
        }
        cout << "수강인원: ";
        while (!(cin >> limit)) {
            cout << "정수를 입력해주세요" << endl;
            cin.clear();
            cin.ignore();
        }
        cout << "---------------------------------------------------" << endl;

        if (findLectureByCode(lectureCodes, lecturecode) != -1) dup_check = true;
        if (dup_check == true) {
            cout << "이미 존재하는 과목코드 입니다." << endl << "계속하려면 아무 키나 누르십시오....(0: 뒤로가기)" << endl;
            cin.ignore();
            if (getchar() == '0') break;
        }
        else {
            lectureCodes.push_back(lecturecode);        //과목코드 vector에 입력받은 과목코드 추가
            lectureNames.push_back(lecturename);        //과목이름 vector에 입력받은 과목이름 추가
            lectureCredits.push_back(lecturecredit);    //과목학점 vector에 입력받은 과목학점 추가
            limits.push_back(limit);                    //수강인원 vector에 입력받은 수강인원 추가
            cout << "성공적으로 강의가 개설되었습니다." << endl << "계속하려면 아무 키나 누르십시오....(0: 뒤로가기)" << endl;
            cin.ignore();
            if (getchar() == '0') break;
        }
    }
}

void deleteLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
    printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits);
    while (1) {
        bool delete_possible = false;     //과목폐쇄 가능 여부 판단
        int lecture_index = 0;
        string delete_lecture;
        cout << "삭제할 강의 코드 (0:뒤로가기) >>";
        cin >> delete_lecture;
        if (delete_lecture == "0") break;

        if (findLectureByCode(lectureCodes, delete_lecture) != -1) {
            delete_possible = true;
            lecture_index = findLectureByCode(lectureCodes, delete_lecture);
        }

        if (delete_possible == false) {
            cout << "일치하는 코드가 없습니다." << endl;
            cout << "계속하려면 아무 키나 누르십시오...." << endl;
            cin.ignore();
            getchar();
            continue;
        }
        if (delete_possible == true) {
            for (unsigned int i = 0; i < appliedLectureCodes.size(); i++) {
                for (unsigned int j = 0; j < appliedLectureCodes[i].size(); j++) {
                    if (appliedLectureCodes[i][j] == delete_lecture) {
                        deleteElement(appliedLectureCodes[i], j);         //강의가 삭제되면 학생은 그 강의를 철회한 것으로 처리한다.
                        credits[i] += lectureCredits[lecture_index];
                        break;
                    }
                }
            }

            int temp_credit = lectureCredits[lecture_index];
            int temp_limit = limits[lecture_index];

            lectureCredits[lecture_index] = lectureCredits[lectureCredits.size() - 1];                //pop_back()을 이용하기 위해 삭제할 요소를 맨 뒤로 이동시키는과정
            lectureCredits[lectureCredits.size() - 1] = temp_credit;
            limits[lecture_index] = limits[limits.size() - 1];
            limits[limits.size() - 1] = temp_limit;

            lectureCredits.pop_back();                           //강의가 삭제됨에 따라 lectureCode, lectureNames, lectureCredits, limits 의 요소들을 삭제해야한다.  
            limits.pop_back();
            deleteElement(lectureCodes, lecture_index);
            deleteElement(lectureNames, lecture_index);

            cout << "성공적으로 강의가 폐쇄되었습니다." << endl << "게속하려면 아무 키나 누르십시오...." << endl;
            cin.ignore();
            getchar();
        }
    }
}

int runAdmin(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
    while (1) {
        char runadmin_type;
        cout << "---------------------------------------------------" << endl;
        cout << "1. 학생 추가" << endl;
        cout << "2. 강의 개설" << endl;
        cout << "3. 강의 삭제" << endl;
        cout << "4. 로그아웃" << endl;
        cout << "0. 종료" << endl;
        cout << "---------------------------------------------------" << endl << ">>";
        cin >> runadmin_type;
        switch (runadmin_type) {
        case('1'):
            addStudent(studentIds, passwords, names, credits, appliedLectureCodes);
            break;
        case('2'):
            addLecture(lectureCodes, lectureNames, lectureCredits, limits);
            break;
        case('3'):
            deleteLecture(lectureCodes, lectureNames, lectureCredits, limits, credits, appliedLectureCodes);
            break;
        case('4'):
            return -1;
            break;
        case('0'):
            return 0;
            break;
        default:
            cout << "잘못 입력하셨습니다." << endl;
            break;
        }
        continue;
    }
}
