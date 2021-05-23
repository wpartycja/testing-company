#pragma once

#include <set>
#include <queue>
#include "game.h"

class Employee {
protected:
    unsigned int id;
    unsigned int wage;
    unsigned int hoursWorked = 0;

    virtual unsigned int bonus() = 0;

public:
    Employee(unsigned int n_id, unsigned int n_wage);

    unsigned int getSalary();
    unsigned int getId() const;
};

class Tester : Employee {
    const std::set<Genre> genres;

    unsigned int bonus() override;

public:
    Tester(unsigned int n_id, unsigned int n_wage,
           std::set<Genre> n_genres); // albo bez wage tylko zalozyc np 20 dla kazdego testera

    bool canTest(Genre genre);
};

class Manager : Employee {
    std::queue<int> requests;
    unsigned int requestsCompleted;
    unsigned int hoursWorked = 40;

    unsigned int bonus() override;

public:
    Manager(unsigned int n_id, unsigned int n_wage); // albo bez wage tylko zalozyc np 30 dla kazdego managera
    void nextHour();
};