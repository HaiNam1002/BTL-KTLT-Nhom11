#pragma once
#include <string>

class Entity {
public:
    virtual ~Entity() {}

    virtual std::string getId() const = 0;

    virtual void display() const = 0;

    virtual std::string toFileString() const = 0;

    virtual void fromFileString(const std::string& line) = 0;
};