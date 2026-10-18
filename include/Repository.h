#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
template <typename T>
class Repository {
private:
    string filePath;
    vector<T> items;

public:
    Repository(const string& path) : filePath(path) {}

    void loadFromFile() {
        items.clear();
        ifstream file(filePath);
        if (!file.is_open()) {
            ofstream newFile(filePath);
            newFile.close();
            return;
        }
        string line;
        while (getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
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

    void saveToFile() const {
        ofstream file(filePath, ios::trunc);
        for (const auto& item : items) {
            file << item.toFileString() << "\n";
        }
        file.close();
    }

    const vector<T>& getAll() const { return items; }

    T* findById(const string& id) {
        for (auto& item : items) {
            if (item.getId() == id) return &item;
        }
        return nullptr;
    }

    bool add(const T& item) {
        if (findById(item.getId()) != nullptr) return false;
        items.push_back(item);
        saveToFile();
        return true;
    }

    bool remove(const string& id) {
        auto it = remove_if(items.begin(), items.end(), 
            [&id](const T& item) { return item.getId() == id; });
        if (it != items.end()) {
            items.erase(it, items.end());
            saveToFile();
            return true;
        }
        return false;
    }

    bool update(const T& newItem) {
        for (auto& item : items) {
            if (item.getId() == newItem.getId()) {
                item = newItem;
                saveToFile();
                return true;
            }
        }
        return false;
    }
};