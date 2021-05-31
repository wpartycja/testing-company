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
    int request_id;

    std::vector<Publisher> getPublishers();

    std::string getPublisherName();

    std::vector<Game> getGames();

    Manager getManager();

    int randomTesterWage();

    std::set<Genre> drawTesterGenres();

    ReviewRequest drawReviewRequest();

    void save(std::string sim_log);

public:
    Simulation(int n_simulation_len, int n_num_testers, int n_numb_publishers, int n_num_games);

    void start();
};