#pragma once

#include <set>
#include <queue>
#include "game.h"

class Employee {
protected:
    const unsigned int id;
    const unsigned int wage;
    unsigned int hoursWorked;

    virtual unsigned int bonus() = 0;

public:
    Employee(unsigned int id, unsigned int wage);

    unsigned int getSalary();

    unsigned int getId();
};

class Tester : Employee {
    const std::set<Genre> genres;

    unsigned int bonus() override;

public:
    Tester(unsigned int id, unsigned int wage,
           std::set<Genre> genres); // albo bez wage tylko zalozyc np 20 dla kazdego testera

    bool canTest(Genre genre);
};

class Manager : Employee {
    const std::queue<int> requests;
    unsigned int requestsCompleted;

    unsigned int bonus() override;

public:
    Manager(unsigned int id, unsigned int wage); // albo bez wage tylko zalozyc np 30 dla kazdego managera
    void nextHour();
};