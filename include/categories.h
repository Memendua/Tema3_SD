// #ifndef __CATEGORIES__H__
// #define __CATEGORIES__H__

// #include <unordered_map>
// #include <time.h>

// #include "years.h"

// class category {
// private:
// 	std::unordered_map<int, year> years;
// 	double best_rating;
// 	int best_year;
// public:
// 	void add_movie_in_year(movie *m, double old_rating) {
// 		int year = gmtime(m->timestamp)->tm_year + 1900;
// 		years[year].add_movie(m, old_rating);
// 		double new_rating = years[year].get_rating();
		
// 		if (year == best_year) {
// 			best_rating = -1;
// 			for (auto it = years.begin(); it != years.end(); ++it) {
// 				double rating = it->second->get_rating();
// 				if (best_rating < rating) {
// 					best_rating = rating;
// 					best_year = it->first;
// 				} else if (rating == best_rating && it->first < best_year) {
// 					best_rating = rating;
// 					best_year = it->first;
// 				}
// 			}
// 		} else if (best_rating < new_rating) {
// 			best_rating = new_rating;
// 			best_year = year;
// 		} else if (best_rating == new_rating && year < best_year) {
// 			best_rating = new_rating;
// 			best_year = year;
// 		}
// 	}
// };

// #endif
