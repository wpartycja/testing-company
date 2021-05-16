#pragma once

enum Genre;

class Game {
    const uint id;
    const Genre genre;
    const std::string title;
    const std::string publisher; // czy gra powinna miec publishera? i tak to publisher(jako obiekt) przechowuje gry
    vector<float> ratings;

public:
    Game(uint id, Genre genre, std::string title, const std::string publisher);

    uint getId();

    Genre getGenre();

    std::string getTitle();

    std::string getPublisher();

    float getAvgRating();

    friend std::ostream &operator<<(std::ostream &os, const Game &game);

    void addRating(float rating);
};

std::ostream &operator<<(std::ostream &os, const Game &game);
