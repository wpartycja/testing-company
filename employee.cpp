#pragma once

#include <iostream>
#include "employee.h"
#include <set>
#include <utility>

//Employee

//constructor
Employee::Employee(const unsigned int n_id, const unsigned int n_wage) : id(n_id), wage(n_wage), hoursWorked(0) {}

//get functions
unsigned int Employee::getSalary() {
    return hoursWorked * wage + bonus();
}

unsigned int Employee::getId() const {
    return id;
}


//Tester

//constructor
Tester::Tester(unsigned int n_id, unsigned int n_wage, std::set<Genre> n_genres)
        : Employee(n_id, n_wage), genres(std::move(n_genres)) {};

unsigned int Tester::bonus() {
    return genres.size() * 20;
}

bool Tester::canTest(Genre genre) {
    auto it = genres.find(genre);
    return it != genres.end();
}

//Manager

Manager::Manager(unsigned int n_id, unsigned int n_wage, std::vector<Tester> testers)
        : Employee(n_id, n_wage), testers(std::move(testers)) {};

unsigned int Manager::bonus() {
    return requestsCompleted * 50;
}

void Manager::nextHour() {

    if (requests.empty()) {
        // there is nothing to do
        std::cout << "Manager: there is nothing to do\n";
        return;
    }

    // TODO: modify the algorithm such that multiple games can be tested simultaneously

    // get first request from the queue
    ReviewRequest *request = requests.front();

    // filter testers that can test this genre
    std::vector<Tester> availableTesters = {};
    for (auto tester :testers) {
        if (tester.canTest(request->getGame().getGenre())) {
            availableTesters.push_back(tester);
        }
    }

    // assign testers and print result
    request->test(availableTesters.size());    // to be implemented
    if (request->getHoursLeft() == 0) {
        std::cout << "Manager: " << request->getGame().getTitle() << " completed!\n";
        requests.pop();
    } else {
        std::cout << "Manager: " << request->getGame().getTitle() << " tested for " << availableTesters.size() << "h. "
                  << request->getHoursLeft() << "h left.\n";
    }

}

void Manager::canTest(const Genre genre) {
    // TODO: check if manager has at least 1 tester who can test given genre
}

void Manager::assignRequest(ReviewRequest *request) {
    requests.push(request);
    std::cout << "Manger: assigned " << request->getGame().getTitle() << "\n";
}

