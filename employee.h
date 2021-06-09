#pragma once

#include <list>
#include <queue>
#include "game.h"
#include <set>

class Employee {
protected:
    int id{};
    int wage{};
    int hoursWorked = 0;

    virtual int bonus() = 0;

public:
    Employee();

    Employee(int n_id, int n_wage);

    int getSalary();

    int getId() const;

    int getHoursWorked();

    void addHoursWorked(int hours);
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
    std::list<std::shared_ptr<ReviewRequest>> requests;
    std::list<std::shared_ptr<Tester>> testers;
    std::vector<std::shared_ptr<ReviewRequest>> requestsCompleted;

    int bonus() override;

    int allPayoffs = 0;

public:
    Manager(int n_id, int n_wage, std::list<std::shared_ptr<Tester>> testers);

    Manager();

    bool canTest(Genre genre);

    std::string nextHour(int hour);

    std::string assignRequest(const std::shared_ptr<ReviewRequest> &request);

    std::string summary();

    std::string payoff();
};