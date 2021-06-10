#pragma once

#include "game.h"
#include "file_names.h"

#include <list>
#include <queue>
#include <set>


class Employee {
protected:
    int id{};
    int wage{};
    int hoursWorked = 0;

    virtual unsigned int bonus() = 0;

public:
    Employee();

    Employee(const int newId, const int newWage);

    int getSalary();

    int getId() const;

    int getHoursWorked() const;

    void addHoursWorked(int hours);
};

class Tester : public Employee {
    const std::set<Genre> genres;

    unsigned int bonus() override;

public:
    Tester(int newId, int newWage, std::set<Genre> newGenres);

    bool canTest(Genre genre);

};

class Manager : public Employee {
    std::list<std::shared_ptr<ReviewRequest>> requests;
    std::list<std::shared_ptr<Tester>> testers;
    std::vector<std::shared_ptr<ReviewRequest>> requestsCompleted;
    std::list<std::shared_ptr<ReviewRequest>> unpaidRequests;
    int allPayoffs = 0;

    unsigned int bonus() override;

public:
    Manager();

    Manager(int newId, int newWage, std::list<std::shared_ptr<Tester>> testers);

    std::string nextHour(int hour);

    std::string assignRequest(const std::shared_ptr<ReviewRequest> &request, int hour);

    std::string summary();

    std::string payoff();

    std::string checkPayments(int hour);

    std::mt19937 generator;
};