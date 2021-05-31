#pragma once

#include "publisher.h"
#include "game.h"
#include "employee.h"

#include <string>
#include <vector>
#include <set>

class Simulation{

    std::vector<Publisher(std::string n_name, std::vector<Game> games, std::set<Genre> n_genres)> publishers;

public:
    Simulation();

    void nextDay();
};