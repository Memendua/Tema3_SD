// Copyright 2017 Popa Bogdan, Rosca Alin-Costin
#include <vector>
#include <unordered_map>
#include <string>

#include "include/movie.h"

movie::movie() {
	this->rating = 0;
}

explicit movie::movie(int timestamp) {
	this->movie_name = "";
	this->movie_id = "";
	this->timestamp = timestamp;
	this->rating = 0;
}

movie::movie(std::string movie_name, std::string movie_id, int timestamp,
		  	 std::vector<std::string> categories, std::string director_name,
          	 std::vector<std::string> actor_ids) {
	this->movie_name = movie_name;
	this->movie_id = movie_id;
	this->timestamp = timestamp;
	this->categories = categories;
	this->director_name = director_name;
	this->actor_ids = actor_ids;
	this->rating = 0;
}

movie::~movie() {}

double movie::add_rating(std::string user_id, int rating) {
	if (ratings.find(user_id) == ratings.end()) {
		double old_rating = this->rating;
		this->rating *= this->ratings.size();
		ratings[user_id] = rating;
		this->rating += rating;
		this->rating /= this->ratings.size();
		return old_rating;
	}
	return 0;
}

double movie::update_rating(std::string user_id, int rating) {
	double old_rating = this->rating;
	this->rating *= this->ratings.size();
	this->rating -= ratings[user_id];
	ratings[user_id] = rating;
	this->rating += rating;
	this->rating /= ratings.size();
	return old_rating;
}

double movie::remove_rating(std::string user_id) {
	double old_rating = this->rating;
	this->rating *= this->ratings.size();
	this->rating -= ratings[user_id];
	ratings.erase(user_id);

	if (ratings.size()) {
		this->rating /= ratings.size();
	} else {
		this->rating = 0;
	}
	return old_rating;
}

void movie::set_position(int position) {
	this->position = position;
}

void movie::set_rating_until_this(double prev_rating) {
	this->rating_until_this = this->rating + prev_rating;
}

bool movie::operator<(const movie &movie2) const {
    if (this->nr_ratings() < movie2.nr_ratings()) {
        return true;
    } else if (this->nr_ratings() == movie2.nr_ratings()) {
        if (this->get_movie_id() > movie2.get_movie_id()) {
            return true;
        }
    }

    return false;
}

double movie::get_rating() const {
	return this->rating;
}

double movie::get_rating_until_this() const {
	return this->rating_until_this;
}

int movie::get_timestamp() const {
	return this->timestamp;
}

int movie::get_position() const {
	return this->position;
}

std::string movie::get_movie_id() const {
	return movie_id;
}

int movie::nr_ratings() const {
	return ratings.size();
}
