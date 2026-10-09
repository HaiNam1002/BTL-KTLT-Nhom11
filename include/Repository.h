#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

template <typename T>
class Repository {
private:
    std::string filePath;
    std::vector<T> items;

public:
    Repository(const std::string& path) : filePath(path) {}

    void loadFromFile() {
        items.clear();
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::ofstream newFile(filePath);
            newFile.close();
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            T item;
            try {
                item.fromFileString(line);
                items.push_back(item);
            } catch (...) {
                std::cout << "[Canh bao] Bo qua dong sai dinh dang!\n";
            }
        }
        file.close();
    }

    void saveToFile() const {
        std::ofstream file(filePath, std::ios::trunc);
        for (const auto& item : items) {
            file << item.toFileString() << "\n";
        }
        file.close();
    }

    const std::vector<T>& getAll() const { return items; }

    T* findById(const std::string& id) {
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