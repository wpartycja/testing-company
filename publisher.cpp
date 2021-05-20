#include <iostream>
#include "publisher.h"


//constructor
Publisher::Publisher(std::string n_name, std::vector<Game> n_games, std::set<Genre> n_genres) {
    name = n_name;
    games = n_games;
    genres = n_genres;
    requests = {};
}

