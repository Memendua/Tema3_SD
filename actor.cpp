// Copyright 2017 Popa Bogdan, Rosca Alin-Costin
#include <limits.h>
#include <string>

#include "include/actor.h"

actor::actor() {
    this->actor_name = "";
    this->actor_id = "";
	this->debut_year = INT_MAX;
	this->last_year = INT_MIN;
	this->years = 0;
}

actor::actor(std::string actor_id, std::string actor_name) {
	this->actor_name = actor_name;
	this->actor_id = actor_id;
	this->debut_year = INT_MAX;
	this->last_year = INT_MIN;
	this->years = 0;
}

actor::actor(const actor &actor2) {
    this->debut_year = actor2.debut_year;
    this->last_year = actor2.last_year;
    this->years = actor2.years;
    this->actor_name = actor2.actor_name;
    this->actor_id = actor2.actor_id;
    this->colleagues = actor2.colleagues;
}

actor::~actor() {}

int& actor::get_debut_year() {
    return debut_year;
}

int& actor::get_last_year() {
    return last_year;
}

int& actor::get_years() {
    return years;
}

std::string actor::get_id() {
	return actor_id;
}

bool actor::operator<(const actor &actor2) const {
    if (this->years < actor2.years) {
    	return true;
    } else if (this->years == actor2.years) {
    	if (this->actor_id > actor2.actor_id) {
    		return true;
    	}
    }

    return false;
}

actor& actor::operator=(const actor &actor2) {
    this->debut_year = actor2.debut_year;
    this->last_year = actor2.last_year;
    this->years = actor2.years;
    this->actor_name = actor2.actor_name;
    this->actor_id = actor2.actor_id;
    this->colleagues = actor2.colleagues;
    return *this;
}

void actor::add_colleague(std::string id) {
    ++colleagues[id];
}

bool actor::check_colleague(std::string id) {
    if (colleagues.find(id) != colleagues.end()) {
        return true;
    }
    return false;
}

std::unordered_map<std::string, int>& actor::get_colleagues() {
    return colleagues;
}

ActorPair::ActorPair() {
    this->actor1_id = "";
    this->actor2_id = "";
    this->movies_together = 0;
}

ActorPair::ActorPair(std::string actor1_id, std::string actor2_id) {
    this->actor1_id = actor1_id;
    this->actor2_id = actor2_id;
    this->movies_together = 0;
}

ActorPair::ActorPair(std::string actor1_id, std::string actor2_id, int m) {
    this->actor1_id = actor1_id;
    this->actor2_id = actor2_id;
    this->movies_together = m;
}

ActorPair::ActorPair(const ActorPair &p) {
    this->actor1_id = p.actor1_id;
    this->actor2_id = p.actor2_id;
    this->movies_together = p.movies_together;
}

ActorPair& ActorPair::operator=(const ActorPair &p) {
    this->actor1_id = p.actor1_id;
    this->actor2_id = p.actor2_id;
    this->movies_together = p.movies_together;
    return *this;
}

ActorPair::~ActorPair() {}

std::string ActorPair::show_pair() {
    std::string nr_movies = std::to_string(movies_together);
    return "(" + actor1_id + " " + actor2_id + " " + nr_movies + ")";
}

std::string ActorPair::show_partner() {
    return actor1_id;
}

void ActorPair::increase_collaboration() {
    ++movies_together;
}

bool ActorPair::operator<(const ActorPair &p) {
    if (this->movies_together > p.movies_together) {
        return true;
    } else if (this->movies_together == p.movies_together) {
        if (this->actor1_id < p.actor1_id) {
            return true;
        } else if (this->actor1_id == p.actor1_id) {
            if (this->actor2_id < p.actor2_id) {
                return true;
            }
        }
    }
    return false;
}