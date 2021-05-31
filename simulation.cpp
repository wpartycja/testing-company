#include "simulation.h"

#include <iostream>
#include <random>
#include <chrono>
#include <thread>


Simulation::Simulation(int n_simulation_len, int n_num_testers, int n_numb_publishers, int n_num_games)
    : simulation_len(n_simulation_len), num_testers(n_num_testers), num_publishers(n_numb_publishers),  num_games(n_num_games), manager(Simulation::getManager())
    {
        publishers = Simulation::getPublishers();
        request_id = 0;
    }


void Simulation::start() {
    std::string log = "Simulation started.\n";

    for (unsigned int h = 0; h < simulation_len; h++) {
        std::cout << "Hour " << h << ":\n";
        auto make_request = rand() % 4;

        switch (make_request) {
        case 0:
            auto request = Simulation::drawReviewRequest();
            std::cout << "Following request has been added:\n" << request;
            manager.assignRequest(&request);
            break;
        }

        manager.nextHour();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    std::cout << "\nSimulation has ended succesfully after " << simulation_len << "hours.";

    Simulation::save(log);
}

ReviewRequest Simulation::drawReviewRequest() {
    auto draw_publisher = rand() % publishers.size();
    auto publisher = publishers[draw_publisher];
    auto draw_game = rand() % publisher.getGames().size();
    auto game = publisher.getGames()[draw_game];
    auto draw_hours = rand() % 20 + 4;
    auto request = ReviewRequest(request_id, game, draw_hours);
    publisher.addReviewRequest(request);
    request_id++;
    return request;
}

std::vector<Publisher> Simulation::getPublishers() {
    std::vector<Publisher> new_pub;

    for (int i = 0; i < num_publishers; i++) {
        auto publisher = Publisher(Simulation::getPublisherName(), Simulation::getGames());
        new_pub.push_back(publisher);
    }
    return new_pub;
}

std::string Simulation::getPublisherName() {
    return "";                      //TODO wybieranie nazw firmy z listy albo pliku
}

std::vector<Game> Simulation::getGames() {
    std::vector<Game> games;
    auto number_of_gaames = num_games / num_publishers;
    for (int i = 0; i < number_of_gaames; i++) {
        auto game = Game();         //TODO wybieranie gry z listy lub pliku
        games.push_back(game);
    }
    return games;
}

Manager Simulation::getManager() {
    std::list<Tester> testers;

    for (int i = 0; i < num_publishers; i++) {
        auto tester = Tester(i, Simulation::randomTesterWage(), Simulation::drawTesterGenres());
        testers.push_back(tester);
    }
    auto new_manager = Manager(1, 30, testers);
    return new_manager;
}

int Simulation::randomTesterWage() {
    return rand() % 10 + 15;
}

std::set<Genre> Simulation::drawTesterGenres() {
    std::set<Genre> genres;
    auto number_of_genres = rand() % 3 + 1;
    for (int i = 0; i < number_of_genres; i++) {
        auto genre;                 //TODO wybieranie genre z listy albo pliku
        genres.insert(genre);
    }
    return genres;
}

void Simulation::save(std::string sim_log) {
                                    //TODO zapisywanie wyników symulacji
}