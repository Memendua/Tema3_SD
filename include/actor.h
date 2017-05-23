// Copyright 2017 Popa Bogdan, Rosca Alin-Costin
#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_ACTOR_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_ACTOR_H_

#include <string>
#include <unordered_map>

class actor {
 private:
	int debut_year;
	int last_year;
	int years;
	std::string actor_name;
	std::string actor_id;
	std::unordered_map<std::string, int> colleagues;

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

	void add_colleague(std::string id);
	bool check_colleague(std::string id);
	std::unordered_map<std::string, int>& get_colleagues();
};

class ActorPair {
 private:
	std::string actor1_id;
	std::string actor2_id;
	int movies_together;

 public:
 	ActorPair();
 	ActorPair(std::string actor1_id, std::string actor2_id);
 	ActorPair(std::string actor1_id, std::string actor2_id, int m);
 	ActorPair(const ActorPair &p);
 	~ActorPair();

 	std::string show_pair();
 	std::string show_partner();
 	void increase_collaboration();

 	bool operator<(const ActorPair &p);
 	ActorPair& operator=(const ActorPair &p);
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_ACTOR_H_
