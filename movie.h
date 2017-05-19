#ifndef __MOVIE__H__
#define __MOVIE__H__

#include <vector>
#include <unordered_map>
#include <string>

class movie {
private:
	int timestamp;
	double rating;
	std::string movie_name;
	std::string movie_id;
	std::string director_name;
	std::vector<std::string> categories;
	std::vector<std::string> actor_ids;
	std::unordered_map<std::string, int> ratings;

public:
	movie();
	movie(int timestamp);
	movie(std::string movie_name, std::string movie_id, int timestamp,
		  std::vector<std::string> categories, std::string director_name,
          std::vector<std::string> actor_ids);
	~movie();

	double add_rating(std::string user_id, int rating);
    double update_rating(std::string user_id, int rating);
    double remove_rating(std::string user_id);

    double get_rating() const;
    std::string get_movie_id() const;

    int no_ratings() const;

    bool operator<(const movie &movie1) const;
};

struct comp_ratings {
	bool operator()(const movie &movie1, const movie &movie2) {
    	if (movie1.no_ratings() < movie2.no_ratings()) {
        	return true;
    	} else if (movie1.no_ratings() == movie2.no_ratings()) {
        	if (movie1.get_movie_id() > movie2.get_movie_id()) {
            	return true;
        	}
    	}

    	return false;
	}
};

#endif
