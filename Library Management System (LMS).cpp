#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;
//Ali Mohammed contributed to this project
// هيكل المستخدم


// هيكل السجل في الأرشيف
struct Record {
    string archiveName;
    string owner;
    vector<string> data; // كل عمود قيمة نصية
};

// القوائم الأساسية
vector<User> users;
vector<Record> archives;

// دوال مساعدة
string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start +1);
}

// تحميل المستخدمين من ملف
void loadUsers() {
    ifstream file("users.csv");
    if (!file.is_open()) return;

    string line;
    while(getline(file, line)) {
        stringstream ss(line);
        string username, password, role;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');
        users.push_back({trim(username), trim(password), trim(role)});
    }
    file.close();
}

// حفظ المستخدمين في ملف
void saveUsers() {
    ofstream file("users.csv");
    for (auto &u : users) {
        file << u.username << "," << u.password << "," << u.role << "\n";
    }
    file.close();
}

// تسجيل الدخول
User* login() {
    string username, password;
    cout << "اسم المستخدم: ";
    cin >> username;
    cout << "كلمة المرور: ";
    cin >> password;

    for (auto &u : users) {
        if (u.username == username && u.password == password) {
            cout << "تم تسجيل الدخول كـ " << u.role << endl;
            return &u;
        }
    }
    cout << "اسم المستخدم او كلمة المرور خاطئة!\n";
    return nullptr;
}

// إضافة مستخدم (للمدير)
void addUser() {
    string username, password, role;
    cout << "اسم المستخدم الجديد: ";
    cin >> username;
    cout << "كلمة المرور: ";
    cin >> password;
    cout << "الدور (admin/user): ";
    cin >> role;
    users.push_back({username,password,role});
    saveUsers();
    cout << "تم اضافة المستخدم!\n";
}

// إضافة سجل أرشيف
void addRecord(User* current) {
    string archiveName;
    cout << "اسم الأرشيف: ";
    cin >> archiveName;

    Record r;
    r.archiveName = archiveName;
    r.owner = current->username;

    int cols;
    cout << "عدد الأعمدة في السجل: ";
    cin >> cols;
    r.data.resize(cols);
    for(int i=0;i<cols;i++){
        cout << "ادخل قيمة العمود " << i+1 << ": ";
        cin >> r.data[i];
    }
    archives.push_back(r);

    // حفظ في ملف CSV
    ofstream file(archiveName + ".csv", ios::app);
    for(int i=0;i<cols;i++){
        file << r.data[i];
        if(i<cols-1) file << ",";
    }
    file << "\n";
    file.close();

    cout << "تم اضافة السجل!\n";
}

// عرض السجلات الخاصة بالمستخدم
void viewRecords(User* current) {
    string archiveName;
    cout << "ادخل اسم الأرشيف لعرضه: ";
    cin >> archiveName;

    ifstream file(archiveName + ".csv");
    if (!file.is_open()) {
        cout << "الارشيف غير موجود!\n";
        return;
    }

    cout << "السجلات في " << archiveName << ":\n";
    string line;
    while(getline(file,line)){
        cout << line << endl;
    }
    file.close();
}

// البرنامج الرئيسي
int main() {
    cout << "===== برنامج Console للأرشيف والمستخدمين =====\n";

    loadUsers();

    User* current = nullptr;
    while(current == nullptr){
        current = login();
    }

    bool running = true;
    while(running){
        cout << "\nخيارات:\n";
        if(current->role == "admin")
            cout << "1- إضافة مستخدم\n";
        cout << "2- إضافة سجل أرشيف\n";
        cout << "3- عرض سجلات\n";
        cout << "0- خروج\n";

        int choice;
        cout << "اختر رقم: ";
        cin >> choice;

        switch(choice){
            case 1:
                if(current->role == "admin") addUser();
                else cout << "ليس لديك صلاحية!\n";
                break;
            case 2:
                addRecord(current);
                break;
            case 3:
                viewRecords(current);
                break;
            case 0:
                running = false;
                break;
            default:
                cout << "اختيار غير صالح!\n";
        }
    }

    cout << "وداعاً!\n";
    return 0;
} <algorithm>

using namespace std;

// هيكل المستخدم

    return 0;
}
