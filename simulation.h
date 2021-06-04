#pragma once

#include "publisher.h"
#include "game.h"
#include "employee.h"

#include <string>
#include <vector>
#include <set>
#include <list>
#include <stack>


class Simulation{

    std::vector<Publisher> publishers;
    Manager manager;
    const int simulation_len;
    const int num_testers;
    const int num_publishers;
    const int num_games;
    int request_id;

    std::stack<std::string> gameDevs;
    std::stack<std::string> gameNames;
    int all_games;

    std::vector<Publisher> getPublishers();

    std::string getPublisherName();

    std::vector<Game> getGames(std::string devName);

    std::string getGameName();

    int getGameId();

    Manager getManager();

    int randomTesterWage();

    std::set<Genre> drawTesterGenres();

    ReviewRequest drawReviewRequest();

    Genre randomGenre();

    void readData();

    void save(std::string sim_log);

public:
    Simulation(int n_simulation_len, int n_num_testers, int n_numb_publishers, int n_num_games);

    void start();
};