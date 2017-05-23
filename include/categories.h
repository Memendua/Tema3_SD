// Copyright 2017 Popa Bogdan, Rosca Alin-Costin
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_CATEGORIES_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_CATEGORIES_H_

#include <unordered_map>
#include <time.h>

#include "./years.h"
#include "./movie.h"

class category {
 private:
	std::unordered_map<int, year> years;
	double best_rating;
	int best_year;
	bool up_to_date;

 public:
 	category();

	void add_movie_in_year(movie &m);
	void outdate(int timestamp);

	int get_best_year();
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_CATEGORIES_H_
