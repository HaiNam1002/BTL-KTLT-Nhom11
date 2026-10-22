#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <memory>
#include "Entity.h"

template <typename T>
class DataManager {
private:
    std::string filename;
    std::vector<T> items;

public:
    DataManager(const std::string& fname) : filename(fname) {
        loadFromFile();
    }

    // Lấy toàn bộ danh sách
    std::vector<T>& getAll() {
        return items;
    }

    // Tìm kiếm theo ID
    T* findById(const std::string& id) {
        for (auto& item : items) {
            if (item.getId() == id) return &item;
        }
        return nullptr;
    }

    // C - Create
    bool add(const T& item) {
        if (findById(item.getId()) != nullptr) {
            std::cout << "Loi: Ma ID da ton tai!\n";
            return false;
        }
        items.push_back(item);
        saveToFile();
        return true;
    }

    // R - Read/Display All
    void displayAll() const {
        if (items.empty()) {
            std::cout << "Danh sach trong!\n";
            return;
        }
        for (const auto& item : items) {
            item.display();
        }
    }

    // U - Update
    bool update(const std::string& id, const T& newItem) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].getId() == id) {
                items[i] = newItem;
                saveToFile();
                return true;
            }
        }
        return false;
    }

    // D - Delete
    bool remove(const std::string& id) {
        auto it = std::remove_if(items.begin(), items.end(),
            [&id](const T& item) { return item.getId() == id; });

        if (it != items.end()) {
            items.erase(it, items.end());
            saveToFile();
            return true;
        }
        return false;
    }

    // Đọc file
    void loadFromFile() {
        items.clear();
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            T item;
            item.fromFileString(line);
            items.push_back(item);
        }
        file.close();
    }

    // Ghi file
    void saveToFile() const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Loi mo file de ghi: " << filename << "\n";
            return;
        }
        for (const auto& item : items) {
            file << item.toFileString() << "\n";
        }
        file.close();
    }
};