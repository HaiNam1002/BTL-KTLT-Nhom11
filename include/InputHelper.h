#pragma once
#include <iostream>
#include <string>
#include <limits>

class InputHelper {
public:
    static std::string getString(const std::string& prompt) {
        std::string s;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, s);
            if (!s.empty()) return s;
            std::cout << "[Loi] Du lieu khong duoc de trong. Vui long nhap lai!\n";
        }
    }

    static int getInt(const std::string& prompt, int minVal = 0, int maxVal = 2000000000) {
        int val;
        while (true) {
            std::cout << prompt;
            if (std::cin >> val && val >= minVal && val <= maxVal) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
            std::cout << "[Loi] Gia tri khong hop le. Vui long nhap lai!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};