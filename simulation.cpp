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