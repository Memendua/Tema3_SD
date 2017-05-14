#include <vector>
#include <unordered_map>
#include <string>
#include <limits>

#include "structs.h"

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
	if (ratings.find(user_id) == std::unordered_map::end) {
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

actor::actor(std::string actor_id, std::string name) {
	this->actor_name = name;
	this->actor_id = actor_id;
	this->debut_year = INT_MAX;
	this->last_year = INT_MIN;
}

