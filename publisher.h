#pragma once

#include "game.h"

#include <string>
#include <vector>
#include <set>


class Publisher {
    std::string name;
    std::vector<Game> games;
    std::vector<ReviewRequest> requests;
    std::set<Genre> genres;

public:
    Publisher(std::string n_name, std::vector<Game> n_games);

    std::vector<Game> getGames();

    void addReviewRequest(ReviewRequest request);

    std::string display();
};
