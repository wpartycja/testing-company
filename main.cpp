#include "employee.h"
#include "simulation.h"

#include <iostream>
#include <thread>
#include <sstream>
#include <fstream>

std::string GAME_NAMES = "game_names.txt";
std::string PUBLISHER_NAMES = "publisher_names.txt";

int main(int argc, char* argv[]) {

    // checking if the number of given arguments is adequate
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " {duration}" << " {number_of_testers} " <<
                     "{number_of_publishers} " << "{number_of_games}" << std::endl;
        return 1;
    }

    // counting number of publishers and games
    // load game and publisher names from files
    int publishersNumber = 0, gamesNumber = 0;
    std::fstream file;
    std::string line;
    std::stack<std::string> publisherNames, gameNames;


    file.open(GAME_NAMES, std::ios::in);
    while (std::getline(file, line)){
        ++publishersNumber;
        gameNames.push(line);
    }
    file.close();

    file.open(PUBLISHER_NAMES, std::ios::in);
    while (std::getline(file, line)){
        ++gamesNumber;
        publisherNames.push(line);
    }
    file.close();

    // checking the type of given arguments
    for (int i = 1; i < 5; i++) {
        std::istringstream ss(argv[i]);
        int x;
        if (!(ss >> x)) {
            std::cerr << "Invalid argument: " << argv[i] << std::endl;
            return 1;
        } else if (!ss.eof()) {
            std::cerr << "Trailing characters in number: " << argv[i] << std::endl;
            return 1;
        } else if (atoi(argv[i]) <= 0){
            std::cerr << "Numbers should be greater than zero!" << std::endl;
            return 1;
        }
        switch (i){
            case 3:
                if (atoi(argv[i]) > publishersNumber){
                    std::cerr << "Argument nr " << i << " is too big. Sorry, we don't have enough publishers. " <<
                                 "Our maximum is: " << publishersNumber;
                    return 1;
                }
            case 4:
                if (atoi(argv[i]) > gamesNumber){
                    std::cerr << "Argument nr " << i << " is too big. Sorry, we don't have enough games. " <<
                                 "Our maximum is: " << gamesNumber;
                    return 1;
                }
            default:
                continue;
        }
    }


    //starting simulation
    std::cout << "Welcome in Testing Games Company Simulator!\n" << std::endl;
    auto sim = Simulation(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),
                          atoi(argv[4]), gameNames, publisherNames);
    sim.start();

    return 0;
}