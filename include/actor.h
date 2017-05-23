#ifndef __ACTOR__H__
#define __ACTOR__H__

#include <string>
#include <unordered_set>

class actor {
private:
	int debut_year;
	int last_year;
	int years;
	// bool checked;
	std::string actor_name;
	std::string actor_id;
	// std::unordered_set<std::string> colleagues;

public:
	actor();
	actor(std::string actor_id, std::string actor_name);
	actor(const actor &actor2);
	~actor();

	int& get_debut_year();
	int& get_last_year();
	int& get_years();
	std::string get_id();
	// bool check();
	// void checking();

	bool operator<(const actor &actor2) const;
	actor& operator=(const actor &actor2);

	// void add_colleague(std::string id1);
	// std::unordered_set<std::string>& get_colleagues();
};

#endif
