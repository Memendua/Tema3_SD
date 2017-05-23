// Copyright 2017 Popa Bogdan, Rosca Alin-Costin
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_DIRECTOR_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_DIRECTOR_H_

#include <unordered_set>
#include <string>

struct director {
	std::string director_name;
	std::unordered_set<std::string> collaborations;

	director();
	explicit director(std::string name);
	director(const director &director2);
	~director();

	director& operator=(const director &director);
	bool operator<(const director &director2) const;

	bool check_collaboration(std::string actor_id);
	void add_collaboration(std::string actor_id);
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_DIRECTOR_H_
