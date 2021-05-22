#pragma once

#include "game.h"

//Time unit
unsigned int HOUR;


//Game

//constructor
Game::Game(unsigned int n_id, Genre n_genre, std::string n_title, const std::string n_publisher) :
	id(n_id), genre(n_genre), title(n_title), publisher(n_publisher) {}

//get functions
unsigned int Game::getId() {
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
	int number_of_ratings = ratings.size();
	float sum = 0;
	for (int i = 0; i < number_of_ratings; i++) {
		sum += ratings[i];
	}
	return sum / number_of_ratings;
}

//add rating
void Game::addRating(float rating) {
	ratings.push_back(rating);
}


//ReviewRequest

//constructor
ReviewRequest::ReviewRequest(unsigned int n_id, Game n_game, unsigned int n_hoursRequested, unsigned int n_hourStart) :
	id(n_id), game(n_game), hoursRequested(n_hoursRequested), hourStart(n_hourStart)
{
	hoursTested = 0;
	wage = setWage();
	hourPaid = NULL;
	paid = false;
}

//get function
Game ReviewRequest::getGame() {
	return game;
}

//set wage functions
unsigned int ReviewRequest::setWage() {
	return game.getGenre() % 10 * 20;
}

void ReviewRequest::setWage(float n_wage) {
	wage = n_wage;
}

//getPrice
unsigned int ReviewRequest::getPrice() {
	return hoursTested * wage;
}

//paying functions
bool ReviewRequest::isPaid() {
	if (paid) return true;
	return false;
}

void ReviewRequest::pay() {
	paid = true;
	hourPaid = HOUR;
}
