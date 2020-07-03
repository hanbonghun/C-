#include "Login.h"
string getInputId() {
    string id;
    cout << "아이디: ";
    cin >> id;
    return id;
}

string getInputPassword() {
    string password;
    cout << "비밀번호: ";
    cin >> password;
    return password;
}

int studentLogin(const vector<string>& studentIds, const vector<string>& passwords) {
    int failcount = 1; //로그인 실패 횟수 저장 
    while (failcount < 4) {
        string id = getInputId();
        string pw = getInputPassword();
        for (unsigned int i = 0; i < studentIds.size(); i++) {
            if (id == studentIds[i] && pw == passwords[i]) {
                failcount = 0;
                return i;
            }
        }
        cout << "로그인 " << failcount << "회 실패 (3회 실패시 종료)" << endl;
        failcount++;
    }
    cout << "3회 실패하여 종료합니다." << endl;
    return -1;
}

bool adminLogin() {
    int failcount = 1;
    while (failcount < 4) {
        string id = getInputId();
        string pw = getInputPassword();
        if (id == "admin" && pw == "admin") {
            failcount = 0;
            return true;
        }
        else {
            cout << "로그인 " << failcount << "회 실패 (3회 실패시 종료)" << endl;
            failcount++;
        }
    }
    cout << "3회 실패하여 종료합니다." << endl;
    return false;
}

int login(const vector<string>& studentIds, const vector<string>& passwords) {
    while (1) {
        int login_type;
        cout << "---------------------------------------------------" << endl;
        cout << "1. 학생 로그인" << endl;
        cout << "2. 관리자 로그인" << endl;
        cout << "0. 종료" << endl;
        cout << "---------------------------------------------------" << endl << ">>";
        cin >> login_type;
        if (login_type == 1) {
            int result_studentlogin = studentLogin(studentIds, passwords);
            if (result_studentlogin == -1)
                return -999;
            else return result_studentlogin;
        }
        else if (login_type == 2) {
            bool result_adminlogin = adminLogin();
            if (result_adminlogin == false)
                return -999;
            else return -100;
        }
        else if (login_type == 0)
            return -1;
        else {
            cout << "숫자를 다시 입력해주세요" << endl;
            continue;
        }
    }
}