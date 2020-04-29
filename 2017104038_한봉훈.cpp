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
        bool dup_check = false;       //학번 중복판단 변수
        cout << "---------------------------------------------------" << endl;
        cout << "학번 ";
        cin >> studentid;
        cout << "비밀번호 ";
        cin >> password;
        cout << "학생 이름: ";
        cin >> name;
        cout << "---------------------------------------------------" << endl;
        for (unsigned int i = 0; i < studentIds.size(); i++) {
            if (studentid == studentIds[i]) {
                dup_check = true;
            }
            }
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
        bool dub_check = false;        //강의명 중복 검사 변수
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

            for (unsigned int i = 0; i < lectureCodes.size(); i++)
                if (lecturecode == lectureCodes[i]) dub_check = true;
            if (dub_check == true) {
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
        for (unsigned int i = 0; i < lectureCodes.size(); i++) {
            if (delete_lecture == lectureCodes[i]) {            //입력받은 과목코드가 lectureCodes 의 요소인지 확인하고 맞다면 그 때의 i값을 lecture_index에 저장
                lecture_index = i;
                delete_possible = true;
                break;
            }
        }
        if (delete_possible == false) {
            cout << "일치하는 코드가 없습니다." << endl;
            cout << "계속하려면 아무 키나 누르십시오...." << endl;
            cin.ignore();
            getchar();
            continue;
        }
        if(delete_possible==true) {
            for (unsigned int i = 0; i < appliedLectureCodes.size(); i++) {
                for (unsigned int j = 0; j < appliedLectureCodes[i].size(); j++) {
                    if (appliedLectureCodes[i][j] == delete_lecture) {
                        string temp = appliedLectureCodes[i][j];
                        appliedLectureCodes[i][j] = appliedLectureCodes[i][appliedLectureCodes[i].size() - 1];          //강의가 삭제되면 학생은 그 강의를 철회한 것으로 처리한다.
                        appliedLectureCodes[i][appliedLectureCodes[i].size() - 1] = temp;
                        appliedLectureCodes[i].pop_back();
                        credits[i] += lectureCredits[lecture_index];
                        break;
                    }
                }
            }
            string temp_code = lectureCodes[lecture_index];         //강의가 삭제됨에 따라 lectureCode, lectureNames, lectureCredits, limits 의 요소들을 삭제해야한다.                                     
            string temp_name = lectureNames[lecture_index];         
            int temp_credit = lectureCredits[lecture_index];
            int temp_limit = limits[lecture_index];

            lectureCodes[lecture_index] = lectureCodes[lectureCodes.size() - 1];
            lectureCodes[lectureCodes.size() - 1] = temp_code;

            lectureNames[lecture_index] = lectureNames[lectureNames.size() - 1];
            lectureNames[lectureNames.size() - 1] = temp_name;

            lectureCredits[lecture_index] = lectureCredits[lectureCredits.size() - 1];                //pop_back()을 이용하기 위해 삭제할 요소를 맨 뒤로 이동시키는과정
            lectureCredits[lectureCredits.size() - 1] = temp_credit;

            limits[lecture_index] = limits[limits.size() - 1];
            limits[limits.size() - 1] = temp_limit;

            lectureCodes.pop_back();
            lectureNames.pop_back();
            lectureCredits.pop_back();
            limits.pop_back();
         
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
            cout << "잘못 입력하셨습니다." << endl;
            break;
        }
        continue;
    }
}


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
        bool apply_possible = true;  //수강신청 가능 여부 결정 변수
        int cnt = 0;        //수강신청 불가 요인이 여러 개일 때 조건검사 순서에 따라 한가지 요인만 출력하게끔 하는 변수
        string applylecture_code;
        cout << "신청할 과목 코드(0: 뒤로가기)>>";
        cin >> applylecture_code;
        if (applylecture_code == "0") break;
        int index = -1;
        for (unsigned int i = 0; i < lectureCodes.size(); i++) {
            if (applylecture_code == lectureCodes[i])  index = i;
        }
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
                    for (unsigned int j = 0; j < lectureCodes.size(); j++) {
                        if (appliedLectureCodes[user][i] == lectureCodes[j]) {
                            if (lectureNames[j] == temp) {
                                cout << "이미 동일명의 과목을 신청했습니다." << endl;
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
                for (unsigned int j = 0; j < lectureCodes.size(); j++) {
                    if (appliedLectureCodes[user][i] == lectureCodes[j]) lecture_index = j;
                }
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
        string temp = appliedLectureCodes[user][user_index];                                                        
        appliedLectureCodes[user][user_index] = appliedLectureCodes[user][appliedLectureCodes[user].size() - 1];    //신청과목 vector에서 제거할 요소의 위치를 맨 뒤 요소와 바꿈
        appliedLectureCodes[user][appliedLectureCodes[user].size() - 1] = temp;
        appliedLectureCodes[user].pop_back();                                                                       //신청과목 vector에서 철회과목 제거
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