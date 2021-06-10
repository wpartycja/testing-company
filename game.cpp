#include "game.h"

        /* class Game */

// constructor
Game::Game(int newId, Genre newGenre, std::string newTitle) :
        id(newId), genre(newGenre), title(std::move(newTitle)), ratings() {}

// get functions

Genre Game::getGenre() {
    return genre;
}

std::string Game::getTitle() const {
    return title;
}

float Game::getAvgRating() {
    /* returns average rating from all that received */

    size_t number_of_ratings = ratings.size();
    float sum = 0;
    for (unsigned int i = 0; i < number_of_ratings; i++) {
        sum += ratings[i];
    }
    return sum / (float) number_of_ratings;
}

std::string Game::getPublisher() const{
    return publisher;
}

int Game::addRating(int rating) {
    ratings.push_back(rating);
    return rating;
}

std::string Game::display() {
    std::string display;
    display = "\tGame title: " + title + "\t\t\tGame ID: " + std::to_string(id);
    return display;
}

void Game::setPublisher(std::string newPublisher) {
    publisher = newPublisher;
}

std::ostream &operator<<(std::ostream &output, Game &game) {
    return output << game.display();
}


        /* class ReviewRequest */

// constructor
ReviewRequest::ReviewRequest(int newId, std::shared_ptr<Game> newGame, int newHoursRequested) :
        id(newId), game(std::move(newGame)), hoursRequested(newHoursRequested) {}


// get functions
std::shared_ptr<Game> ReviewRequest::getGame() const {
    return game;
}

int ReviewRequest::getId() const {
    return id;
}

int ReviewRequest::getRate() const {
    return rate;
}

int ReviewRequest::getPrice() const {
    return price;
}

int ReviewRequest::getHoursRequested() const {
    return hoursRequested;
}

int ReviewRequest::getHoursTested() const {
    return hoursTested;
}

unsigned int ReviewRequest::getHoursLeft() const {
    return hoursRequested - hoursTested;
}

int ReviewRequest::getSubmissionHour() const{
    return submissionHour;
}

int ReviewRequest::getHourPaid() const {
    return hourPaid;
}

// set functions
void ReviewRequest::setPrice(int n_price) {
    price = n_price;
}

void ReviewRequest::setRate(int n_rate) {
    rate = n_rate;
}

void ReviewRequest::setSubmissionHour(int newHour) {
    submissionHour = newHour;
}

//paying functions
bool ReviewRequest::isPaid() const {
    return paid;
}

void ReviewRequest::pay(int hour) {
    paid = true;
    hourPaid = hour;
}

void ReviewRequest::addOverhang(int overhang) {
    price += overhang;
}

// another
int ReviewRequest::test(int hours) {
    int testedFor = std::min(hours, hoursRequested - hoursTested);
    hoursTested += testedFor;
    return testedFor;
}

std::string ReviewRequest::display() const {
    std::string display;
    display += "\tId of new request: " + std::to_string(id) + "\n";
    display += "\tTitle of the game: " + ReviewRequest::getGame()->getTitle() + "\n";
    display += "\tRequested hours to test: " + std::to_string(hoursRequested) + "\n";
    return display;
}

std::ostream &operator<<(std::ostream &output, ReviewRequest &review) {
    return output << review.display();
}