#include "game.h"

//Time unit
unsigned int HOUR;


//Game

//constructor
Game::Game(unsigned int n_id, Genre n_genre, std::string n_title, std::string n_publisher) :
        id(n_id), genre(n_genre), title(std::move(n_title)), publisher(std::move(n_publisher)), ratings() {}

//get functions
unsigned int Game::getId() const {
    return id;
}

Genre Game::getGenre() {
    return genre;
}

std::string Game::getTitle() {
    return title;
}

std::string Game::getPublisher() {
    return publisher;
}

float Game::getAvgRating() {
    size_t number_of_ratings = ratings.size();
    float sum = 0;
    for (int i = 0; i < number_of_ratings; i++) {
        sum += ratings[i];
    }
    return sum / (float) number_of_ratings;
}

//add rating
void Game::addRating(float rating) {
    ratings.push_back(rating);
}


//ReviewRequest

//constructor
ReviewRequest::ReviewRequest(unsigned int n_id, Game n_game, unsigned int n_hoursRequested) :
        id(n_id), game(std::move(n_game)), hoursRequested(n_hoursRequested) {}


//get function
Game ReviewRequest::getGame() const {
    return game;
}

unsigned int ReviewRequest::getPrice() const {
    // mysle ze mozna to uzaleznic np. od liczby testerow(im wiecej testerow tym taniej) ale na razie zostawiam 30 na sztywno
    // edit od Pati: zrobiłam tak że manager bedzie patrzył miedzy tym ile ma pracowników zdolnych do tego i na tej zasadzie ustalał cene
    return price;
}

unsigned int ReviewRequest::getHoursRequested() const {
    return hoursRequested;
}

//set function
void ReviewRequest::setPrice(float n_price) {
    price = n_price;
}

//paying functions
bool ReviewRequest::isPaid() const {
    return paid;
}

void ReviewRequest::pay() {
    paid = true;
    hourPaid = HOUR;
}

unsigned int ReviewRequest::getHoursLeft() const {
    return hoursRequested - hoursTested;
}

void ReviewRequest::test(unsigned int hours) {
    hoursTested += std::min(hours, hoursRequested - hoursTested);
}
