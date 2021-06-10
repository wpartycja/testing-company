#pragma once

#include "publisher.h"
#include "game.h"
#include "employee.h"
#include "file_names.h"

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

    std::stack<std::string> gameNames;
    std::stack<std::string> publisherNames;

    int requestId;
    int gameId;

    Genre getGenre();

    int getTesterWage();

    std::set<Genre> getTesterGenres();

    std::string getPublisherName();

    std::string getGameName();

    std::shared_ptr<ReviewRequest> getReviewRequest();

    static void save(const std::string&);

    std::string summary();

    std::mt19937 generator;

public:

    Simulation(int newSimulationLen, int newNumTesters, int newNumPublishers, int newNumGames,
               std::stack<std::string> newGameNames, std::stack<std::string> newPublisherNames);

    void start();
};