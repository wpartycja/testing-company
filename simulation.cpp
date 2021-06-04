#include "simulation.h"

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>


Simulation::Simulation(int n_simulation_len, int n_num_testers, int n_numb_publishers, int n_num_games)
    : simulation_len(n_simulation_len), num_testers(n_num_testers), num_publishers(n_numb_publishers),  num_games(n_num_games)
    {
        manager = Simulation::getManager();
        std::cout<<num_testers<<std::endl;
        std::cout<<"Manager created succesfully"<<std::endl;
        Simulation::readData();
        std::cout<<"Data iported succesfully"<<std::endl;
        publishers = Simulation::getPublishers();
        std::cout<<"Publishers created succesfully"<<std::endl;
        request_id = 0;
    }


void Simulation::start() {
    std::cout << "Simulation started.\n";
    std::string log;

    for (unsigned int h = 0; h < simulation_len; h++) {
        std::cout << "Hour " << h << ":\n";
        auto make_request = rand() % 2;

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

    std::cout << "\nSimulation has ended succesfully after " << simulation_len << " hours.";

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
        auto publisherName = Simulation::getPublisherName();
        auto publisher = Publisher(publisherName, Simulation::getGames(publisherName));
        new_pub.push_back(publisher);
    }
    return new_pub;
}

std::string Simulation::getPublisherName() {
    auto name = gameDevs.top();
    gameDevs.pop();
    return name;
}

std::vector<Game> Simulation::getGames(std::string devName) {
    std::vector<Game> games;
    auto number_of_games = num_games / num_publishers;
    for (int i = 0; i < number_of_games; i++) {
        auto game = Game(Simulation::getGameId(), Simulation::randomGenre(), Simulation::getGameName(), devName);
        games.push_back(game);
    }
    return games;
}

std::string Simulation::getGameName() {
    auto name = gameNames.top();
    gameNames.pop();
    return name;
}

int Simulation::getGameId() {
    return all_games - gameNames.size();
}

Manager Simulation::getManager() {
    std::cout<<"Generate testers"<<std::endl;
    std::list<Tester> testers;

    for (int i = 0; i < num_testers; i++) {
        auto tester = Tester(i, Simulation::randomTesterWage(), Simulation::drawTesterGenres());
        std::cout<<"\t!!!Tester generated!!!"<<std::endl;
        testers.push_back(tester);
    }
    std::cout<<"Testers created!"<<std::endl;
    auto new_manager = Manager(1, 30, testers);
    return new_manager;
}

int Simulation::randomTesterWage() {
    return rand() % 10 + 15;
}

std::set<Genre> Simulation::drawTesterGenres() {
    std::set<Genre> genres;
    auto number_of_genres = rand() % 3 + 2;
    for (int i = 0; i < number_of_genres; i++) {
        genres.insert(Simulation::randomGenre());
    }
    return genres;
}

Genre Simulation::randomGenre(){
    auto draw_genre = rand() % 16;
    auto genre = Genre(draw_genre);
    return genre;
}

void Simulation::readData() {
    std::fstream file;
    file.open("data.txt", std::ios::in);
    int counter = 1;
    std::string name;
    while(getline(file, name))
    {
        if (counter < 33) gameDevs.push(name);
        if (counter > 34) gameNames.push(name);
        counter++;
    }
    file.close();
    all_games = gameNames.size();
}

void Simulation::save(std::string sim_log) {
                                    //TODO zapisywanie wyników symulacji
}