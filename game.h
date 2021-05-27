#pragma once

#include <string>
#include <vector>

enum Genre {
    action, adventure, action_adventure, RPG, simulation,
    strategy, sports, MMO, sandbox, casual, horror,
    logic, party, typing, photography, idle
};

class Game {


    const unsigned int id;
    const Genre genre;
    const std::string title;
    const std::string publisher; // czy gra powinna miec publishera? i tak to publisher(jako obiekt) przechowuje gry
    std::vector<float> ratings;

public:
    Game(unsigned int n_id, Genre n_genre, std::string n_title, std::string n_publisher);

    unsigned int getId() const;

    Genre getGenre();

    std::string getTitle();

    std::string getPublisher();

    float getAvgRating();

    void addRating(float rating);
};

class ReviewRequest {
    unsigned int id;
    Game game;
    unsigned int hoursTested = 0;
    unsigned int hourPaid = 0;
    bool paid = false;
    unsigned int hoursRequested;
    float price = 0;

public:
    ReviewRequest(unsigned int n_id, Game n_game, unsigned int n_hoursRequested);

    Game getGame() const;
    unsigned int getHoursRequested() const;
    unsigned int getPrice() const; // get price

    void setPrice(float n_price);

    bool isPaid() const;

    void pay(); // mark this request as paid
    unsigned int getHoursLeft() const;

    void test(unsigned int hours);
};