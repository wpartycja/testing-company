#pragma once

#include "game.h"

#include <string>
#include <vector>
#include <set>


class Publisher {
    std::string name;
    std::vector<std::shared_ptr<Game>> games;
    std::vector<std::shared_ptr<ReviewRequest>> requests;

public:
    Publisher(std::string n_name, std::vector<std::shared_ptr<Game>> n_games);

    std::vector<std::shared_ptr<Game>> getGames();

    void addReviewRequest(std::shared_ptr<ReviewRequest> request);

    std::string getName();
};
