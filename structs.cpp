#include <vector>
#include <unordered_map>
#include <string>
#include <limits.h>

#include "structs.h"

movie::movie() {
	this->rating = 0;
	this->nr_ratings = 0;
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
	this->nr_ratings = 0;
}

movie::~movie() {};

void movie::add_rating(std::string user_id, int rating) {
	if (ratings.find(user_id) == ratings.end()) {
		ratings[user_id] = rating;
		this->rating *= this->nr_ratings;
		++this->nr_ratings;
		this->rating += rating;
		this->rating /= this->nr_ratings;
	}
}

void movie::update_rating(std::string user_id, int rating) {
	this->rating *= this->nr_ratings;
	this->rating -= ratings[user_id];
	ratings[user_id] = rating;
	this->rating += rating;
	this->rating /= nr_ratings;
}

void movie::remove_rating(std::string user_id) {
	this->rating *= this->nr_ratings;
	this->rating -= ratings[user_id];
	ratings.erase(user_id);
	--this->nr_ratings;

	if (this->nr_ratings) {
		this->rating /= nr_ratings;
	} else {
		this->rating = 0;
	}
}

bool movie::operator<(const movie &movie2) const {
	if (this->timestamp > movie2.timestamp) {
		return true;
	}

	return false;
}

double movie::get_rating() {
	return this->rating;
}

std::string movie::get_movie_id() const {
	return movie_id;
}

bool movie::no_ratings() {
	return nr_ratings ? false : true;
}

actor::actor() {
	this->debut_year = INT_MAX;
	this->last_year = INT_MIN;
	this->years = 0;
}

actor::actor(std::string actor_id, std::string actor_name) {
	this->actor_name = actor_name;
	this->actor_id = actor_id;
	this->debut_year = INT_MAX;
	this->last_year = INT_MIN;
	this->years = 0;
}

actor::actor(const actor &actor2) {
    this->debut_year = actor2.debut_year;
    this->last_year = actor2.last_year;
    this->years = actor2.years;
    this->actor_name = actor2.actor_name;
    this->actor_id = actor2.actor_id;
}

actor::~actor() {};

int& actor::get_debut_year() {
    return debut_year;
}

int& actor::get_last_year() {
    return last_year;
}

int& actor::get_years() {
    return years;
}

std::string actor::get_id() {
	return actor_id;
}

bool actor::operator<(const actor &actor2) const {
    if (this->years > actor2.years) {
    	return true;
    } else if (this->years == actor2.years) {
    	if (this->actor_id < actor2.actor_id) {
    		return true;
    	}
    }

    return false;
}

actor& actor::operator=(const actor &actor2) {
    this->debut_year = actor2.debut_year;
    this->last_year = actor2.last_year;
    this->years = actor2.years;
    this->actor_name = actor2.actor_name;
    this->actor_id = actor2.actor_id;
    return *this;
}

director::director() {
	nr_actors = 0;
}

director::director(std::string name) {
    director_name = name;
    nr_actors = 0;
}

director::director(const director &director2) {
    this->director_name = director2.director_name;
    this->nr_actors = director2.nr_actors;
    this->collaborations = director2.collaborations;
}

director::~director() {};

director& director::operator=(const director &director2) {
    this->director_name = director2.director_name;
    this->nr_actors = director2.nr_actors;
    this->collaborations = director2.collaborations;
    return *this;
}

bool director::check_collaboration(std::string actor_id) {
    if (collaborations.find(actor_id) != collaborations.end()) {
        return true;
    }
    return false;
}

void director::add_collaboration(std::string actor_id) {
    collaborations.insert(actor_id);
    ++nr_actors;
}

bool director::operator<(const director &director2) const {
    if (this->nr_actors > director2.nr_actors) {
    	return true;
    } else if (this->nr_actors == director2.nr_actors) {
    	if (this->director_name < director2.director_name) {
    		return true;
    	}
    }

    return false;
}
