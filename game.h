#pragma once

#include <iostream>
#include <string>
#include <vector>

enum Genre {
    action, adventure, action_adventure, RPG, simulation,
    strategy, sports, MMO, sandbox, casual, horror,
    logic, party, typing, photography, idle
};

class Game {


    const int id;
    const Genre genre;
    const std::string title;
    const std::string publisher; // czy gra powinna miec publishera? i tak to publisher(jako obiekt) przechowuje gry
    std::vector<float> ratings;

public:
    Game(int n_id, Genre n_genre, std::string n_title, std::string n_publisher);

    int getId() const;

    Genre getGenre();

    std::string getTitle();

    std::string getPublisher();

    float getAvgRating();

    void addRating(float rating);

    std::string display();
};

std::ostream& operator<< (std::ostream& output, Game& game);

class ReviewRequest {
    int id;
    Game game;
    int hoursTested = 0;
    int hourPaid = 0;
    bool paid = false;
    int hoursRequested;
    int price = 0;

public:
    ReviewRequest(int n_id, Game n_game, int n_hoursRequested);

    Game getGame() const;

    int getId() const;

    int getHoursRequested() const;

    int getPrice() const; // get price

    void setPrice(int n_price);

    bool isPaid() const;

    void pay(int hour); // mark this request as paid
    int getHoursLeft() const;

    void test(int hours);

    std::string display();
};

std::ostream& operator<< (std::ostream& output, ReviewRequest& rewiew);