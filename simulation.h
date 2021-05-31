#pragma once

#include "publisher.h"
#include "game.h"
#include "employee.h"

#include <string>
#include <vector>
#include <set>
#include <list>


class Simulation{

    std::vector<Publisher> publishers;
    Manager manager;
    const int simulation_len;
    const int num_testers;
    const int num_publishers;
    const int num_games;

    std::vector<Publisher> getPublishers();

    Manager getManager();

public:
    Simulation(int n_simulation_len, int n_num_testers, int n_numb_publishers, int n_num_games);

    void start();
};