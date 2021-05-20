#pragma once

#include <string>
#include <vector>
#include <set>
#include "game.h"

class Publisher {
    std::string name;
    std::vector<Game> games;
    std::vector<ReviewRequest> requests;
    std::set<Genre> genres;

public:
    Publisher(std::string n_name, std::vector<Game> n_games, std::set<Genre> n_genres);

    void nextHour();
};

