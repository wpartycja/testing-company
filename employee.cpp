#include <iostream>
#include "employee.h"
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <sstream>

//Employee

//constructor
Employee::Employee() = default;

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
        : Employee(n_id, n_wage), genres(std::move(n_genres)) {}

int Tester::bonus() {
    return (int) genres.size() * 20;
}

bool Tester::canTest(Genre genre) {
    auto it = genres.find(genre);
    return it != genres.end();
}


//Manager

Manager::Manager() = default;

Manager::Manager(int n_id, int n_wage, std::list<std::shared_ptr<Tester>> testers)
        : Employee(n_id, n_wage), testers(std::move(testers)) {}

int Manager::bonus() {
    return requestsCompleted * 50;
}

std::string Manager::nextHour() {
    std::ostringstream progress;
    std::ostringstream info;
    if (requests.empty()) {
        // there is nothing to do
        return "Waiting for requests\n";
    }

    std::list<std::shared_ptr<Tester>> freeTesters = testers;
    std::vector<std::shared_ptr<Tester>> competentTesters = {};
    std::vector<std::shared_ptr<ReviewRequest>> readyRequests = {};

    for (const auto &request :requests) {

        progress << "(" << request->getId() << ") " << request->getGame()->getTitle() << "\n";

        // creating a group of testers to one game
        for (const auto &tester :freeTesters) {
            // checking if don't have more testers than it is needed
            if (competentTesters.size() == request->getHoursLeft()) {
                competentTesters.push_back(tester);
                break;
            }

            // separate competent testers
            if (tester->canTest(request->getGame()->getGenre())) {
                competentTesters.push_back(tester);
            }
        }

        if (competentTesters.empty()) {
            progress << "[";
            for (int i = 0; i < request->getHoursTested(); i++)progress << "#";
            for (int i = 0; i < request->getHoursLeft(); i++)progress << " ";
            progress << "] Waiting for testers\n\n";
            continue;
        }


        // cleaning to check how many free testers we have now
        for (const auto &tester :competentTesters) {
            int tester_id = tester->getId();
            freeTesters.remove_if([tester_id](const std::shared_ptr<Tester> &freeTester) {
                return tester_id == freeTester->getId();
            });
        }

        // assign testers and print result
        progress << "[";
        for (int i = 0; i < request->getHoursTested(); i++)progress << "#";
        int testedFor = request->test((int) competentTesters.size());
        for (int i = 0; i < testedFor; i++)progress << "+";
        for (int i = 0; i < request->getHoursLeft(); i++)progress << " ";
        progress << "] ";

        if (request->getHoursLeft() == 0) {
            readyRequests.push_back(request);
            progress << " Completed";
        } else {
            progress << request->getHoursTested() << "/" << request->getHoursRequested() << "h (+" << testedFor << "h)";
        }
        progress << "\n\n";
        competentTesters.clear();
    }

    // cleaning to check how many free testers we have now
    for (const auto &request : readyRequests) {
        requests.remove(request);
    }
    return progress.str() + info.str();
}

std::string Manager::assignRequest(const std::shared_ptr<ReviewRequest> &request) {

    std::ostringstream log;

    //counting how many tester can test that game
    int specialistNr = 0;
    for (const auto &tester :testers) {
        if (tester->canTest(request->getGame()->getGenre())) {
            specialistNr++;
        }
    }

    if (specialistNr == 0) {
        log << "\tRejected request (" << request->getId() << ") " << request->getGame()->getTitle()
            << "no testers for this genre\n";
        return log.str();
    }

    // pricePerHour is cheaper if the manager has more qualified testers to this genre
    std::map<int, int> pricesPerHour{{1, 100},
                                     {2, 70},
                                     {3, 50},
                                     {4, 30},
                                     {5, 30}};

    int pricePerHour = pricesPerHour.count(specialistNr) ? pricesPerHour[specialistNr] : 20;
    int totalPrice = pricePerHour * request->getHoursRequested();
    request->setPrice(totalPrice);

    requests.push_back(request);

    log << "\t|New request (" << request->getId() << ") : " << request->getGame()->getTitle() << "\n";
    log << "\t|Price: " << request->getHoursRequested() << "h * " << pricePerHour << "zl/h = "
        << totalPrice << "zl\n\n";
    return log.str();
}

