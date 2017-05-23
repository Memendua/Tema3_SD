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
    // this->checked = false;
}

actor::actor(std::string actor_id, std::string actor_name) {
	this->actor_name = actor_name;
	this->actor_id = actor_id;
	this->debut_year = INT_MAX;
	this->last_year = INT_MIN;
	this->years = 0;
    // this->checked = false;
}

actor::actor(const actor &actor2) {
    this->debut_year = actor2.debut_year;
    this->last_year = actor2.last_year;
    this->years = actor2.years;
    // this->checked = actor2.checked;
    this->actor_name = actor2.actor_name;
    this->actor_id = actor2.actor_id;
    // this->colleagues = actor2.colleagues;
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

// bool actor::check() {
//     return checked;
// }

// void actor::checking() {
//     checked = !checked;
// }

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
    // this->colleagues = actor2.colleagues;
    return *this;
}

// void actor::add_colleague(std::string id1) {
//     this->colleagues.insert(id1);
// }

// std::unordered_set<std::string>& actor::get_colleagues() {
//     return colleagues;
// }
