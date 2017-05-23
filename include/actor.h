#ifndef __ACTOR__H__
#define __ACTOR__H__

#include <string>
#include <unordered_map>

class actor {
private:
	int debut_year;
	int last_year;
	int years;
	bool checked;
	std::string actor_name;
	std::string actor_id;
	std::unordered_map<std::string, actor> colleagues;

public:
	actor();
	actor(std::string actor_id, std::string actor_name);
	actor(const actor &actor2);
	~actor();

	int& get_debut_year();
	int& get_last_year();
	int& get_years();
	std::string get_id();
	bool check();
	void checking();

	bool operator<(const actor &actor2) const;
	actor& operator=(const actor &actor2);

	void add_colleague(std::string id1, actor actor1);
	std::unordered_map<std::string, actor>& get_colleagues();
};

#endif
