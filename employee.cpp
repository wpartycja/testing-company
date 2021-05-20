#pragma once

#include <iostream>
#include "employee.h"
#include <set>

//Employee

//constructor
Employee::Employee(const unsigned int n_id, const unsigned int n_wage){
    id = n_id;
    wage = n_wage;
}

//get functions
unsigned int Employee::getSalary(){
    return hoursWorked*wage + bonus();
}

unsigned int Employee::getId() const {
    return id;
}


//Tester

//constructor
Tester::Tester(unsigned int n_id, unsigned int n_wage, std::set<Genre> n_genres)
                : Employee(n_id, n_wage), genres(n_genres) {};

unsigned int Tester::bonus() {
    return genres.size() * 20;
}

bool Tester::canTest(Genre genre) {
    std::set<Genre>::iterator element = genres.begin();

    while(element != genres.end()){
        if ((*element) == genre){
            return true;
        }
    }
    return false;
}

//Manager

Manager::Manager(unsigned int n_id, unsigned int n_wage)
                : Employee(n_id, n_wage){};

unsigned int Manager::bonus(){
    return requestsCompleted * 50;
}

