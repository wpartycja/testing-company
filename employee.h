#pragma once

#include <list>
#include <queue>
#include "game.h"
#include <set>

class Employee {
protected:
    unsigned int id;
    unsigned int wage;
    unsigned int hoursWorked = 0;

    virtual unsigned int bonus() = 0;

public:
    Employee(unsigned int n_id, unsigned int n_wage);

    unsigned int getSalary();

    unsigned int getId();
};

class Tester : public Employee {
    const std::set<Genre> genres;

    unsigned int bonus() override;

public:
    Tester(unsigned int n_id, unsigned int n_wage,
           std::set<Genre> n_genres); // albo bez wage tylko zalozyc np 20 dla kazdego testera

    bool canTest(Genre genre);

};

class Manager : public Employee {
    std::list<ReviewRequest *> requests;
    std::list<Tester> testers;
    unsigned int requestsCompleted = 0;

    unsigned int bonus() override;

public:
    Manager(unsigned int n_id, unsigned int n_wage, std::list<Tester> testers);

    bool canTest(Genre genre);

    void assignRequest(ReviewRequest *request);

    void nextHour();
};