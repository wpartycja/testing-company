#include <iostream>
#include <utility>
#include "publisher.h"


//constructor
Publisher::Publisher(std::string n_name, std::vector<Game> n_games) :
        name(std::move(n_name)), games(std::move(n_games)) {}


std::vector<Game> Publisher::getGames() {
        return games;
}

void Publisher::addReviewRequest(ReviewRequest request) {
        requests.push_back(request);
}

std::string Publisher::display() {
        std::string display = "";
        display += name + " have " + std::to_string(games.size()) + " games.\n";
        for (int i=0; i<games.size(); i++) {display += games[i].display();}
        return display;
}