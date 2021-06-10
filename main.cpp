#include "employee.h"
#include "simulation.h"

#include <iostream>
#include <thread>
#include <sstream>
#include <fstream>

int main(int argc, char *argv[]) {

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


    file.open("game_names.txt", std::ios::in);
    while (std::getline(file, line)) {
        ++publishersNumber;
        gameNames.push(line);
    }
    file.close();

    file.open("publisher_names.txt", std::ios::in);
    while (std::getline(file, line)) {
        ++gamesNumber;
        publisherNames.push(line);
    }
    file.close();

    // checking the type of given arguments
    try {
        for (int i = 1; i < 5; i++) {
            std::istringstream ss(argv[i]);
            int x;
            if (!(ss >> x)) {
                throw std::invalid_argument("Invalid argument: " + std::string(argv[i]));
            } else if (!ss.eof()) {
                throw std::invalid_argument("Trailing characters in number: " + std::string(argv[i]));
            } else if (atoi(argv[i]) <= 0) {
                throw std::invalid_argument("Arguments should be greater than 0");
            }
            switch (i) {
                case 3:
                    if (atoi(argv[i]) > publishersNumber) {
                        std::ostringstream msg;
                        msg << "Argument " << i << " can't be less than the number of publishers (" << publishersNumber
                            << ")";
                        throw std::invalid_argument(msg.str());
                    }
                    break;
                case 4:
                    if (atoi(argv[i]) > gamesNumber) {
                        std::ostringstream msg;
                        msg << "Argument " << i << " can't be less than the number of games (" << gamesNumber << ")";
                        throw std::invalid_argument(msg.str());
                    }
                    break;
                default:
                    continue;
            }
        }
    } catch (const std::invalid_argument &except) {
        std::cerr << "Error while reading arguments:\n" << except.what() << "\nTry again\n";
        return 1;
    }


    //starting simulation
    std::cout << "Welcome in Testing Games Company Simulator!\n" << std::endl;
    auto sim = Simulation(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),
                          atoi(argv[4]), gameNames, publisherNames);
    sim.start();

    return 0;
}