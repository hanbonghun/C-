#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;
// File read
void readStudentFile(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes);
void readLectureFile(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits);
// File write
void writeStudentFile(const vector<string>& studentIds, const vector<string>& passwords, const vector<string>& names, const vector<int>& credits, const vector<vector<string>>& appliedLectureCodes);
void writeLectureFile(const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits);

// Get user input
string getInputId();
string getInputPassword();

// Login
int studentLogin(const vector<string>& studentIds, const vector<string>& passwords);
bool adminLogin();
int login(const vector<string>& studentIds, const vector<string>& passwords);

// Common
void printLectures(const vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits, const int& user = -100);

// Admin
void addStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes);
void addLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits);
void deleteLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, vector<int>& credits, vector<vector<string>>& appliedLectureCodes);
int runAdmin(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits);

//user
void printStudent(const vector<string>& studentIds, const vector<string>& names, const vector<int>& credits, const int& user);
void applyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user);
void disapplyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user);
void changePassword(vector<string>& passwords, const int& user);
int runStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, int user);


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

void readStudentFile(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
    string id, pw, name, lecturecode; //���̵�, ��й�ȣ, �̸� ,���� ��û�� ����
    int Credits_available; //������������
    int enrol_count; //������û�����
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
        if (appliedLectureCodes[i].size()> 0) {
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

void printLectures(const vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits, const int& user) {

    cout << "---------------------------------------------------" << endl;
    cout << "�����ڵ�\t���Ǹ�\t     ����    ���������ο�" << endl;
    cout << "---------------------------------------------------" << endl;
    if (user == -100) {
        for (unsigned int i = 0; i < lectureCodes.size(); i++)
            cout << lectureCodes[i] << " " << lectureNames[i] << "    " << lectureCredits[i] << "       " << limits[i] << endl;
        cout << "---------------------------------------------------" << endl;
    }
    else {
        int index = 0;
        for (unsigned int i = 0; i < appliedLectureCodes[user].size(); i++) {
            for (unsigned int j = 0; j < lectureCodes.size(); j++) {
                if (appliedLectureCodes[user][i] == lectureCodes[j]) index = j;
            }
            cout << appliedLectureCodes[user][i] << " " << lectureNames[index] << "    " << lectureCredits[index] << "       " << limits[index] << endl;
        }
        cout << "---------------------------------------------------" << endl;
    }
}

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
        for (unsigned int i = 0; i < studentIds.size(); i++) {
            if (studentid == studentIds[i]) {
                dup_check = true;
            }
            }
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
        bool dub_check = false;        //���Ǹ� �ߺ� �˻� ����
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

            for (unsigned int i = 0; i < lectureCodes.size(); i++)
                if (lecturecode == lectureCodes[i]) dub_check = true;
            if (dub_check == true) {
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
        for (unsigned int i = 0; i < lectureCodes.size(); i++) {
            if (delete_lecture == lectureCodes[i]) {            //�Է¹��� �����ڵ尡 lectureCodes �� ������� Ȯ���ϰ� �´ٸ� �� ���� i���� lecture_index�� ����
                lecture_index = i;
                delete_possible = true;
                break;
            }
        }
        if (delete_possible == false) {
            cout << "��ġ�ϴ� �ڵ尡 �����ϴ�." << endl;
            cout << "����Ϸ��� �ƹ� Ű�� �����ʽÿ�...." << endl;
            cin.ignore();
            getchar();
            continue;
        }
        if(delete_possible==true) {
            for (unsigned int i = 0; i < appliedLectureCodes.size(); i++) {
                for (unsigned int j = 0; j < appliedLectureCodes[i].size(); j++) {
                    if (appliedLectureCodes[i][j] == delete_lecture) {
                        string temp = appliedLectureCodes[i][j];
                        appliedLectureCodes[i][j] = appliedLectureCodes[i][appliedLectureCodes[i].size() - 1];          //���ǰ� �����Ǹ� �л��� �� ���Ǹ� öȸ�� ������ ó���Ѵ�.
                        appliedLectureCodes[i][appliedLectureCodes[i].size() - 1] = temp;
                        appliedLectureCodes[i].pop_back();
                        credits[i] += lectureCredits[lecture_index];
                        break;
                    }
                }
            }
            string temp_code = lectureCodes[lecture_index];         //���ǰ� �����ʿ� ���� lectureCode, lectureNames, lectureCredits, limits �� ��ҵ��� �����ؾ��Ѵ�.                                     
            string temp_name = lectureNames[lecture_index];         
            int temp_credit = lectureCredits[lecture_index];
            int temp_limit = limits[lecture_index];

            lectureCodes[lecture_index] = lectureCodes[lectureCodes.size() - 1];
            lectureCodes[lectureCodes.size() - 1] = temp_code;

            lectureNames[lecture_index] = lectureNames[lectureNames.size() - 1];
            lectureNames[lectureNames.size() - 1] = temp_name;

            lectureCredits[lecture_index] = lectureCredits[lectureCredits.size() - 1];                //pop_back()�� �̿��ϱ� ���� ������ ��Ҹ� �� �ڷ� �̵���Ű�°���
            lectureCredits[lectureCredits.size() - 1] = temp_credit;

            limits[lecture_index] = limits[limits.size() - 1];
            limits[limits.size() - 1] = temp_limit;

            lectureCodes.pop_back();
            lectureNames.pop_back();
            lectureCredits.pop_back();
            limits.pop_back();
         
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
        switch(runadmin_type){
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
        bool apply_possible = true;  //������û ���� ���� ���� ����
        int cnt = 0;        //������û �Ұ� ������ ���� ���� �� ���ǰ˻� ������ ���� �Ѱ��� ���θ� ����ϰԲ� �ϴ� ����
        string applylecture_code;
        cout << "��û�� ���� �ڵ�(0: �ڷΰ���)>>";
        cin >> applylecture_code;
        if (applylecture_code == "0") break;
        int index = -1;
        for (unsigned int i = 0; i < lectureCodes.size(); i++) {
            if (applylecture_code == lectureCodes[i])  index = i;
        }
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
                    for (unsigned int j = 0; j < lectureCodes.size(); j++) {
                        if (appliedLectureCodes[user][i] == lectureCodes[j]) {
                            if (lectureNames[j] == temp) {
                                cout << "�̹� ���ϸ��� ������ ��û�߽��ϴ�." << endl;
                                apply_possible = false;
                                cnt++;
                                break;
                            }
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
                for (unsigned int j = 0; j < lectureCodes.size(); j++) {
                    if (appliedLectureCodes[user][i] == lectureCodes[j]) lecture_index = j;
                }
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
        string temp = appliedLectureCodes[user][user_index];                                                        
        appliedLectureCodes[user][user_index] = appliedLectureCodes[user][appliedLectureCodes[user].size() - 1];    //��û���� vector���� ������ ����� ��ġ�� �� �� ��ҿ� �ٲ�
        appliedLectureCodes[user][appliedLectureCodes[user].size() - 1] = temp;
        appliedLectureCodes[user].pop_back();                                                                       //��û���� vector���� öȸ���� ����
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