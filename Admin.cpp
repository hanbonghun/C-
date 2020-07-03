#include "Admin.h"
#include "Util.h"
#include "Common.h"

void addStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
    while (1) {
        string studentid, password, name;
        bool dup_check = false;       //�й� �ߺ��Ǵ� ����
        cout << "---------------------------------------------------" << endl;
        cout << "�й� ";
        cin >> studentid;
        cout << "��й�ȣ ";
        cin >> password;
        cout << "�л� �̸�: ";
        cin >> name;
        cout << "---------------------------------------------------" << endl;
        if (findStudentById(studentIds, studentid) != -1) dup_check = true;
        if (dup_check == true) {
            cout << "�̹� �����ϴ� �й��Դϴ�." << endl << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�....(0 :�ڷΰ���)" << endl;
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
            cout << "���������� ��ϵǾ����ϴ�." << endl << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�....(0 :�ڷΰ���)" << endl;
            cin.ignore();
            if (getchar() == '0') break;
        }
    }
}

void addLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
    while (1) {
        string lecturecode, lecturename;
        int lecturecredit, limit;
        bool dup_check = false;        //���Ǹ� �ߺ� �˻� ����
        cout << "---------------------------------------------------" << endl;
        cout << "�����ڵ�: ";
        cin >> lecturecode;
        cout << "�����: ";
        cin >> lecturename;
        cout << "����: ";
        while (!(cin >> lecturecredit)) {
            cout << "������ �Է����ּ���" << endl;
            cin.clear();
            cin.ignore();
        }
        cout << "�����ο�: ";
        while (!(cin >> limit)) {
            cout << "������ �Է����ּ���" << endl;
            cin.clear();
            cin.ignore();
        }
        cout << "---------------------------------------------------" << endl;

        if (findLectureByCode(lectureCodes, lecturecode) != -1) dup_check = true;
        if (dup_check == true) {
            cout << "�̹� �����ϴ� �����ڵ� �Դϴ�." << endl << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�....(0: �ڷΰ���)" << endl;
            cin.ignore();
            if (getchar() == '0') break;
        }
        else {
            lectureCodes.push_back(lecturecode);        //�����ڵ� vector�� �Է¹��� �����ڵ� �߰�
            lectureNames.push_back(lecturename);        //�����̸� vector�� �Է¹��� �����̸� �߰�
            lectureCredits.push_back(lecturecredit);    //�������� vector�� �Է¹��� �������� �߰�
            limits.push_back(limit);                    //�����ο� vector�� �Է¹��� �����ο� �߰�
            cout << "���������� ���ǰ� �����Ǿ����ϴ�." << endl << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�....(0: �ڷΰ���)" << endl;
            cin.ignore();
            if (getchar() == '0') break;
        }
    }
}

void deleteLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
    printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits);
    while (1) {
        bool delete_possible = false;     //������� ���� ���� �Ǵ�
        int lecture_index = 0;
        string delete_lecture;
        cout << "������ ���� �ڵ� (0:�ڷΰ���) >>";
        cin >> delete_lecture;
        if (delete_lecture == "0") break;

        if (findLectureByCode(lectureCodes, delete_lecture) != -1) {
            delete_possible = true;
            lecture_index = findLectureByCode(lectureCodes, delete_lecture);
        }

        if (delete_possible == false) {
            cout << "��ġ�ϴ� �ڵ尡 �����ϴ�." << endl;
            cout << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�...." << endl;
            cin.ignore();
            getchar();
            continue;
        }
        if (delete_possible == true) {
            for (unsigned int i = 0; i < appliedLectureCodes.size(); i++) {
                for (unsigned int j = 0; j < appliedLectureCodes[i].size(); j++) {
                    if (appliedLectureCodes[i][j] == delete_lecture) {
                        deleteElement(appliedLectureCodes[i], j);         //���ǰ� �����Ǹ� �л��� �� ���Ǹ� öȸ�� ������ ó���Ѵ�.
                        credits[i] += lectureCredits[lecture_index];
                        break;
                    }
                }
            }

            int temp_credit = lectureCredits[lecture_index];
            int temp_limit = limits[lecture_index];

            lectureCredits[lecture_index] = lectureCredits[lectureCredits.size() - 1];                //pop_back()�� �̿��ϱ� ���� ������ ��Ҹ� �� �ڷ� �̵���Ű�°���
            lectureCredits[lectureCredits.size() - 1] = temp_credit;
            limits[lecture_index] = limits[limits.size() - 1];
            limits[limits.size() - 1] = temp_limit;

            lectureCredits.pop_back();                           //���ǰ� �����ʿ� ���� lectureCode, lectureNames, lectureCredits, limits �� ��ҵ��� �����ؾ��Ѵ�.  
            limits.pop_back();
            deleteElement(lectureCodes, lecture_index);
            deleteElement(lectureNames, lecture_index);

            cout << "���������� ���ǰ� ���Ǿ����ϴ�." << endl << "�Լ��Ϸ��� �ƹ� Ű�� �����ʽÿ�...." << endl;
            cin.ignore();
            getchar();
        }
    }
}

int runAdmin(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
    while (1) {
        char runadmin_type;
        cout << "---------------------------------------------------" << endl;
        cout << "1. �л� �߰�" << endl;
        cout << "2. ���� ����" << endl;
        cout << "3. ���� ����" << endl;
        cout << "4. �α׾ƿ�" << endl;
        cout << "0. ����" << endl;
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
            cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
            break;
        }
        continue;
    }
}
