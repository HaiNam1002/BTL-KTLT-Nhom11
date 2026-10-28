#pragma once
#include <iostream>
#include <string>
#include <limits>

using namespace std;
class InputHelper {
public:
    static string getString(const string& p) {
        string s;
        while (true) {
            cout << p;
            getline(cin, s);
            if (!s.empty()) return s;
            cout << "Gia tri khong duoc de trong. Vui long nhap lai!\n";
        }
    }

    // Nhập số nguyên an toàn
    static int getInt(const string& p, int minVal = 0, int maxVal = 2000000000) {
        int val;
        while (true) {
            cout << p;
            if (cin >> val && val >= minVal && val <= maxVal) {
                cin.ignore(1000, '\n');
                return val;
            }
            cout << "Gia tri khong hop le. Vui long nhap lai!\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    // Nhập số thực double an toàn
    static double getDouble(const string& p, double minVal = 0.0) {
        double val;
        while (true) {
            cout << p;
            if (cin >> val && val >= minVal) {
                cin.ignore(1000, '\n');
                return val;
            }
            cout << "Gia tri khong hop le. Vui long nhap lai!\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
};