#include <set>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <sstream>

#include "employee.h"

        /* class Employee */

// default constructor
Employee::Employee() = default;

//constructor
Employee::Employee(const int newId, const int newWage) : id(newId), wage(newWage), hoursWorked(0) {}


// functions
int Employee::getSalary() {
    return hoursWorked * wage + bonus();
}

int Employee::getId() const {
    return id;
}

int Employee::getHoursWorked() const {
    return hoursWorked;
}

void Employee::addHoursWorked(int hours) {
    hoursWorked += hours;
}


        /* class Tester : public Employee */

// constructor
Tester::Tester(int newId, int newWage, std::set<Genre> newGenres)
        : Employee(newId, newWage), genres(std::move(newGenres)) {}

// functions
unsigned int Tester::bonus() {
    return (int) genres.size() * 20;
}

bool Tester::canTest(Genre genre) {
    auto it = genres.find(genre);
    return it != genres.end();
}


        /* class Manager : public Employee */

// default constructor
Manager::Manager() = default;

// constructor
Manager::Manager(int newId, int newWage, std::list<std::shared_ptr<Tester>> testers)
        : Employee(newId, newWage), testers(std::move(testers)), allPayoffs(0) {}


// functions
unsigned int Manager::bonus() {
    /* manager receives bonus with every completed request */

    return requestsCompleted.size() * 50;
}

