#include "Login.h"
string getInputId() {
    string id;
    cout << "���̵�: ";
    cin >> id;
    return id;
}

string getInputPassword() {
    string password;
    cout << "��й�ȣ: ";
    cin >> password;
    return password;
}

int studentLogin(const vector<string>& studentIds, const vector<string>& passwords) {
    int failcount = 1; //�α��� ���� Ƚ�� ���� 
    while (failcount < 4) {
        string id = getInputId();
        string pw = getInputPassword();
        for (unsigned int i = 0; i < studentIds.size(); i++) {
            if (id == studentIds[i] && pw == passwords[i]) {
                failcount = 0;
                return i;
            }
        }
        cout << "�α��� " << failcount << "ȸ ���� (3ȸ ���н� ����)" << endl;
        failcount++;
    }
    cout << "3ȸ �����Ͽ� �����մϴ�." << endl;
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
            cout << "�α��� " << failcount << "ȸ ���� (3ȸ ���н� ����)" << endl;
            failcount++;
        }
    }
    cout << "3ȸ �����Ͽ� �����մϴ�." << endl;
    return false;
}

int login(const vector<string>& studentIds, const vector<string>& passwords) {
    while (1) {
        int login_type;
        cout << "---------------------------------------------------" << endl;
        cout << "1. �л� �α���" << endl;
        cout << "2. ������ �α���" << endl;
        cout << "0. ����" << endl;
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
            cout << "���ڸ� �ٽ� �Է����ּ���" << endl;
            continue;
        }
    }
}