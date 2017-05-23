// Copyright 2017 Popa Bogdan, Rosca Alin-Costin
#include <unordered_map>

#include "include/years.h"

year::year() {
	average_rating = 0.0;
	up_to_date = false;
}

void year::outdate() {
	up_to_date = false;
}

void year::update() {
	double total_rating = 0.0;
	int nr_ratings = 0;
	for (auto it = movies_in_year.begin(); it != movies_in_year.end(); ++it) {
		if (it->second.nr_ratings()) {
			total_rating += it->second.get_rating();
			nr_ratings++;
		}
	}

	if (nr_ratings != 0) {
		average_rating = total_rating / nr_ratings;
		up_to_date = true;
	}
}

void year::add_movie(movie &m) {
	movies_in_year.emplace(m.get_movie_id(), m);
	up_to_date = false;
}

double year::get_avg_rating() {
	return average_rating;
}

bool year::isUpdated() {
	return up_to_date;
}