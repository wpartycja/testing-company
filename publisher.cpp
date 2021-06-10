#include "publisher.h"

#include <iostream>


        /* class Publisher */

//constructor
Publisher::Publisher(std::string n_name, std::vector<std::shared_ptr<Game>> n_games) :
        name(std::move(n_name)), games(std::move(n_games)) {}


std::vector<std::shared_ptr<Game>> Publisher::getGames() {
    return games;
}

void Publisher::addReviewRequest(std::shared_ptr<ReviewRequest> request) {
    requests.push_back(request);
}

std::string Publisher::getName() {
    return name;
}
