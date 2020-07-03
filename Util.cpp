#include "Util.h"
int findStudentById(vector<string>studentIds, string id) {
    for (unsigned i = 0; i < studentIds.size(); i++) {
        if (studentIds[i] == id)
            return i;
    }
    return -1;
}

int findLectureByCode(vector<string>lectureCodes, string code) {
    for (unsigned i = 0; i < lectureCodes.size(); i++) {
        if (lectureCodes[i] == code)
            return i;
    }
    return -1;
}

void deleteElement(vector<string>& v, int index) {
    v.erase(v.begin() + index);
}