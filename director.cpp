#include <unordered_set>
#include <string>

#include "director.h"

director::director() {
	this->director_name = "";
}

director::director(std::string name) {
    this->director_name = name;
}

director::director(const director &director2) {
    this->director_name = director2.director_name;
    this->collaborations = director2.collaborations;
}

director::~director() {};

director& director::operator=(const director &director2) {
    this->director_name = director2.director_name;
    this->collaborations = director2.collaborations;
    return *this;
}

bool director::operator<(const director &director2) const {
    if (this->collaborations.size() < director2.collaborations.size()) {
        return true;
    } else if (this->collaborations.size() == director2.collaborations.size()) {
        if (this->director_name > director2.director_name) {
            return true;
        }
    }

    return false;
}

bool director::check_collaboration(std::string actor_id) {
    if (collaborations.find(actor_id) != collaborations.end()) {
        return true;
    }
    return false;
}

void director::add_collaboration(std::string actor_id) {
    collaborations.insert(actor_id);
}

