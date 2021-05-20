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

Manager::Manager(unsigned int n_id, unsigned int n_wage)
        : Employee(n_id, n_wage), requestsCompleted(0) {};

unsigned int Manager::bonus() {
    return requestsCompleted * 50;
}

