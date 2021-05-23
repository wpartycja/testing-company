#include <iostream>
#include <utility>
#include "publisher.h"


//constructor
Publisher::Publisher(std::string n_name, std::vector<Game> n_games, std::set<Genre> n_genres)
        : name(std::move(n_name)), games(std::move(n_games)), genres(std::move(n_genres)) {}

