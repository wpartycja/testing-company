#include <iostream>
#include <utility>
#include "publisher.h"


//constructor
Publisher::Publisher(std::string n_name, std::vector<Game> n_games)
        : name(std::move(n_name)), games(std::move(n_games)) {}

