#include "simulation.h"

#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <utility>


Simulation::Simulation(int n_simulation_len, int n_num_testers, int n_numb_publishers, int n_num_games,
                       std::stack<std::string> newGameNames, std::stack<std::string> newPublisherNames)
        : simulation_len(n_simulation_len), num_testers(n_num_testers), num_publishers(n_numb_publishers),
          num_games(n_num_games), gameNames(std::move(newGameNames)), publisherNames(std::move(newPublisherNames)),
          requestId(0), gameId(0) {


    // create publishers
    for (int i = 0; i < num_publishers; i++) {

        // create games for each publisher
        std::vector<std::shared_ptr<Game>> publisherGames;
        auto number_of_games = num_games / num_publishers;
        for (int j = 0; j < number_of_games; j++) {
            auto game = std::make_shared<Game>(gameId++, getGenre(), getGameName());
            publisherGames.push_back(game);
        }

        auto publisher = std::make_shared<Publisher>(getPublisherName(), publisherGames);
        publishers.push_back(publisher);
    }

    // create manager with testers
    std::list<std::shared_ptr<Tester>> testers;
    for (int i = 0; i < num_testers; i++) {
        auto tester = std::make_shared<Tester>(i, getTesterWage(), getTesterGenres());
        testers.push_back(tester);
    }

    manager = Manager(1, 30, testers);
}


void Simulation::start() {
    for (int h = 1; h <= simulation_len; h++) {

        std::ostringstream requestsLog;

        if (rand() % 5 == 0) {
            requestsLog << manager.assignRequest(getReviewRequest(), h);
        }

        std::ostringstream testingLog;
        testingLog << "\nHour " << h << ":\n"  << requestsLog.str() << manager.nextHour(h);

        std::cout << testingLog.str();
        save(testingLog.str());
//        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        #ifdef WIN32
            std::system("pause");
        #else
            std::system("read");
        #endif
    }

    std::cout << summary();
    save(summary());
}

std::string Simulation::summary() {
    std::ostringstream summary;
    summary << "\n\n\n\t***Summary***\n\nSimulation duration: " << simulation_len <<"h.\nNumber of testers: " << num_testers
            << "\n\nManager:\n" << manager.summary();
    return summary.str();
}

std::shared_ptr<ReviewRequest> Simulation::getReviewRequest() {
    auto publisher = publishers[rand() % publishers.size()];
    auto game = publisher->getGames()[rand() % publisher->getGames().size()];
    auto hours = rand() % 10 + 10;
    auto request = std::make_shared<ReviewRequest>(requestId++, game, hours);
    publisher->addReviewRequest(request);
    return request;
}

std::string Simulation::getPublisherName() {
    auto name = publisherNames.top();
    publisherNames.pop();
    return name;
}


std::string Simulation::getGameName() {
    auto name = gameNames.top();
    gameNames.pop();
    return name;
}

int Simulation::getTesterWage() {
    return rand() % 15 + 10;
}

std::set<Genre> Simulation::getTesterGenres() {
    std::set<Genre> genres;
    auto number_of_genres = rand() % 3 + 2;
    for (int i = 0; i < number_of_genres; i++) {
        genres.insert(getGenre());
    }
    return genres;
}

Genre Simulation::getGenre() {
    return Genre(rand() % 16);
}

void Simulation::save(std::string sim_log) {
    std::fstream file;
    file.open("save.txt", std::ios::out | std::ios::app);
    file << sim_log;
    file.close();
}
