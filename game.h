#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum Genre {
    action, adventure, action_adventure, RPG, simulation,
    strategy, sports, MMO, sandbox, casual, horror,
    logic, party, typing, photography, idle
};

class Game {


    const int id;
    const Genre genre;
    const std::string title;
    std::vector<float> ratings;

public:
    Game(int n_id, Genre n_genre, std::string n_title);

    int getId() const;

    Genre getGenre();

    std::string getTitle() const;

    float getAvgRating();

    int addRating(int rating);

    std::string display();
};

std::ostream &operator<<(std::ostream &output, Game &game);

class ReviewRequest {
    int id;
    std::shared_ptr<Game> game;
    int hoursTested = 0;
    int hourPaid = 0;
    bool paid = false;
    int hoursRequested;
    int price = 0;
    int rate = 0;

public:
    ReviewRequest(int n_id, std::shared_ptr<Game> n_game, int n_hoursRequested);

    std::shared_ptr<Game> getGame() const;

    int getId() const;

    int getRate() const;

    int getHoursRequested() const;

    int getHoursTested() const;

    unsigned int getHoursLeft() const;

    int getPrice() const; // get price

    void setPrice(int n_price);

    void setRate(int n_rate);

    bool isPaid() const;

    void pay(int hour); // mark this request as paid

    int test(int hours);

    std::string display();
};

std::ostream &operator<<(std::ostream &output, ReviewRequest &rewiew);