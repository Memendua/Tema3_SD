#ifndef __MOVIE__H__
#define __MOVIE__H__

#include <vector>
#include <unordered_map>
#include <string>

class movie {
private:
	int timestamp;
	int position;
	double rating_until_this;
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
    void set_position(int position);
    void set_rating_until_this(double prev_rating);

    double get_rating() const;
    double get_rating_until_this() const;
    int get_timestamp() const;
    int get_position() const;
    std::string get_movie_id() const;

    int nr_ratings() const;

    bool operator<(const movie &movie1) const;
};

#endif
