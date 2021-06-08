#include <iostream>
#include "employee.h"
#include "simulation.h"
#include <thread>
#include <sstream>

int main(int argc, char* argv[]) {
    // checking if the number of given arguments is adequate
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <duration>" << " <number_of_testers " <<
                     "<number_of_publishers>" << "<number_of_games>" << std::endl;
        return 1;
    }

    // checking the type of given arguments
    for (int i = 1; i < 5; i++) {
        std::istringstream ss(argv[i]);
        int x;
        if (!(ss >> x)) {
            std::cerr << "Invalid argument: " << argv[i] << '\n';
            return 1;
        } else if (!ss.eof()) {
            std::cerr << "Trailing characters in number: " << argv[i] << '\n';
            return 1;
        }
    }

    //starting simulation

    std::cout << "Welcome in Testing Games Company Simulator!\n" << std::endl;
    auto sim = Simulation(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),
                          atoi(argv[4]));
    sim.start();

    return 0;
}