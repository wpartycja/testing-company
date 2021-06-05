#include "simulation.h"

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>

std::string LOAD = "data.txt";
std::string SAVE = "save.txt";


Simulation::Simulation(int n_simulation_len, int n_num_testers, int n_numb_publishers, int n_num_games)
    : simulation_len(n_simulation_len), num_testers(n_num_testers), num_publishers(n_numb_publishers),  num_games(n_num_games)
    {
        std::string log = "\n";
        manager = Simulation::getManager();
        std::cout<<"Manager created succesfully with "<< std::to_string(num_testers)<<" testers.\n"<<std::endl;
        log += "Manager created succesfully with " + std::to_string(num_testers) + " testers.\n";
        Simulation::readData();
        std::cout<<"Data loaded succesfully."<<std::endl;
        std::cout<<"\t"<<gameDevs.size()<<" game developers loaded."<<std::endl;
        std::cout<<"\t"<<gameNames.size()<<" games loaded.\n"<<std::endl;
        log += "\nData loaded succesfully.\n\t" + std::to_string(gameDevs.size());
        log += " game developers loaded.\n\t" + std::to_string(gameNames.size()) + " games loaded.\n";
        publishers = Simulation::getPublishers();
        std::cout<<"Publishers created succesfully."<<std::endl;
        log += "\nPublishers created succesfully.\n\n";
        Simulation::save(log);
        request_id = 0;
    }


void Simulation::start() {
    std::string log;
    std::cout << "\n\nSimulation started.\n";
    log +=  "Simulation started.\n";
    for (unsigned int h = 0; h < simulation_len; h++) {
        std::cout << "Hour " << h << ":\n";
        log += "Hour " + std::to_string(h) +  ":\n";
        auto make_request = rand() % 2;
        switch (make_request) {
        case 0:
            auto request = Simulation::drawReviewRequest();
            std::cout << "Following request has been added:\n" << request;
            log += "Following request has been added:\n" + request.display();
            auto assign = manager.assignRequest(&request);
            std::cout << assign;
            log += assign;
            break;
        }

        auto nexth = manager.nextHour();
        std::cout << nexth;
        log += nexth;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        if (h % 2 == 0) {Simulation::save(log); log = "";}
    }

    std::cout << "\nSimulation has ended succesfully after " << simulation_len << " hours.";
    log += "\nSimulation has ended succesfully after " + std::to_string(simulation_len) + " hours.";

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
    std::string log = "";
    for (int i = 0; i < num_publishers; i++) {
        auto publisherName = Simulation::getPublisherName();
        auto publisher = Publisher(publisherName, Simulation::getGames(publisherName));
        log += publisher.display();
        new_pub.push_back(publisher);
    }
    std::cout<<log;
    Simulation::save(log);
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
    std::string log = "";
    log += "Generated testers:\n";
    std::list<Tester> testers;

    for (int i = 0; i < num_testers; i++) {
        auto tester = Tester(i, Simulation::randomTesterWage(), Simulation::drawTesterGenres());
        log += "\t" + std::to_string(i) + ". tester generated.\n";
        testers.push_back(tester);
    }
    std::cout<<log;
    Simulation::save(log);
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
    file.open(LOAD, std::ios::in);
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
    std::fstream file;
    file.open(SAVE, std::ios::out | std::ios::app);
    file << sim_log;
    file.close();
}