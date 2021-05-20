#pragma once

#include <string>

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
    Game(unsigned int id, Genre genre, std::string title, const std::string publisher);

    unsigned int getId();

    Genre getGenre();

    std::string getTitle();

    std::string getPublisher();

    float getAvgRating();

    void addRating(float rating);
};

class ReviewRequest {
    unsigned int id;
    Game game;
    unsigned int hoursRequested;
    unsigned int hoursTested;
    unsigned int hourStart;
    unsigned int hourPaid;
    bool paid;

public:
    ReviewRequest(unsigned int id, Game game, unsigned int hoursRequested, unsigned int hourStart);

    bool isPaid();

    unsigned int getPrice(); // get price based on hoursTested and number of testers
    void pay(); // mark this request as paid
};