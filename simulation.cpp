#include "simulation.h"

#include <iostream>
#include <random>


Simulation::Simulation(int n_simulation_len, int n_num_testers, int n_numb_publishers, int n_num_games)
    : simulation_len(n_simulation_len), num_testers(n_num_testers), num_publishers(n_numb_publishers),  num_games(n_num_games), manager(Simulation::getManager())
    {
        publishers = Simulation::getPublishers();
    }


void Simulation::start() {


    for (unsigned int h = 0; h < simulation_len; h++) {
        std::cout << "Hour " << h << ":\n";
        manager.nextHour();

    }
}

std::vector<Publisher> Simulation::getPublishers() {
    std::vector<Publisher> new_pub;

    for (int i = 0; i < num_publishers; i++) {
        auto publisher = Publisher();
        new_pub.push_back(publisher);
    }
    return new_pub;
}

Manager Simulation::getManager() {
    std::list<Tester> testers;

    for (int i = 0; i < num_publishers; i++) {
        auto tester = Tester();
        testers.push_back(tester);
    }
    auto new_manager = Manager(1, 25, testers);
    return new_manager;
}
