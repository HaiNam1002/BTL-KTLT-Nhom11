#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

template <class T>
class Repository {
private:
    string filePath;
    vector<T> items;

public:
    Repository(string path) {
        filePath = path;
    }
    // Doc du lieu tu file .txt nap vao vector
    void loadFromFile() {
        items.clear(); // Xoa sach danh sach cu tren RAM
        ifstream file(filePath);
        
        // Neu file chua ton tai thi tao file moi roi thoat
        if (!file.is_open()) {
            ofstream newFile(filePath);
            newFile.close();
            return;
        }

        string line;
        while (getline(file, line)) {
            // Bo qua dong trong hoac dong ghi chu co dau #
            if (line == "" || line[0] == '#') continue;

            T item;
            try {
                item.fromFileString(line);
                items.push_back(item);
            } catch (...) {
                cout << "[Canh bao] Bo qua dong sai dinh dang!\n";
            }
        }
        file.close();
    }

    // Ghi toan bo danh sach tu RAM xuong file .txt
    void saveToFile() {
        ofstream file(filePath);
        for (int i = 0; i < items.size(); i++) {
            file << items[i].toFileString() << "\n";
        }
        file.close();
    }

    // Lay danh sach tat ca phan tu
    vector<T> getAll() {
        return items;
    }

    // Tim phan tu theo ID, tra ve con tro
    T* findById(string id) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].getId() == id) {
                return &items[i]; // Tra ve dia chi phan tu tim thay
            }
        }
        return nullptr; // Khong tim thay
    }

    // Them phan tu moi
    bool add(T item) {
        // Neu ID da ton tai thi khong cho them
        if (findById(item.getId()) != nullptr) {
            return false;
        }
        items.push_back(item);
        saveToFile(); // Luu ngay xuong file
        return true;
    }

    // Xoa phan tu theo ID
    bool remove(string id) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].getId() == id) {
                items.erase(items.begin() + i); // Xoa phan tu tai vi tri i
                saveToFile(); // Cap nhat lai file
                return true;
            }
        }
        return false;
    }

    // Cap nhat thong tin phan tu
    bool update(T newItem) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].getId() == newItem.getId()) {
                items[i] = newItem;
                saveToFile();
                return true;
            }
        }
        return false;
    }
};