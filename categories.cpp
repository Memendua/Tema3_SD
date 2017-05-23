// Copyright 2017 Popa Bogdan, Rosca Alin-Costin
#include <time.h>

#include "include/categories.h"
#include "include/movie.h"

category::category() {
	this->best_rating = -1;
	this->best_year = -1;
	this->up_to_date = false;
}

void category::add_movie_in_year(movie &m) {
	time_t time = m.get_timestamp();
	int year = gmtime(&time)->tm_year + 1900;
	years[year].add_movie(m);
	up_to_date = false;
}

void category::outdate(int timestamp) {
	time_t time = timestamp;
	int year = gmtime(&time)->tm_year + 1900;
	years[year].outdate();
	up_to_date = false;
}

int category::get_best_year() {
	if (up_to_date) {
		return best_year;
	}
	best_rating = -1;
	for (auto it = years.begin(); it != years.end(); ++it) {
		if (!it->second.isUpdated()) {
			it->second.update();
		}
		if (it->second.isUpdated()) {
			double current_rating = it->second.get_avg_rating();
			int current_year = it->first;
			if (best_rating < current_rating) {
				best_rating = current_rating;
				best_year = current_year;
			} else if (best_rating == current_rating) {
				if (best_year > current_year) {
					best_year = current_year;
				}
			}
		}
	}
	up_to_date = true;

	if (best_rating == -1) {
		return -1;
	}

	return best_year;
}