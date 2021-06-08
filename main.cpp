#include <iostream>
#include "employee.h"
#include "simulation.h"
#include <chrono>
#include <thread>

int main() {

    auto sim = Simulation(80, 20, 2, 10);
    sim.start();

    return 0;
}