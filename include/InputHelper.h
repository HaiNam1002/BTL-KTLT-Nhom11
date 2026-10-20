#pragma once
#include <iostream>
#include <string>
#include <limits>

using namespace std;

class InputHelper {
public:
    // Nhập chuỗi không được để rỗng
using namespace std;
class InputHelper {
public:
    static string getString(const string& prompt) {
        string s;
        while (true) {
            cout << prompt;
            getline(cin, s);
            if (!s.empty()) return s;
            cout << "[Loi] Du lieu khong duoc de trong. Vui long nhap lai!\n";
        }
    }

    // Nhập số nguyên an toàn
    static int getInt(const string& prompt, int minVal = 0, int maxVal = 2000000000) {
        int val;
        while (true) {
            cout << prompt;
            if (cin >> val && val >= minVal && val <= maxVal) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return val;
            }
            cout << "[Loi] Gia tri khong hop le. Vui long nhap lai!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Nhập số thực double an toàn (đã bổ sung)
    static double getDouble(const string& prompt, double minVal = 0.0) {
        double val;
        while (true) {
            cout << prompt;
            if (cin >> val && val >= minVal) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return val;
            }
            cout << "[Loi] Gia tri khong hop le. Vui long nhap lai!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
};