#ifndef __ACTOR__H__
#define __ACTOR__H__

#include <string>

class actor {
private:
	int debut_year;
	int last_year;
	int years;
	std::string actor_name;
	std::string actor_id;

public:
	actor();
	actor(std::string actor_id, std::string actor_name);
	actor(const actor &actor2);
	~actor();

	int& get_debut_year();
	int& get_last_year();
	int& get_years();
	std::string get_id();

	bool operator<(const actor &actor2) const;
	actor& operator=(const actor &actor2);
};

#endif
