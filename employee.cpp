#include <iostream>
#include "employee.h"
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <map>

//Employee

//constructor
Employee::Employee() {}

Employee::Employee(const int n_id, const int n_wage) : id(n_id), wage(n_wage), hoursWorked(0) {}

//get functions
int Employee::getSalary() {
    return hoursWorked * wage + bonus();
}

int Employee::getId() const {
    return id;
}


//Tester

//constructor
Tester::Tester(int n_id, int n_wage, std::set<Genre> n_genres)
        : Employee(n_id, n_wage), genres(std::move(n_genres)) {};

int Tester::bonus() {
    return (int) genres.size() * 20;
}

bool Tester::canTest(Genre genre) {
    auto it = genres.find(genre);
    return it != genres.end();
}



//Manager
Manager::Manager() {};

Manager::Manager(int n_id, int n_wage, std::list<Tester> testers)
        : Employee(n_id, n_wage), testers(std::move(testers)) {};

int Manager::bonus() {
    return requestsCompleted * 50;
}

std::string Manager::nextHour() {
    std::string log = "";
    if (requests.empty()) {
        // there is nothing to do
        return "Manager: there is nothing to do\n";
    }

    std::list<Tester> freeTesters = testers;
    std::vector<Tester> competentTesters = {};
    std::vector<ReviewRequest *> readyRequests = {};

    for (auto request :requests) {

        if (!this->canTest(request->getGame().getGenre())) {
            log += request->getGame().getTitle() + ": we don't have specialist to this game genre,";
            log += " request has been rejected.\n";
            readyRequests.push_back(request);
        }

        // creating a group of testers to one game
        for (auto tester :freeTesters) {
            // checking if don't have more testers than it is needed
            if (competentTesters.size() == request->getHoursLeft()) {
                competentTesters.push_back(tester);
                break;
            }

            // separate competent testers
            if (tester.canTest(request->getGame().getGenre())) {
                competentTesters.push_back(tester);
            }
        }

        if (competentTesters.empty()) {
            continue;
        }


        // cleaning to check how many free testers we have now
        for (const auto &tester :competentTesters) {
            int tester_id = tester.getId();
            freeTesters.remove_if([tester_id](const Tester &freeTester) { return tester_id == freeTester.getId(); });
        }

        // assign testers and print result
        request->test((int) competentTesters.size());
        if (request->getHoursLeft() == 0) {
            log += "Manager: " + request->getGame().getTitle() + " completed!\n";
            readyRequests.push_back(request);
        } else {
            log += "Manager: " + request->getGame().getTitle() + " tested for " + std::to_string(competentTesters.size());
            log += "h. " + std::to_string(request->getHoursLeft()) + "h left.\n";
        }

        competentTesters.clear();
    }

    // cleaning to check how many free testers we have now
    for (auto request : readyRequests) {
        requests.remove(request);
    }
    return log;
}


//checking if manager has specialists to test this game
bool Manager::canTest(const Genre genre) {

    for (auto tester: testers) {
        if (tester.canTest(genre)) {
            return true;
        }
    }
    return false;
}

std::string Manager::assignRequest(ReviewRequest *request) {
    requests.push_back(request);

    //counting the prize

    //counting how many tester can test that game
    int specialistNr = 0;
    for (auto tester :testers) {
        if (tester.canTest(request->getGame().getGenre())) {
            specialistNr++;
        }
    }

    // price is cheaper if the manager has more qualified testers to this genre
    std::map<int, int> pricesPerHour{{1, 100},
                                     {2, 70},
                                     {3, 50},
                                     {4, 30},
                                     {5, 30}};

    int price = pricesPerHour.count(specialistNr) ? pricesPerHour[specialistNr] : 20;
    request->setPrice(price);

    std::string log = "Manger: assigned " + request->getGame().getTitle();
    log += "\nPrice of testing this request is: " + std::to_string(request->getPrice()) + "\n";
    return log;
}


