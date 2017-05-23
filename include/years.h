// Copyright 2017 Popa Bogdan, Rosca Alin-Costin
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_YEARS_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_YEARS_H_

#include <unordered_map>

#include "./movie.h"

class year {
 private:
	std::unordered_map<std::string, movie&> movies_in_year;
	double average_rating;
	bool up_to_date;

 public:
 	year();

 	void outdate();
 	void update();

 	void add_movie(movie &m);

 	double get_avg_rating();

 	bool isUpdated();
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_YEARS_H_
