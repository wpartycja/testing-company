#pragma once

#include <list>
#include <queue>
#include "game.h"
#include <set>

class Employee {
protected:
    int id;
    int wage;
    int hoursWorked = 0;

    virtual int bonus() = 0;

public:
    Employee();

    Employee(int n_id, int n_wage);

    int getSalary();

    int getId() const;
};

class Tester : public Employee {
    const std::set<Genre> genres;

    int bonus() override;

public:
    Tester(int n_id, int n_wage,
           std::set<Genre> n_genres); // albo bez wage tylko zalozyc np 20 dla kazdego testera

    bool canTest(Genre genre);

};

class Manager : public Employee {
    std::list<ReviewRequest *> requests;
    std::list<Tester> testers;
    int requestsCompleted = 0;

    int bonus() override;

public:
    Manager();

    Manager(int n_id, int n_wage, std::list<Tester> testers);

    bool canTest(Genre genre);

    void assignRequest(ReviewRequest *request);

    void nextHour();
};