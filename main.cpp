#include <iostream>
#include "employee.h"
#include <chrono>
#include <thread>

int main() {

    std::set<Genre> tester1Genres = {sports, MMO, action, sandbox};
    std::set<Genre> tester2Genres = {sandbox};
    auto tester1 = Tester(1, 20, tester1Genres);
    auto tester2 = Tester(2, 20, tester2Genres);
    std::vector<Tester> testers = {tester1, tester2};
    auto manager1 = Manager(1, 25, testers);
    auto game1 = Game(1, sports, "Flanks", "Warsaw University of Technology");
    auto game2 = Game(2, sandbox, "minicraft", "mojang");

    auto request1 = ReviewRequest(0, game1, 10);
    auto request2 = ReviewRequest(0, game2, 3);

    manager1.assignRequest(&request1);
    manager1.assignRequest(&request2);

    for (unsigned int h = 0; h < 15; h++) {
        std::cout << "Hour " << h << ":\n";
        manager1.nextHour();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    return 0;
}