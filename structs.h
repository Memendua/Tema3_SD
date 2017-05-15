#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

class movie {
private:
	int timestamp;
	double rating;
	int nr_ratings;
	std::string movie_name;
	std::string movie_id;
	std::string director_name;
	std::vector<std::string> categories;
	std::vector<std::string> actor_ids;
	std::unordered_map<std::string, int> ratings;

public:
	movie(std::string movie_name, std::string movie_id, int timestamp,
		  std::vector<std::string> categories, std::string director_name,
          std::vector<std::string> actor_ids);
	~movie();

	void add_rating(std::string user_id, int rating);
    void update_rating(std::string user_id, int rating);
    void remove_rating(std::string user_id);

    double get_rating();
    bool no_ratings();

};

class actor {
private:
	int debut_year;
	int last_year;
	int years;
	std::string actor_name;
	std::string actor_id;

public:
	actor(std::string actor_id, std::string name);
	actor(const actor &actor2);
	~actor();

	int& get_debut_year();
	int& get_last_year();
	int& get_years();

	bool operator<(const actor &actor2);
	actor& operator=(const actor &actor2);
}

struct director {

	int nr_actors;
	std::string director_name;
	std::unordered_set<std::string> collaborations;  // L-am facut set


	director(std::string name);
	director(const director &director2);
	~director();

	bool check_collaboration(std::string actor_id);
	void add_collaboration(std::string actor_id);

	bool operator<(const director &director2);
	director& operator=(const director &director);
}
#endif
