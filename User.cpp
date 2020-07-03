#include "User.h"
#include "Util.h"
#include "Common.h"
void printStudent(const vector<string>& studentIds, const vector<string>& names, const vector<int>& credits, const int& user) {
    cout << "---------------------------------------------------" << endl;
    cout << "�й�: " << studentIds[user] << "    " << "�̸�: " << names[user] << "  ������������: " << credits[user] << endl;
    cout << "---------------------------------------------------" << endl;
}
int runStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, int user) {
    while (1) {
        char runstudent_type;
        cout << "---------------------------------------------------" << endl;
        cout << "1. ������û" << endl;
        cout << "2. ������Ȳ" << endl;
        cout << "3. ����öȸ" << endl;
        cout << "4. ��й�ȣ ����" << endl;
        cout << "5. �α׾ƿ�" << endl;
        cout << "0. ����" << endl;
        cout << "---------------------------------------------------" << endl << ">>";

        cin >> runstudent_type;
        switch (runstudent_type) {
        case ('1'):
            applyLecture(studentIds, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
            break;
        case('2'):
            printStudent(studentIds, names, credits, user);
            printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
            cout << "����Ϸ��� �ƹ�Ű�� �����ʽÿ�...." << endl;
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
            cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
            break;
        }
        continue;
    }
}

void applyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user) {
    printStudent(studentIds, names, credits, user);
    printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits);
    while (1) {
        bool apply_possible = true;                      //������û ���� ���� ���� ����
        int cnt = 0;                                       //������û �Ұ� ������ ���� ���� �� ���ǰ˻� ������ ���� �Ѱ��� ���θ� ����ϰԲ� �ϴ� ����
        string applylecture_code;
        cout << "��û�� ���� �ڵ�(0: �ڷΰ���)>>";
        cin >> applylecture_code;
        if (applylecture_code == "0") break;
        int index = -1;

        index = findLectureByCode(lectureCodes, applylecture_code);

        if (index == -1) {
            cout << "�߸��Է��ϼ̽��ϴ�." << endl;                                              //���� �ڵ尡 �ƴ� �ٸ� ���� �Է��� ���
            cout << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�....";
            cin.ignore();
            getchar();
            continue;
        }
        if (limits[index] == 0) {
            cout << "�����ο��� �� á���ϴ�." << endl;                                          //1. �����ο� ��п���
            apply_possible = false;
            continue;
        }
        if (cnt == 0) {
            if (credits[user] < lectureCredits[index]) {
                cout << "�������������� �����մϴ�." << endl;                                   //2. �������� ��п���
                apply_possible = false;
                continue;
            }
        }
        if (cnt == 0) {
            for (unsigned int i = 0; i < appliedLectureCodes[user].size(); i++) {
                if (applylecture_code == appliedLectureCodes[user][i]) {                        //3. �����ڵ� �ߺ�����
                    cout << "�̹� �ش� ������ ��û�߽��ϴ�." << endl;
                    apply_possible = false;
                    cnt++;
                    break;
                }
            }
        }
        if (cnt == 0) {
            string temp = lectureNames[index]; //index =3;
            if (appliedLectureCodes[user].size() > 0) {
                for (unsigned int i = 0; i < appliedLectureCodes[user].size(); i++) {           //4.����� �ߺ�����
                    if (findLectureByCode(lectureCodes, appliedLectureCodes[user][i]) != -1) {
                        if (lectureNames[findLectureByCode(lectureCodes, appliedLectureCodes[user][i])] == temp) {
                            cout << "�̹� ���ϸ��� ������ ��û�߽��ϴ�." << endl;
                            apply_possible = false;
                            cnt++;
                            break;
                        }
                    }
                }

            }
        }

        if (apply_possible == true) {
            cout << '[' << applylecture_code << ']' << lectureNames[index] << "(��)�� ���������� ��û�Ͽ����ϴ�." << endl;
            limits[index]--;                                             //���������ο� 1�� ����
            credits[user] = credits[user] - lectureCredits[index];       //�л��� ������������ ����
            appliedLectureCodes[user].push_back(lectureCodes[index]);    //�л��� ��û���� vector�� ��û�� �����ڵ� �߰�           
        }
        cout << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�....";
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
        bool disapply_possible = false;         //����öȸ ���� ���� ���� ����
        cout << "öȸ�� ���� �ڵ�(0: �ڷΰ���)>>" << endl;
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
            cout << "���� �ڵ尡 �ùٸ��� �ʽ��ϴ�." << endl;
            cout << "����Ϸ��� �ƹ�Ű�� �����ʽÿ�...." << endl;
            cin.ignore();
            getchar();
            continue;
        }
        cout << "[" << appliedLectureCodes[user][user_index] << "] " << lectureNames[lecture_index] << "(��)�� öȸ�Ͽ����ϴ�." << endl;
        limits[lecture_index]++;
        credits[user] = credits[user] + lectureCredits[lecture_index];                                              //�л��� ������������ ����
        deleteElement(appliedLectureCodes[user], user_index);                                                       //������û��� vector���� disapply_lecture ���� 
        printStudent(studentIds, names, credits, user);
        printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
        cout << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�...." << endl;
        cin.ignore();
        getchar();
    }
}

void changePassword(vector<string>& passwords, const int& user) {
    while (1) {
        string password;
        cout << "---------------------------------------------------" << endl << ">>";
        cout << "���� Ȯ���� ���� ��й�ȣ�� �� �� �� �Է����ּ���." << endl;
        cout << "��й�ȣ: ";
        cin >> password;
        if (password == passwords[user]) {
            cout << "---------------------------------------------------" << endl << ">>";
            cout << "���� ������ ��й�ȣ�� �Է��ϼ���." << endl;
            cout << "��й�ȣ: ";
            cin >> password;
            cout << "����Ǿ����ϴ�." << endl;
            passwords[user] = password;
            cout << "---------------------------------------------------" << endl << ">>";
        }
        else cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
        cout << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�....(0: �ڷΰ���)" << endl;
        cin.ignore();
        if (getchar() == '0') break;;
    }
}