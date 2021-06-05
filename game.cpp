#include "game.h"




//Game

//constructor
Game::Game(int n_id, Genre n_genre, std::string n_title, std::string n_publisher) :
        id(n_id), genre(n_genre), title(std::move(n_title)), publisher(std::move(n_publisher)), ratings() {}

//get functions
int Game::getId() const {
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

std::string Game::display() {
    std::string display = "";
    display += "\tGame title: " + title + "\t\t\tGame ID: " + std::to_string(id);
    display += "\n\tPublisher: " + publisher + "\t\tGenre: " + std::to_string(genre) + "\n";
    return display;
}

std::ostream& operator<< (std::ostream& output, Game& game) {
    return output << game.display();
}


//ReviewRequest

//constructor
ReviewRequest::ReviewRequest(int n_id, Game n_game, int n_hoursRequested) :
        id(n_id), game(std::move(n_game)), hoursRequested(n_hoursRequested) {}


//get function
Game ReviewRequest::getGame() const {
    return game;
}

int ReviewRequest::getId() const {
    return id;
}

int ReviewRequest::getPrice() const {
    // mysle ze mozna to uzaleznic np. od liczby testerow(im wiecej testerow tym taniej) ale na razie zostawiam 30 na sztywno
    // edit od Pati: zrobiłam tak że manager bedzie patrzył miedzy tym ile ma pracowników zdolnych do tego i na tej zasadzie ustalał cene
    return price;
}

int ReviewRequest::getHoursRequested() const {
    return hoursRequested;
}

//set function
void ReviewRequest::setPrice(int n_price) {
    price = n_price;
}

//paying functions
bool ReviewRequest::isPaid() const {
    return paid;
}

void ReviewRequest::pay(int hour) {
    paid = true;
    hourPaid = hour;
}

int ReviewRequest::getHoursLeft() const {
    return hoursRequested - hoursTested;
}

void ReviewRequest::test(int hours) {
    hoursTested += std::min(hours, hoursRequested - hoursTested);
}

std::string ReviewRequest::display() {
    std::string display = "";
    display += "\tId of new rewiew request: " + std::to_string(id) + "\n";
    display += "\tTitle of the game: " + ReviewRequest::getGame().getTitle() + "\n";
    display += "\tRequested hours to test: " + std::to_string(hoursRequested) + "\n";
    return display;
}

std::ostream& operator<< (std::ostream& output, ReviewRequest& rewiew) {
    return output << rewiew.display();
}