//
std::string Manager::nextHour(int hour) {
    /* Huge function simulating next hour, handles with:
     * games testing, paying for requests (on-time), giving payoffs for employees.
     * Allows to test multiple games at one hour. */

    // data initialization
    std::ostringstream progress;
    std::list<std::shared_ptr<Tester>> freeTesters = testers;
    std::vector<std::shared_ptr<Tester>> competentTesters = {};

    // if there is nothing to do
    if (requests.empty()) {
       progress << "Waiting for requests\n";
    }

    for (const auto &request :requests) {
        progress << "(" << request->getId() << ") " << request->getGame()->getTitle() << "\n";

        // creating a group of testers to one game
        for (const auto &tester :freeTesters) {

            // checking if manager doesn't have more testers than it is needed
            if (competentTesters.size() == request->getHoursLeft()) {
                break;
            }

            // separate competent testers
            if (tester->canTest(request->getGame()->getGenre())) {
                competentTesters.push_back(tester);
                tester->addHoursWorked(1);
            }
        }

        // if manager doesn't have free competent testers to this request
        if (competentTesters.empty()) {
            progress << "[";
            for (int i = 0; i < request->getHoursTested(); i++)progress << "#";
            for (unsigned int i = 0; i < request->getHoursLeft(); i++)progress << " ";
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
        for (unsigned int i = 0; i < request->getHoursLeft(); i++)progress << " ";
        progress << "] ";

        // completed request
        if (request->getHoursLeft() == 0) {
            requestsCompleted.push_back(request);
            request->setRate(rand() % 10 + 1); // games are rated from 1 to 10
            progress << "Completed! Rating: " << request->getGame()->addRating(request->getRate());
        } else {
            progress << request->getHoursTested() << "/" << request->getHoursRequested() << "h (+" << testedFor << "h)";
        }
        progress << "\n\n";
        competentTesters.clear();
    }

    // cleaning to check how many free testers we have now
    for (const auto &request : requestsCompleted) {
        requests.remove(request);
    }

    // add Hours Worked for manager
    addHoursWorked(1);

    // if it's been a week employees got their payoff
    std::string earnings;
    if (hour % 40 == 0){
        earnings += payoff();
    }

    // checking payments for the requests
    std::string payments = checkPayments(hour);

    return progress.str() + payments + earnings;
}

std::string Manager::assignRequest(const std::shared_ptr<ReviewRequest> &request, int hour) {
    /* checks if company has testers to test this genre,
     * sets submission Hour and price for a request */

    std::ostringstream log;

    // counting how many testers can test that game
    int specialistNr = 0;
    for (const auto &tester :testers) {
        if (tester->canTest(request->getGame()->getGenre())) {
            specialistNr++;
        }
    }

    // request rejection
    if (specialistNr == 0) {
        log << "\tRejected request (" << request->getId() << ") " << request->getGame()->getTitle()
            << " - no testers for this genre\n";
        return log.str();
    }

    // price per hour is cheaper if the manager has more qualified testers to this genre
    std::map<int, int> pricesPerHour{{1, 100},
                                     {2, 70},
                                     {3, 50},
                                     {4, 30},
                                     {5, 30}};

    int pricePerHour = pricesPerHour.count(specialistNr) ? pricesPerHour[specialistNr] : 60;
    int totalPrice = pricePerHour * request->getHoursRequested();
    request->setPrice(totalPrice);
    request->setSubmissionHour(hour);

    requests.push_back(request);
    unpaidRequests.push_back(request);

    log << "\t|New request (" << request->getId() << ") : " << request->getGame()->getTitle() << "\n";
    log << "\t|Price: " << request->getHoursRequested() << "h * " << pricePerHour << "zl/h = "
        << totalPrice << "zl\n\n";
    return log.str();
}


std::string Manager::summary() {
    /* Prints the summary from tester. Includes:
     * Request summary,
     * Cash summary,
     * Unfinished request summary */

    //Request summary
    std::ostringstream summary;
    summary << "Number of tested requests: " << requestsCompleted.size() << "\n\n";
    int counter = 1;
    int revenue = 0;
    for (const auto &request : requestsCompleted){
        summary << counter << ") " << request->getGame()->getTitle()
                << "\nRating from this request:" << request->getRate()
                << "\n\tTotal game rating: " << request->getGame()->getAvgRating() << "\n\n";
        revenue += request->getPrice();
        counter++;
    }

    // Cash summary
    int income = revenue-getSalary()-allPayoffs;

    summary << "Total company revenue: " << revenue << "zl" << std::endl;
    summary << "Testers earned: " << allPayoffs << "zl" << std::endl;
    summary << "Manager earned: " << getSalary() << "zl" << std::endl;
    summary << "\nTotal company income: " << income << "zl" << std::endl;

    // Unfinished requests summary
    counter = 0;
    summary << "\nUnfinished requests:" << std::endl;
    if (requests.empty()) summary << "None - All tasks are completed" << std::endl;
    else{
        for (const auto &request : requests){
            summary << counter << ") " << request->getGame()->getTitle() <<
                    "\nTested for " << request->getHoursTested() << "/" << request->getHoursRequested() <<"h.\n";
            counter++;
        }
    }
    return summary.str();
}

std::string Manager::payoff(){
    /* gives payoffs to employees,
     * returns string with all information about it */

    std::ostringstream earnings;
    earnings << "\n!!! It's been a week, time for payoff !!!\nTesters earnings:\n";
    for (const auto &tester : testers){
        if (tester->getHoursWorked() != 0) {
            earnings << tester->getId() << ". Tester earned: " << tester->getSalary() << "zl" << std::endl;
            allPayoffs += tester->getSalary();
        }
    }
    return earnings.str();
}

std::string Manager::checkPayments(int hour){
    /* make payments between publisher and manager,
     * returns string with all information about it */

    std::ostringstream payments;

    // paying for the requests
    for (const auto &request : unpaidRequests){
        int payed = rand() % 2;
        if (payed){
            request->pay(hour);
            payments << "\t|Request nr " << request->getId() << ": (" << request->getGame()->getTitle()
            << ") has just been paid";

            // if there was a delay, manager adds overhang
            int overhang = (request->getHourPaid() - request->getSubmissionHour()) - 4;
            if (overhang > 0){
                request->addOverhang(overhang*15);
                payments << " with an overhang of " << overhang*15 << " zl. There were "
                << overhang << " hours of delay.";
            }
            payments << "\n\t|Total price: " << request->getPrice() << "zl" << std::endl;
        }
        else{
            payments <<  "\t|Request nr " << request->getId() << ": (" << request->getGame()->getTitle()
                     << ") has not been paid yet." << std::endl;
        }
    }

    // deleting paid requests
    for (const auto &request : unpaidRequests){
        if (request->isPaid()) unpaidRequests.remove(request);
    }

    return payments.str();
}

