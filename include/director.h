#ifndef __DIRECTOR__H__
#define __DIRECTOR__H__

#include <unordered_set>
#include <string>

struct director {

	std::string director_name;
	std::unordered_set<std::string> collaborations;

	director();
	director(std::string name);
	director(const director &director2);
	~director();
	
	director& operator=(const director &director);
	bool operator<(const director &director2) const;

	bool check_collaboration(std::string actor_id);
	void add_collaboration(std::string actor_id);

};

#endif
