#pragma once

#include "publisher.h"
#include "game.h"
#include "employee.h"

#include <string>
#include <vector>
#include <set>
#include <list>
#include <stack>


class Simulation {

    std::vector<std::shared_ptr<Publisher>> publishers;
    Manager manager;

    const int simulation_len;
    const int num_testers;
    const int num_publishers;
    const int num_games;
    int requestId;
    int gameId;

    std::stack<std::string> publisherNames;
    std::stack<std::string> gameNames;


    static Genre getGenre();

    static int getTesterWage();

    static std::set<Genre> getTesterGenres();

    std::string getPublisherName();

    std::string getGameName();

    std::shared_ptr<ReviewRequest> getReviewRequest();

    void save(std::string);

    std::string summary();

public:

    Simulation(int n_simulation_len, int n_num_testers, int n_numb_publishers, int n_num_games,
               std::stack<std::string> newGameNames, std::stack<std::string> newPublisherNames);

    void start();
};