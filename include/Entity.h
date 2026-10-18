#pragma once
#include <string>
using namespace std;
class Entity {
public:
    virtual ~Entity() {}

    virtual string getId() const = 0;

    virtual void display() const = 0;

    virtual string toFileString() const = 0;

    virtual void fromFileString(const string& line) = 0;
};