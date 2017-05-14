#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include <vector>
#include <unordered_map>
#include <string>

class movie {
private:
	int timestamp;
	int rating;
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
};

class actor {
private:
	int debut_year;
	int last_year;
	std::string actor_name;
	std::string actor_id;

public:
	actor(std::string actor_id, std::string name);
	~actor();
}

class director {
private:
	int nr_actors;
	std::string director_name;
	std::unordered_map<std::string, std::string> collaborations;

public:
	director(std::string name);
	~director();

	void check_collaboration(std::string actor_id);
	void add_collaboration(std::string actor_id);

}
#endif
