#include <iterator>
#include <string>
#include <vector>

#include "imdb.h"


IMDb::IMDb() {
    // initialize what you need here.
}

IMDb::~IMDb() {}

void IMDb::add_movie(std::string movie_name,
                     std::string movie_id,
                     int timestamp, // unix timestamp when movie was launched
                     std::vector<std::string> categories,
                     std::string director_name,
                     std::vector<std::string> actor_ids) {
}

void IMDb::add_user(std::string user_id, std::string name) {
}

void IMDb::add_actor(std::string actor_id, std::string name) {
}

void IMDb::add_rating(std::string user_id, std::string movie_id, int rating) {
}

void IMDb::update_rating(std::string user_id, std::string movie_id, int rating) {
}

void IMDb::remove_rating(std::string user_id, std::string movie_id) {
}

std::string IMDb::get_rating(std::string movie_id) {
    return "";
}

std::string IMDb::get_longest_career_actor() {
    return "";
}

std::string IMDb::get_most_influential_director() {
    return "";
}

std::string IMDb::get_best_year_for_category(std::string category) {
    return "";
}

std::string IMDb::get_2nd_degree_colleagues(std::string actor_id) {
    return "";
}

std::string IMDb::get_top_k_most_recent_movies(int k) {
    return "";
}

std::string IMDb::get_top_k_actor_pairs(int k) {
    return "";
}

std::string IMDb::get_top_k_partners_for_actor(int k, std::string actor_id) {
    return "";
}

std::string IMDb::get_top_k_most_popular_movies(int k) {
    return "";
}

std::string IMDb::get_avg_rating_in_range(int start, int end) {
    return "";
}
